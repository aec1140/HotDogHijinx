#pragma once
#include<glm/glm.hpp>
#include<glm/gtx/transform.hpp>
using namespace glm;

class Camera
{
public:
	Camera();
	Camera(vec3 pos, float startYaw, float startPitch);
	~Camera();
	void turn(float dx, float dy);
	vec3 getLocation();
	vec3 getForward();
	vec3 getLookAt();
	vec3 getUp();
	vec3 getRight();
	vec3 getLookDir();
	void setPosition(vec3 pos);

private:
	vec3 position;
	float yaw;
	float pitch;
};

