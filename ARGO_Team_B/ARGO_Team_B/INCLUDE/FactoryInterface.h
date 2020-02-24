#pragma once
#include "WeaponInterface.h"
#include <vector>
class Factory {
public:
	virtual Weapon* CreateLongAxe() = 0;
	virtual Weapon* CreateRepeater() = 0;
};
