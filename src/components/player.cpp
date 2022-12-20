#include "player.h"

#include <render/Renderer.h>
#include <string>


Player::Player()
{
	health = 100;
	speed = 1.0f;
	damage_melee = 10;
	money = 0;
}

void Player::update()
{
}

void Player::render(Renderer* ren)
{
	;
}
