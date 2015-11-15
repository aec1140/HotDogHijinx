#pragma once
#include "Entity.h"
#include "Camera.h"
class Player :
	public Entity
{
public:
	Player(Shape* s, vec3 pos, vec3 scalVec, float rotRat);
	~Player();
	void update(float dt);
	void setCam(Camera* c);
	vec3 getForward();
	void setCenter(vector<vec3> vert);
private:
	Camera* cam;
	vec3 center;
};

