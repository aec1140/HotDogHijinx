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

void Player::setCam(Camera* c)
{
	cam = c;
}