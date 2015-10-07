//Header
#pragma once;
#include<glew.h>
#include<glfw3.h>
#include<glm/glm.hpp>
#include<vector>
using namespace glm;
using namespace std;

//Functions
char* loadTextFile(const char* file);

GLuint loadShader(const char* file, GLenum shaderType);

GLuint loadShaderProgram(const char* vertexFile, const char* fragmentFile);

void setShaderColor(GLuint index, const char* varName, float red, float green, float blue);

void setShaderMatrix(GLuint index, GLint loc, mat4 &matrix);

//Non-Shader functions
int loadOBJFile(const char* file, vector<vec3> &verticies, vector<vec3> &normals, vector<vec2> &uvs, vector<unsigned int> &elements);