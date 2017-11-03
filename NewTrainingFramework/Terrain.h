#pragma once
#include <iostream>
#include "stdafx.h"
#include "stdio.h"
#include "../Utilities/utilities.h"
#include "SceneObject.h"
#include "Vertex.h"
#include "Model.h"
#include "Camera.h"

using namespace std;

class Terrain : public SceneObject {
public:
	Terrain();
	GLuint id, iboId, wiredIboId, vboId, nrVer, nrInd, nrWired;
	int nrCel;
	float dimCel;
	float offsetY;
	Vector3 inaltimi;
	void generate();
	

	Vertex* listVertex;
	Camera* cam;
	void virtual Draw(int w);
	void virtual Update(GLfloat deltaTime);
	float f1, f2;
};