#include "components/pickups/crossbow_ammo_pickup.h"


void CrossbowAmmoPickup::onPickUp() {
	Inventory::CrossbowAmmo += 10;
	Factory::CreateTextPopup(this->entity->world, this->entity->position, "10x crossbow ammo");

	this->entity->world->remove(this->entity);

}

void CrossbowAmmoPickup::update() {

	Pickupable::update();
}