#include "effects.h"

Effect::Effect(Entity* player_ref)
{
	duration = -1;
	follow = true;
	this->player_ref = player_ref;
}
