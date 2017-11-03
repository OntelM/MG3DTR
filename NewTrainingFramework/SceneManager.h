#pragma once
#include "../Utilities/utilities.h"
#include "Camera.h"
#include "SceneObject.h"
#include <map>
#include "Model.h"
#include "Light.h"
#include "Sound.h"
#include "EventsClass.h"
#include "TextRendering.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H

using namespace std;

class SceneManager {
protected:
	SceneManager();
	static SceneManager* spInstance;
public:
	static SceneManager* getInstance();
	

	map<GLint, SceneObject*> objectMap;
	map<GLint, Camera*> cameraMap;
	map<GLint, Light*> lightMap; 
	map<GLint, Sound*> soundMap;
	EventsClass* eveniment;
	TextRendering* textNou;


	~SceneManager();

	float rFog, RFog, rFogFull;
	Vector3 colorFog;
	void wired();
	int w;

	void Init();
	void Draw(GLfloat deltaTime);
	void Update(GLfloat deltaTime);

	
	
};


