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

	setCenter(s->getVert());
}

Entity::~Entity(void)
{
}

//Methods
void Entity::update(float dt)
{
	velocity += acceleration * dt;
	position += velocity;
	center += velocity;
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

void Entity::setCenter(vector<vec3> vert)
{
	// random vertex x
	vec3 randX = vert[1];

	// most distant y
	float distance = 0;
	vec3 y;

	for (int i = 0; i < vert.size(); i++)
	{
		float x1 = randX.x;
		float x2 = vert[i].x;
		float y1 = randX.y;
		float y2 = vert[i].y;
		float z1 = randX.z;
		float z2 = vert[i].z;

		float d = sqrt(((x2 - x1)*(x2 - x1)) +
			((y2 - y1)*(y2 - y1)) +
			((z2 - z1)*(z2 - z1)));
		if (d > distance)
		{
			distance = d;
			y = vert[i];
		}
	}

	// most distant z
	distance = 0;
	vec3 z;

	for (int i = 0; i < vert.size(); i++)
	{
		float x1 = y.x;
		float x2 = vert[i].x;
		float y1 = y.y;
		float y2 = vert[i].y;
		float z1 = y.z;
		float z2 = vert[i].z;

		float d = sqrt(((x2 - x1)*(x2 - x1)) +
			((y2 - y1)*(y2 - y1)) +
			((z2 - z1)*(z2 - z1)));
		if (d > distance)
		{
			distance = d;
			z = vert[i];
		}
	}

	// Put the sphere halfway between y and z
	vec3 c = (y + z) / 2.0f;
	float diameter = distance;

	// Find an external vertex not in the sphere
	for (int i = 0; i < vert.size(); i++)
	{
		float x1 = c.x;
		float x2 = vert[i].x;
		float y1 = c.y;
		float y2 = vert[i].y;
		float z1 = c.z;
		float z2 = vert[i].z;

		float d = sqrt(((x2 - x1)*(x2 - x1)) +
			((y2 - y1)*(y2 - y1)) +
			((z2 - z1)*(z2 - z1)));

		float delta = abs(d) - (diameter / 2);

		if (delta > 0)
		{
			diameter += delta;
			c += (delta / 2);
		}
	}

	this->center = c;
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

vec3 Entity::getCenter()
{
	return this->center;
}

float Entity::getRotateAmt()
{
	return rotAm;
}
