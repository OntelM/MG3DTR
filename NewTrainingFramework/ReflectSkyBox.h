#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <Vector>
#include "SceneObject.h"
#include "SceneManager.h"
#include "Camera.h"
#include "Vertex.h"

class ReflectSkyBox: public SceneObject {
public:
	ReflectSkyBox();
	void Draw(int w);

};