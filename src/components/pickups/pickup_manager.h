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
#include "components/pickups/ammo_pickup.h"


static class PickupManager : public Component{


public:

	static Entity* GetRandomPickup(Player* player) {
		int r = rand() % 100;
		
		if (r < 50) {
			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("icon_skull.png"));
			auto pickupable = pickup->add(AmmoPickup(player));

			return pickup;
		}
		else if (r < 75) {

			//something else

			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("icon_skull.png"));
			auto pickupable = pickup->add(AmmoPickup(player));

			return pickup;
		}
		else if (r < 95) {
			//something else
			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("icon_skull.png"));
			auto pickupable = pickup->add(AmmoPickup(player));

			return pickup;
		}
		else {
			//something else
			Entity* pickup = player->entity->world->create("Pickup");
			auto col = pickup->add(Collider(Vec2(24, 24), Vec2(0, 0)));
			auto sp = pickup->add(Sprite("icon_skull.png"));
			auto pickupable = pickup->add(AmmoPickup(player));

			return pickup;
		}
		
		return NULL;
	}

};