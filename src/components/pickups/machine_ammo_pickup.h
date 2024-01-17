#pragma once

#include "components/pickups/pickupable.h"

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

class MachineAmmoPickup : public Pickupable {
public:

	MachineAmmoPickup() = default;
	MachineAmmoPickup(Player* p) {
		player = p;
	}
	
	void onPickUp() override;

	void update() override;

};