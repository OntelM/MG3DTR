#pragma once
#include "../Utilities/utilities.h"
#include <string>
#include <Vector>
#include "Shaders.h"
#include "Texture.h"
#include "Model.h"

using namespace std;

class SceneObject {
public:
	SceneObject();
	~SceneObject();
	
	GLint id, lights, followingCamera;
	Vector3 position, rotation, scale;
	string depthTest, blend, name, type;
	GLfloat selfRotateSpeed, dispMax;
	string modView;
	int w;
	void virtual Draw(int w);
	void virtual Update(GLfloat deltaTime);

	Model *model;
	vector<Texture*> texture;
	Shaders* myShaders;


	void SendData();
	Vertex* listVertex;
	Vector3* AABB;

	GLuint vboDebugId, indDebug;
	float	xMin, xMax, yMin, yMax, zMin, zMax;
	int nrIndiciWiredDebug = 24;
	int nrVerDebug = 8;





	Vector3 startPoint, endPoint, center;
	vector<Vector3> pointPosition;
	Vector3 rotPlane;
	enum TypeTraj { T_STATIC, T_LINEAR, T_LINE_STRIP, T_LINE_LOOP, T_CIRCLE };
	TypeTraj typeTrajectory;
	bool trajectory;
	int iterationTrajectory;
	const GLfloat PI = 3.1415;
	string directionTrajectory;
	Vector3 color;
	GLfloat speed;
	int radius;
	int pointSize;
	int sens;
	int inc;
	GLfloat unghi;
	Matrix M;

};


