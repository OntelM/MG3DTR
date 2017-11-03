#pragma once
#include "../Utilities/utilities.h"
#include <map>
#include "Texture.h"
#include "Model.h"
#include "Shaders.h"
#include "Structuri.h"
#include "Sound.h"
#include "FMOD\fmod.h"
#include "FMOD\fmod.hpp"

using namespace std;

//----------------------------------------------ResourceManager--------------------------------------------------

class ResourceManager {
protected:
	ResourceManager();
	static ResourceManager* spInstance;
public:
	//ModelResource* mr;
	//ShaderResource* sr;
	//TextureResource* tr;
	//sau
	map<int, Model*> mrMap;
	map<int, Shaders*> srMap;
	map<int, Texture*> trMap;
	map<int, Sound*> soMap;
	

	map<int, ModelResource*> mrMapR;
	map<int, ShaderResource*> srMapR;
	map<int, TextureResource*> trMapR;
	map<int, SoundResource*> soMapR;
	int nrModels;
	
	Model* getModel(int id);
	Shaders* getShader(int id);
	Texture* getTexture(int id);
	Sound* getSound(int id);
	
	FMOD::System *fmodSystem;


	void Init();
	static ResourceManager* getInstance();
	//void freeResources();//eliberarea zonelor de memorie alocate
	void setNrModel(int nr);
	~ResourceManager();

};