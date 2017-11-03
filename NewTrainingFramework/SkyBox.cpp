#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "SkyBox.h"
#include "Camera.h"
#include "SceneManager.h"


SkyBox::SkyBox() {};
void SkyBox::SkyBox::Update(GLfloat deltaTime) {
	Camera* cam = SceneManager::getInstance()->cameraMap[followingCamera];
	Matrix trans, rotx, roty, rotz, rot, scal;
	trans.SetTranslation(position);
	rotx.SetRotationX(rotation.x);
	roty.SetRotationY(rotation.y);
	rotz.SetRotationZ(rotation.z);
	rot = rotx * roty * rotz;
	scal.SetScale(scale);
	M = scal * rot * trans;

	position = Vector3(cam->cToV3(cam->position));
	position.y = cam->position.y;
}