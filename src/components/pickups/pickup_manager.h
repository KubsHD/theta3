#pragma once

#include <core/types.h>
#include <core/ecs.h>
#include <stdlib.h>
#include <SDL_stdinc.h>

#include <components/sprite.h>	
#include <core/audio.h>
#include <core/asset.h>
#include <components/player.h>
#include <render/Renderer.h>
#include "components/pickups/shotgun_ammo_pickup.h"
#include "components/pickups/machine_ammo_pickup.h"
#include "components/pickups/crossbow_ammo_pickup.h"
#include "components/pickups/medpack_pickup.h"


static class PickupManager : public Component{


public:

	static Entity* GetRandomPickup(Player* player) {
		int r = rand() % 100;
		
		if (r < 15) {
			//shotugn ammo
			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("pickup_shotgun_ammo.png"));
			auto pickupable = pickup->add(ShotgunAmmoPickup(player));

			return pickup;
		}
		else if (r < 30) {

			//machine gun ammo

			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("pickup_machinegun_ammo.png"));
			auto pickupable = pickup->add(MachineAmmoPickup(player));

			return pickup;
		}
		else if (r < 40) {
			//crossbow ammo
			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("pickup_crossbow_ammo.png"));
			auto pickupable = pickup->add(CrossbowAmmoPickup(player));

			return pickup;
		}
		else if(r < 50){
			//medpack
			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("pickup_medpack.png"));
			auto pickupable = pickup->add(MedpackPickup(player));

			return pickup;
		}
		
		return NULL;
	}

};