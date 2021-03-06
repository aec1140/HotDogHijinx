#pragma once
#include"Shape.h"
class Entity
{
public:
	Entity(void);
	Entity(Shape* s, vec3 pos, vec3 scalVec, float rotRat);
	~Entity(void);
	virtual void update(float dt);
	void draw(mat4* camMat);
	void setPos(vec3 pos);
	void setScale(vec3 scaleVec);
	void setRotAm(float amount);
	void addForce(vec3 force);
	vec3 getPos();
	void setActive(bool value);
	bool getActive();
	void bounce(bool up);
	void setVelocity(vec3 vel);
	void setRotRate(float rotRate);
	vec3 getCenter();
	float getRotateAmt();

protected:
	vec3 center;
	Shape* shape;
	vec3 position;
	vec3 velocity;
	vec3 acceleration;
	vec3 scale;
	vec3 rotAx;
	float rotRate;
	bool active;
	float rotAm;

	void setCenter(vector<vec3> vert);

};

