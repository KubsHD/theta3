#include "Inventory.h"
 long int Inventory::PistolAmmo;
 long int Inventory::ShotgunAmmo;
 long int Inventory::MachinegunAmmo;
 long int Inventory::CrossbowAmmo;
bool Inventory::CanShootThenSubstractAmmo(GUN_TYPE gun_type) {
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

bool Inventory::HasAmmo(GUN_TYPE gun_type) {
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