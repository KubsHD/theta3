#include "components/pickups/medpack_pickup.h"


void MedpackPickup::onPickUp() {
	player->health += 25;
	if (player->health > 100) {
		player->health = 100;
	}
	Factory::CreateTextPopup(this->entity->world, this->entity->position, "healed 25 HP");
	this->entity->world->remove(this->entity);

}

void MedpackPickup::update() {

	Pickupable::update();
}