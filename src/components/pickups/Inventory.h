#pragma once

#include "components/gun_type.h"

static class Inventory {
public:
	static long int PistolAmmo;
	static long int ShotgunAmmo;
	static long int MachinegunAmmo;
	static long int CrossbowAmmo;

	Inventory() {
		PistolAmmo = 50000;
		ShotgunAmmo = 0;
		MachinegunAmmo = 0;
		CrossbowAmmo = 0;
	}

	static bool HasAmmo(GUN_TYPE gun_type);

	static bool CanShootThenSubstractAmmo(GUN_TYPE gun_type);
};