#pragma once
#include "../Utilities/utilities.h"
#include "ResourceManager.h"


class Parsobj {
public:
	ModelResource* mr;
	GLuint iboId, wiredIboId, vboId;
	GLushort nrIndici, nrIndiciWired;
	Parsobj();
	~Parsobj();
	void Load();	//Incarca modelul din fisierul .nfg
};