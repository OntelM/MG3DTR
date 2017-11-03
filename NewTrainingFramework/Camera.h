#pragma once

#include "../Utilities/utilities.h"
using namespace std;

class Camera {
public:
	Vector4 position, rotation, target, up, xAxis, yAxis, zAxis;
	Matrix viewMatrix, worldMatrix;
	GLfloat translationSpeed, rotationSpeed, vnear, vfar, fov;
	Matrix MVP;
	GLfloat deltaTime;

	
	GLfloat unghi;
	Vector4 localUp = Vector4(0.0f, 1.0f, 0.0f, 0.0f);
	GLfloat directie = 1.0f; //1 su -1


	Camera();


	void setDeltaTime(GLfloat d);
	void moveOz(GLfloat directie);
	void moveOy(GLfloat directie);
	void moveOx(GLfloat directie);
	void rotateOx(GLfloat directie);
	void rotateOy(GLfloat directie);
	void rotateOz(GLfloat directie);
	void updateWorldView();


	Vector3 cToV3(Vector4 a);
	Vector4 cToV4(Vector3 a, GLfloat b);
	~Camera();
};


