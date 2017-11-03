#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <Vector>
#include "SceneObject.h"

class SkyBox : public SceneObject{
public:
	SkyBox();
	void Update(GLfloat deltaTime);
};