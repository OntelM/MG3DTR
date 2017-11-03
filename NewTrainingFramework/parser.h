#pragma once
#include "../Utilities/utilities.h"
#include <fstream>
#include <sstream>
#include "Vertex.h"
#include <vector>


using namespace std;

class Parser{
public:

	int nrVer;
	int nrInd;
	//Vector3 pos[nrVertices], norm[nrVertices], binorm[nrVertices], tgt[nrVertices];  //Vertices list
	//GLushort indices[4000];
	
	vector<string> wordVector;
//---------------------------------------------------------------

	Vertex* verList = new Vertex[nrVer];
	GLushort* indices = new GLushort[nrInd];
	Vertex ddd;
	GLushort iii;

	Parser();

	void convertObject(string file);
	void test(string s);
	inline bool isDelim(char c);
	void setNrVer(int a);
	int getNrVer();
	void setNrInd(int a);
	int getNrInd();
};
