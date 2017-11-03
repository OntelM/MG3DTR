#pragma once
#include "../Utilities/utilities.h"
#include "Structuri.h"
#include <vector>
#include "Vertex.h"
using namespace std;

class Model {
public:
	ModelResource* mr;
	GLuint id, iboId, wiredIboId, vboId;
	GLushort nrIndici, nrIndiciWired;
	string file;
	void LoadModel();
	void LoadNFG();
	void LoadOBJ();
	Vertex *listVertex;
	GLushort *listIndici;
	int nrVer;
	Model();
	~Model();
	string Extension(string str);
};


