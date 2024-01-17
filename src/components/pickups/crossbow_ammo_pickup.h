#pragma once

#include "components/pickups/pickupable.h"

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

class CrossbowAmmoPickup : public Pickupable {
public:

	CrossbowAmmoPickup() = default;
	CrossbowAmmoPickup(Player* p) {
		player = p;
	}
	
	void onPickUp() override;

	void update() override;

};