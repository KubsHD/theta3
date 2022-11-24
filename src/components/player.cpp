#include "player.h"

#include <render/Renderer.h>
#include <string>


Player::Player()
{
	health = 100;
	souls = 60;
	speed = 1.0f;
	damage_melee = 10;

}

void Player::update()
{
	;
}

void Player::render(Renderer* ren)
{
	//ren->draw_text("HP: " + std::to_string(health), Renderer::DefaultFont, Vec2(entity->position.x - 60, entity->position.y - 48));

	Enemy::render(ren);
}
