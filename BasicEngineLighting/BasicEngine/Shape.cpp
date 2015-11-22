#include "Shape.h"
using namespace std;
#include<glew.h>
#include"ShaderHelper.h"
#include<glm/gtc/matrix_transform.hpp>
#include<SOIL.h>
#include<iostream>
using namespace glm;

//Constructor/Destructor
Shape::Shape(void)
{
}

Shape::Shape(char* modelFile, char* texture, int index)
{
	shader = index;

	//Load model data
	loadOBJFile(modelFile, verticies, normals, uvs, elements);

	//Combine data
	vector<GLfloat> vertexData;
	for (size_t i = 0; i < elements.size()/3; i++)
	{
		vertexData.push_back(verticies[elements[3*i]].x);
		vertexData.push_back(verticies[elements[3*i]].y);
		vertexData.push_back(verticies[elements[3*i]].z);
		vertexData.push_back(uvs[elements[3*i]+1].x);
		vertexData.push_back(uvs[elements[3*i]+1].y);
		vertexData.push_back(normals[elements[3*i]+2].x);
		vertexData.push_back(normals[elements[3*i]+2].y);
		vertexData.push_back(normals[elements[3*i]+2].z);
	}

	vector<unsigned int> elementData;
	for (unsigned int i = 0; i < elements.size()/3; i++)
	{
		elementData.push_back(i);
	}

	//Create vbo and ebo
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	//Load texture
	textureID = SOIL_load_OGL_texture(texture, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_INVERT_Y);
	glBindTexture(GL_TEXTURE_2D, textureID);

	//Enter data
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * vertexData.size(), &vertexData[0], GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * elementData.size(), &elementData[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * NUMFLOATS, 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * NUMFLOATS, (void*)(sizeof(GL_FLOAT) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * NUMFLOATS, (void*)(sizeof(GL_FLOAT) * 5));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	//Get the location of world matrix
	worldMatLoc = glGetUniformLocation(index, "worldMatrix");
}

Shape::~Shape(void)
{
	//Delete objects
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

//Methods
void Shape::draw(vec3 currPos, vec3 scaling, vec3 rotAx, float rotAm, mat4* camMat)
{

	//Gen transform matrix
	mat4 transform = mat4();
	transform = translate(transform, currPos);
	transform = scale(transform, scaling);
	transform = rotate(transform, -rotAm, rotAx);

	//Matrix multiplication is associative!! :D
	transform = (*camMat) * transform;

	//Set transform matrix
	setShaderMatrix(shader, worldMatLoc, transform);

	//Bind array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	cout << rotAm << endl;

	//Draw elements
	glDrawElements(GL_TRIANGLES, elements.size() * NUMFLOATS, GL_UNSIGNED_INT, (void*)0);
}

vector<vec3> Shape::getVert()
{
	return verticies;
}
