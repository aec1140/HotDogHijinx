#include "Camera.h"

const float PI = 3.14159265358979f;

//Constructors destructor
Camera::Camera()
{
}

Camera::Camera(vec3 pos, float startYaw, float startPitch)
{
	position = pos;
	yaw = startYaw;
	pitch = startPitch;
}

Camera::~Camera()
{
}

void Camera::turn(float dx, float dy)
{
	yaw += dx * 1.f *.5f;
	if (yaw > PI)
	{
		yaw -= 2 * PI;
	}
	else if (yaw < -1.0f * PI)
	{
		yaw += 2 * PI;
	}
	if (!(pitch + (dy * 1.f * .5f) >= PI) && !((pitch + (dy * 1.f * .5f)) <= 0))
	{
		pitch += dy * 1.f * .5f;
	}
}

vec3 Camera::getLocation()
{
	return position;
}

void Camera::setPosition(vec3 pos)
{
	position = pos;
}

vec3 Camera::getForward()
{
	vec3 forward = (vec3(0.f, 0.f, -1.f) * cos(yaw)) + (vec3(1.f, 0.f, 0.f) * sin(yaw));
	normalize(forward);
	return forward;
}

vec3 Camera::getLookAt()
{
	vec3 look = getLocation() + getLookDir();
	normalize(look);
	return look;
}

vec3 Camera::getLookDir()
{
	vec3 dir = cross(getUp(), getRight());
	return dir;
}

vec3 Camera::getUp()
{
	vec3 up = vec3(0.f, 1.f, 0.f) * sin(pitch);
	up = up +  -1.f * getForward() * cos(pitch);
	normalize(up);
	return up;
}

vec3 Camera::getRight()
{
	vec3 right = cross(vec3(0.f, 1.f, 0.f), getForward());
	return right;
}