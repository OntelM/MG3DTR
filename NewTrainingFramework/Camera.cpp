#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include <conio.h>
#include "Globals.h"
#include "Camera.h"




Camera::Camera(){
	updateWorldView();
};

	void Camera::setDeltaTime(GLfloat d)
	{
		deltaTime = d;
	}
void Camera::moveOz(GLfloat directie) {
	Vector4 forwardLocal = -(target - position).Normalize() * directie;   // z = directie (initial a fost doar directie)
	Vector4 vectorDeplasare = forwardLocal * translationSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}
void Camera::moveOx(GLfloat directie) {
	Vector3 pos3 = cToV3(position);
	Vector3 tar3 = cToV3(target);
	Vector3 up3 = cToV3(up);

	Vector3 mL3 = (-(tar3 - pos3).Cross(up3)).Normalize();
	Vector4 mL4 = cToV4(mL3, 0.0f);
	Vector4 moveLeft = mL4 * directie;
	Vector4 vectorDeplasare = moveLeft * translationSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}

void Camera::moveOy(GLfloat directie) {
	Vector4 moveUp = up.Normalize() * directie;
	Vector4 vectorDeplasare = moveUp * translationSpeed * deltaTime;
	position += vectorDeplasare;
	target += vectorDeplasare;
	updateWorldView();
}
void Camera::rotateOy(GLfloat directie) {
	GLfloat unghi = rotationSpeed * deltaTime * directie;
	Matrix mRotateOY;
	mRotateOY.SetRotationY(unghi);
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f); //target
	Vector4 rotatedTarget = localTarget * mRotateOY; //matrice de rotatie apelare set rotation de y cu 0.3 ... * timp (deltaTime)
	target = rotatedTarget * worldMatrix;
	updateWorldView();
}
void Camera::rotateOx(GLfloat directie) {
	GLfloat unghi = rotationSpeed * deltaTime * directie;
	Matrix mRotateOX;
	mRotateOX.SetRotationX(unghi);
	Vector4 rotatedLocalUp = localUp * mRotateOX; //localUp
	up = rotatedLocalUp * worldMatrix;
	up = up.Normalize();
	Vector4 localTarget = Vector4(0.0f, 0.0f, -(target - position).Length(), 1.0f);
	Vector4 rotatedTarget = localTarget * mRotateOX;
	target = rotatedTarget * worldMatrix;
	updateWorldView();

}

void Camera::updateWorldView() {
	zAxis = -(target - position).Normalize();
	//up.y = 1.0;
	yAxis = up.Normalize();
	//yAxis = Vector4(0.0, 100.0, 0.0, 1.0).Normalize();
	//xAxis = zAxis.Cross(yAxis).Normalize();   //Cross nu exista in Vector4, exista doar in Vector3 .........................
	Vector3 xAxis3 = cToV3(xAxis);
	Vector3 yAxis3 = cToV3(yAxis);
	Vector3 zAxis3 = cToV3(zAxis);
	xAxis3 = zAxis3.Cross(yAxis3).Normalize();
	xAxis = cToV4(xAxis3, 0.0);

	Matrix R;
	R.m[0][0] = xAxis.x; R.m[0][1] = xAxis.y; R.m[0][2] = xAxis.z; R.m[0][3] = 0;
	R.m[1][0] = yAxis.x; R.m[1][1] = yAxis.y; R.m[1][2] = yAxis.z; R.m[1][3] = 0;
	R.m[2][0] = zAxis.x; R.m[2][1] = zAxis.y; R.m[2][2] = zAxis.z; R.m[2][3] = 0;
	R.m[3][0] = 0;       R.m[3][1] = 0;       R.m[3][2] = 0;       R.m[3][3] = 1;

	//Matrix T;
	Matrix T;
	T.SetTranslation(position.x, position.y, position.z);

	worldMatrix = R * T;
	T.SetTranslation(-position.x, -position.y, -position.z);
	R = R.Transpose();
	viewMatrix = T * R;
}

Vector3 Camera::cToV3(Vector4 a) {
	GLfloat x = a.x;
	GLfloat y = a.y;
	GLfloat z = a.z;
	Vector3 b; b.x = x; b.y = y; b.z = z;
	return b;
}
Vector4 Camera::cToV4(Vector3 a, GLfloat b) {
	GLfloat x = a.x;
	GLfloat y = a.y;
	GLfloat z = a.z;

	return Vector4(x , y, z, b);
}


Camera::~Camera() {
}