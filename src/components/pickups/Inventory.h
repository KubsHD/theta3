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

	static bool HasAmmo(GUN_TYPE gun_type) {
		switch (gun_type)
		{
			case PISTOL:
			{
				if (PistolAmmo > 0) {
					return true;
				}
				return false;
				break;
			}

			case SHOTGUN:
			{
				if (ShotgunAmmo > 0) {
					return true;
				}
				return false;
				break;
			}

			case MACHINE_GUN:
			{
				if (MachinegunAmmo > 0) {
					return true;
				}
				return false;
				break;
			}

			case CROSSBOW:
			{
				if (CrossbowAmmo > 0) {
					return true;
				}
				return false;
				break;
			}
			default:
			{
				break;
			}
		}
	}

	static bool CanShootThenSubstractAmmo(GUN_TYPE gun_type) {
		switch (gun_type)
		{
			case PISTOL:
			{
				if (PistolAmmo > 0) {
					return true;
				}
				return false;
				break;
			}

			case SHOTGUN:
			{
				if (ShotgunAmmo > 0) {
					ShotgunAmmo--;
					return true;
				}
				return false;
				break;
			}

			case MACHINE_GUN:
			{
				if (MachinegunAmmo > 0) {
					MachinegunAmmo--;
					return true;
				}
				return false;
				break;
			}

			case CROSSBOW:
			{
				if (CrossbowAmmo > 0) {
					CrossbowAmmo--;
					return true;
				}
				return false;
				break;
			}
			default:
			{
				break;
			}
		}
	}
};