// BasicOGL.cpp : Defines the entry point for the console application.
#pragma once
#include<iostream>
#include "stdafx.h"
#include<glew.h>
#include<glfw3.h>
#include"ShaderHelper.h"
#include"Entity.h"
#include<vector>
#include<time.h>
#include"Camera.h"

using namespace std;

//PI (glm math documentation is bad)
const float PI = 3.14159265358979f;

//Global variables
GLFWwindow* windowPtr;
int result;
vector<Entity*> entities;
Shape* monkey;
Camera* playerCam;
bool mouseButtonHeld;
bool wHeld;
bool aHeld;
bool sHeld;
bool dHeld;
double prevTime;

//Set up OGL
int initialize()
{
	cout << "Initializing..." << endl;

	//RNG
	srand((uint)time(NULL));

	//Initialize the library
	if (!glfwInit()) return -1;

	//Create window
	windowPtr = glfwCreateWindow(800, 800, "Model!", NULL, NULL);
	if (!windowPtr)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(windowPtr);

	//Initailize GLEW
	if (glewInit() != GLEW_OK) return false;

	//Set background
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Wireframes
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	//Load shader program
	result = loadShaderProgram("Shaders/vertexShader.glsl", "Shaders/fragmentShader.glsl");
	if (result != 0) glUseProgram(result);

	//Create Model entity
	monkey = new Shape("monkey2.obj", result);
	entities.push_back(new Entity(monkey, vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), 0.0f));
	entities[0]->setActive(true);

	//Create camera
	playerCam = new Camera(vec3(0, 0, 1), 0.f, PI/2);
	glfwSetInputMode(windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	return 0;
}

void update()
{
	//Calc framerate
	double curTime = glfwGetTime();
	float dt = (float)(curTime - prevTime);
	prevTime = curTime;

	//Update
	vec3 g = vec3(0.0f, -0.1f, 0.0f);
	for (uint i = 0; i < entities.size(); i++)
	{
		//Update active ones only
		if (entities[i]->getActive() == true)
		{
			//Update
			entities[i]->update(dt);
		}

		//Move camera
		vec3 newPos = playerCam->getLocation();
		if (wHeld)
		{
			newPos += playerCam->getLookDir() * .05f;
		}
		if (aHeld)
		{
			newPos += playerCam->getRight() * -.05f;
		}
		if (sHeld)
		{
			newPos += playerCam->getLookDir() * -.05f;
		}
		if (dHeld)
		{
			newPos += playerCam->getRight() * .05f;
		}
		playerCam->setPosition(newPos);
	}
}

void draw()
{
	//Clear the screen
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Draw triangles
	mat4 perspecMat = perspective(PI/3.f, 1.0f, 0.01f, 1000.0f);
	mat4 lookMat = lookAt(playerCam->getLocation(), playerCam->getLookAt(), vec3(0.0f,1.0f,0.0f));

	mat4 camMat = perspecMat * lookMat;
	for (uint i = 0; i < entities.size(); i++)
	{
		if (entities[i]->getActive() == true)
			entities[i]->draw(&camMat);
	}

	//Flush
	glFlush();
}

//Input callbacks
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	//Get Cursor Position and Window size
	int width, height;
	double xpos, ypos;
	glfwGetWindowSize(window, &width, &height);
	glfwGetCursorPos(window, &xpos, &ypos);

	//Convert coordinates
	xpos = (2 * xpos / width) - 1;
	ypos = -(2 * ypos / height) + 1;

	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		mouseButtonHeld = true;
	}
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
	{
		mouseButtonHeld = false;
	}
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_W && action == GLFW_PRESS)
	{
		wHeld = true;
	}
	else if (key == GLFW_KEY_W && action == GLFW_RELEASE)
	{
		wHeld = false;
	}
	else if (key == GLFW_KEY_A && action == GLFW_PRESS)
	{
		aHeld = true;
	}
	else if (key == GLFW_KEY_A && action == GLFW_RELEASE)
	{
		aHeld = false;
	}
	else if (key == GLFW_KEY_S && action == GLFW_PRESS)
	{
		sHeld = true;
	}
	else if (key == GLFW_KEY_S && action == GLFW_RELEASE)
	{
		sHeld = false;
	}
	else if (key == GLFW_KEY_D && action == GLFW_PRESS)
	{
		dHeld = true;
	}
	else if (key == GLFW_KEY_D && action == GLFW_RELEASE)
	{
		dHeld = false;
	}
	else if (key == GLFW_KEY_Q && action == GLFW_PRESS)
	{
		exit(0);
	}
}

void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	//Get Cursor Position and Window size
	int width, height;
	glfwGetWindowSize(window, &width, &height);

	//Convert coordinates
	xpos = (2 * xpos / width) - 1;
	ypos = -(2 * ypos / height) + 1;

	playerCam->turn(xpos, ypos);

	glfwSetCursorPos(windowPtr, width / 2, height / 2);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//Initialize
	initialize();

	//Set input callbacks
	glfwSetMouseButtonCallback(windowPtr, mouseButtonCallback);
	glfwSetKeyCallback(windowPtr, keyCallback);
	glfwSetCursorPosCallback(windowPtr, cursorCallback);

	while (!glfwWindowShouldClose(windowPtr))
	{
		//Update
		update();

		//Draw
		draw();
		glfwSwapBuffers(windowPtr);
		glfwPollEvents();
	}

	//Delete
	for (uint i = 0; i < entities.size(); i++)
	{
		delete(entities[i]);
	}
	delete playerCam;

	glfwTerminate();
	return 0;
}
