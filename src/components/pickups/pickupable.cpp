#include "pickupable.h"




void Pickupable::update(){

	if (glm::distance(entity->position, player->pos_sprite_center) < 32){

		this->onPickUp();
		return;
	}

}

