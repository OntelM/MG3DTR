#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <Vector>
#include "SceneObject.h"
#include "Camera.h"
#include "SceneManager.h"
#include "Vertex.h"

class Fire: public SceneObject {
public:
	Fire();
	float time;
	void Draw(int w);
	void Update(GLfloat deltaTime);
};