#include "components/pickups/ammo_pickup.h"


void AmmoPickup::onPickUp() {
	//TO DO: functionality
	this->entity->world->remove(this->entity);

}

void AmmoPickup::update() {

	Pickupable::update();
}