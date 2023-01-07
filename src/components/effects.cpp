#include "effects.h"

Effect::Effect(Entity* player_ref, String name)
{
	this->name = name;

	duration = -1;
	follow = true;
	this->player_ref = player_ref;

	player_offset = player_ref->get<Player>()->player_offset;

	is_sprite = false;
	is_anim = false;

}

void Effect::play_once()
{
	anim->play_one_shot(name, [this]() {});
}

void Effect::init()
{
	if (sprite = this->entity->get<Sprite>())
	{     
		sprite->enabled = true;
		is_sprite = true;
	}
	if (anim = this->entity->get<Animator>())
	{	
		is_anim = true;
	}

}

void Effect::update()
{
	if (is_sprite)
		entity->position = Vec2(player_ref->position.x - sprite->tex->size.x / 2,
			player_ref->position.y - sprite->tex->size.y / 2) + player_offset;

	if (is_anim)
	{
		entity->position = Vec2(player_ref->position.x - anim->get_frame_size().x / 2,
			player_ref->position.y - anim->get_frame_size().y / 2) + player_offset;
	}
}

void Effect::render(Renderer* ren)
{
}


