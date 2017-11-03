#pragma once
#include "../Utilities/utilities.h"

class Collision {
public:
	BOOLEAN collision;
	int objA, objB;
	Vector3* AABB;
};