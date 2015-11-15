#include "Player.h"



Player::Player(Shape* s, vec3 pos, vec3 scalVec, float rotRat) : Entity(s, pos, scalVec, rotRat)
{
	
}

Player::~Player()
{
}

void Player::update(float dt)
{
	velocity += acceleration * dt;
	position += velocity;
	rotAm += rotRate * dt;
	acceleration = vec3(0, 0, 0);

	cam->setPosition(this->getPos());
}

vec3 Player::getForward()
{
	vec3 forward = (vec3(0.f, 0.f, -1.f) * cosf(rotAm)) + (vec3(1.f, 0.f, 0.f) * sinf(rotAm));
	normalize(forward);
	return forward;
}

void Player::setCenter(vector<vec3> vert)
{
	// random vertex x
	vec3 randX = vert[10];

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

void Player::setCam(Camera* c)
{
	cam = c;
}