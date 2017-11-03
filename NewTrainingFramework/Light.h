#pragma once
#include "stdafx.h"
#include "../Utilities/utilities.h"
#include <string>
#include <iostream>
#include "stdio.h"


#include "Globals.h"
#include "../Utilities/memDbg.h"


using namespace std;

class Light{
public:
	int id, associatedObject;
	Vector3 position, ambiental, diffuseColor, specularColor;
	float type;
	float specCoef, diffCoef, specPower, shininess, ratio, attenuation;
};