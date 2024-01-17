#include "components/pickups/shotgun_ammo_pickup.h"


void ShotgunAmmoPickup::onPickUp() {
	Inventory::ShotgunAmmo += 12;
	Factory::CreateTextPopup(this->entity->world, this->entity->position, "12x shotgun ammo");
	this->entity->world->remove(this->entity);

}

void ShotgunAmmoPickup::update() {

	Pickupable::update();
}