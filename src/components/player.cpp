#include "player.h"

#include <render/Renderer.h>
#include <string>
#include <core/log.h>


Player::Player()
{
	health = 100;
	speed = 1.0f;
	damage_melee = 10;
	money = 0;
	health_decay = 0.05f;
}

void Player::update()
{
	health -= health_decay;
}

void Player::render(Renderer* ren)
{
	;
}
