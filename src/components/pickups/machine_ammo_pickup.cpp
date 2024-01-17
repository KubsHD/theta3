#include "components/pickups/machine_ammo_pickup.h"


void MachineAmmoPickup::onPickUp() {
	Inventory::MachinegunAmmo += 90;
	Factory::CreateTextPopup(this->entity->world, this->entity->position, "50x machine gun ammo");
	this->entity->world->remove(this->entity);

}

void MachineAmmoPickup::update() {

	Pickupable::update();
}