#include"Entity.h"

Entity::Entity(void)
{
}

Entity::Entity(Shape* s, vec3 pos, vec3 scalVec, float rotRat)
{
	shape = s;
	rotAx = vec3(0,1,0);
	acceleration = vec3(0,0,0);
	velocity = vec3(0,0,0);
	position = pos;
	scale = scalVec;
	rotAm = 0.0f;
	rotRate = rotRat;
	active = false;
}

Entity::~Entity(void)
{
}

//Methods
void Entity::update(float dt)
{
	velocity += acceleration * dt;
	position += velocity;
	rotAm += rotRate * dt;
	acceleration = vec3(0,0,0);
}

void Entity::draw(mat4* camMat)
{
	(*shape).draw(position, scale, rotAx, rotAm, camMat);
}

void Entity::addForce(vec3 force)
{
	acceleration += force;
}

void Entity::bounce(bool up)
{
	if (up)
	{
		velocity = vec3(velocity.x, velocity.y * -1.0f, velocity.z);
	}
	else
	{
		velocity = vec3(velocity.x * -1.0f, velocity.y, velocity.z);
	}
}

//Setters
void Entity::setPos(vec3 pos)
{
	position = pos;
}
void Entity::setScale(vec3 scaleVec)
{
	scale = scaleVec;
}
void Entity::setRotAm(float amount)
{
	rotAm = amount;
}

void Entity::setActive(bool value)
{
	active = value;
}

bool Entity::getActive()
{
	return active;
}

vec3 Entity::getPos()
{
	return position;
}

void Entity::setVelocity(vec3 vel)
{
	velocity = vel;
}

void Entity::setRotRate(float rate)
{
	rotRate = rate;
}
