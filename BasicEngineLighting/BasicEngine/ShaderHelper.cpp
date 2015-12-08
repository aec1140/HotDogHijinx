//Header
#pragma once
#include"ShaderHelper.h"
#include<iostream>
#include<fstream>
using namespace std;
#include<glew.h>
#include<glfw3.h>
#include<string>
#include<sstream>

//Functions
char* loadTextFile(const char* file)
{
	//Create input stream
	char* contents = 0;
	ifstream input(file, ios::binary);
	if (input.is_open())
	{
		//Get length
		input.seekg(0, ios::end);
		int length = (int)input.tellg();
		input.seekg(0, ios::beg);

		//Make array
		contents = new char[length + 1];
		input.read(contents, length);
		contents[length] = 0;

		//Close file
		input.close();

		return contents;
	}
	else return 0;
}

GLuint loadShader(const char* file, GLenum shaderType)
{
	//Get shader file
	const char* shader = loadTextFile(file);
	if (shader == 0)
	{
		cout << "Error: Unable to load file" << endl;
		return 0;
	}

	//Create shader
	GLuint index = glCreateShader(shaderType);
	glShaderSource(index, 1, &shader, 0);
	glCompileShader(index);

	//Delete extra data
	delete(shader);

	//Check shader
	GLint result;
	glGetShaderiv(index, GL_COMPILE_STATUS, &result);
	if (result == GL_TRUE) return index;

	//Print log if error
	GLint length;
	glGetShaderiv(index, GL_INFO_LOG_LENGTH, &length);
	char* log = new char[length];
	glGetShaderInfoLog(index, length, 0, log);
	cout << "Error: loadShader:" << endl;
	cout.write(log, length);
	glDeleteShader(index);
	delete[length](log);
	return 0;
}

GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile)
{
	//Load Shaders
	GLuint vertShader = loadShader(vertexFile, GL_VERTEX_SHADER);
	if (vertShader == 0) return 0;
	GLuint fragShader = loadShader(fragmentFile, GL_FRAGMENT_SHADER);
	if (fragShader == 0) return 0;

	//Create shader program
	GLint index = glCreateProgram();
	glAttachShader(index, vertShader);
	glAttachShader(index, fragShader);
	glLinkProgram(index);

	//Check program
	GLint result;
	glGetProgramiv(index, GL_LINK_STATUS, &result);
	if (result == GL_TRUE) return index;

	//Print log if error
	GLint length;
	glGetProgramiv(index, GL_INFO_LOG_LENGTH, &length);
	char* log = new char[length];
	glGetProgramInfoLog(index, length, 0, log);
	cout << "Error: loadShaderProgram:" << endl;
	cout.write(log, length);
	glDeleteProgram(index);
	delete[length](log);
	return 0;
}

void setShaderColor(GLuint index, const char* varName, float red, float green, float blue)
{
	//Get the location
	GLint loc = glGetUniformLocation(index, varName);

	//Set the color
	glProgramUniform4f(index, loc, red, green, blue, 1.0f);
}

void setShaderMatrix(GLuint index, GLint loc, mat4 &matrix)
{
	//Set the matrix
	glProgramUniformMatrix4fv(index, loc, 1, GL_FALSE, &matrix[0][0]);
}

//Non shader functions
//Load obj model - based on tutorial at https://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
int loadOBJFile(const char* file, vector<vec3> &verticies, vector<vec3> &normals, vector<vec2> &uvs, vector<unsigned int> &elements)
{
	//Open file
	ifstream input(file, ios::in);
	if (!input.is_open())
	{
		cout << "Error: Cannot open model" << file << endl;
		return 1;
	}

	//Get data
	string line;
	while (getline(input, line))
	{
		//Sort data into proper vector based on type
		//Vertex data starts with v
		if (line.substr(0, 2) == "v ")
		{
			//Create a stream starting after the second character
			istringstream str(line.substr(2));
			//Slot the numbers into a vec4
			vec3 v; str >> v.x, str >> v.y, str >> v.z;
			//Push vec4 onto vector
			verticies.push_back(v);
		}
		//Element data starts with f
		else if (line.substr(0, 2) == "f ")
		{
			//Same process as to get vertex data
			istringstream str(line.substr(2));
			unsigned int a, b, c; char x;
			for (uint i = 0; i < 3; i++)
			{
				str >> a; str >> x;
				str >> b; str >> x;
				str >> c;
				//Looks like the obj file starts numbering at 1, but we start at 0, so this lines them up
				a--; b--; c--;
				elements.push_back(a); elements.push_back(b); elements.push_back(c);
			}
		}
		//Normals starts with vn
		else if (line.substr(0, 3) == "vn ")
		{
			//Create a stream starting after the third character
			istringstream str(line.substr(3));
			//Slot the numbers into a vec3
			vec3 v; str >> v.x, str >> v.y, str >> v.z;
			//Push vec4 onto vector
			normals.push_back(v);
		}
		else if (line.substr(0,3) =="vt ")
		{
			//Create a stream starting after the third character
			istringstream str(line.substr(3));
			//Slot the numbers into a vec2
			vec2 v; str >> v.x, str >> v.y;
			//Push vec4 onto vector
			uvs.push_back(v);
		}

		//Ignore other stuff for now
		else;
	}
	return 0;
}