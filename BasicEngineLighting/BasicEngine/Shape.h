#pragma once
using namespace std;
#include<glew.h>
#include<glm\glm.hpp>
#include<vector>
using namespace glm;

class Shape
{
public:
	Shape(void);
	Shape(char* modelFile, int index);
	~Shape(void);
	void draw(vec3 currPos, vec3 scaling, vec3 rotAx, float rotAm, mat4* camMat);
	vector<vec3> getVert();

private:
	static const int NUMFLOATS = 8;
	GLuint vbo;
	GLuint ebo;
	vector<vec3> verticies;
	vector<vec3> normals;
	vector<vec2> uvs;
	vector<unsigned int> elements;
	int numVertex;
	GLuint shader;
	GLint worldMatLoc;
	GLuint textureID;
};

