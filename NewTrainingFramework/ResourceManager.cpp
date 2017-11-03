#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "../Utilities/memDbg.h"
#include "ResourceManager.h"
#include <string>


using namespace rapidxml;
using namespace std;

ResourceManager::ResourceManager() {
	
}

ResourceManager* ResourceManager::spInstance = NULL;
ResourceManager* ResourceManager::getInstance() {
	if (!spInstance)
	{
		spInstance = new ResourceManager();
		
	}
	return spInstance;
}

void ResourceManager::Init() {
	


	xml_document<> doc;
	file<> xmlFile("../Resources/Xml/resourceManager.xml");
	doc.parse<0>(xmlFile.data());

	xml_node<> *node = doc.first_node(doc.first_node()->name());

	string addPrefix = "../";
	for (xml_node<> *modelNode = node->first_node("models")->first_node("model"); modelNode; modelNode = modelNode->next_sibling()) {
		ModelResource* mr2 = new ModelResource;
		mr2->idModel = atoi(modelNode->first_attribute("id")->value());
		mr2->path = addPrefix + modelNode->first_node("path")->value();
		mrMapR[mr2->idModel] = mr2;

	}
	for (xml_node<> *shaderNode = node->first_node("shaders")->first_node("shader"); shaderNode; shaderNode = shaderNode->next_sibling()) {
		ShaderResource* sr2 = new ShaderResource;
		sr2->idShader = atoi(shaderNode->first_attribute("id")->value());
		sr2->vs = addPrefix + shaderNode->first_node("vs")->value();
		sr2->fs = addPrefix + shaderNode->first_node("fs")->value();
		srMapR[sr2->idShader] = sr2;
	}
	for (xml_node<> *textureNode = node->first_node("textures")->first_node("texture"); textureNode; textureNode = textureNode->next_sibling()) {
		TextureResource* tr2 = new TextureResource;
		tr2->idTexture = atoi(textureNode->first_attribute("id")->value());
		tr2->type = textureNode->first_attribute("type")->value();
		tr2->path = addPrefix + textureNode->first_node("path")->value();
		tr2->min_filter = textureNode->first_node("min_filter")->value();
		tr2->mag_filter = textureNode->first_node("mag_filter")->value();
		tr2->wrap_s = textureNode->first_node("wrap_s")->value();
		tr2->wrap_t = textureNode->first_node("wrap_t")->value();
		trMapR[tr2->idTexture] = tr2;
	}

	if (FMOD::System_Create(&fmodSystem) != FMOD_OK) {
		cout << "nu avem sunete, vom afisa un mesaj de eroare";
	}
	else {
		fmodSystem->init(36, FMOD_INIT_NORMAL, NULL);//initializat la 36 de canale
		//cout << "initializat la 36 de canale";
	}


	for (xml_node<> *soundNode = node->first_node("sounds")->first_node("sound"); soundNode; soundNode = soundNode->next_sibling()) {
		SoundResource* sound = new SoundResource;
		sound->id = atoi(soundNode->first_attribute("id")->value());
		sound->path = addPrefix + soundNode->first_node()->value();

		soMapR[sound->id] = sound;
	}

}
Sound* ResourceManager::getSound(int id) {

	if (soMap.find(id) == soMap.end()) {
		Sound* so = new Sound;
		if (soMapR.find(id) != soMapR.end()) {
			so->soR = soMapR[id];
			so->id = soMapR[id]->id;
			so->path = soMapR[id]->path;
		}
		else {
			cout << "Modelul " << id << " nu a fost gasit \n";
			exit(0);
		}
		so->LoadSound();
		soMap[id] = so;
	}
	return soMap[id];
}
Model* ResourceManager::getModel(int id) {

	if (mrMap.find(id) == mrMap.end()) {
		Model* m;
		m = new Model;
		if (mrMapR.find(id) != mrMapR.end()) {
			m->mr = mrMapR[id];
		}
		else {
			cout << "Modelul " << id << " nu a fost gasit \n";
			exit(0);
		}
		m->LoadModel();
		mrMap[id] = m;
	}
	return mrMap[id];
}
Texture* ResourceManager::getTexture(int id) {
	if (trMap.find(id) == trMap.end()) {
		Texture* t = new Texture;
		if (trMapR.find(id) != trMapR.end()){
			t->tr = trMapR[id];
		}
		else {
			cout << "textura "<< id <<" nu a fost gasita \n";
			exit(0);
		}
		
		t->loadTexture();
		trMap[id] = t;
	}
	return trMap[id];
}
Shaders* ResourceManager::getShader(int id) {
	if (srMap.find(id) == srMap.end()) {
		Shaders* s;
		s = new Shaders;
		if (srMapR.find(id) != srMapR.end()) {
			s->sr = srMapR[id];
		}
		else {
			cout << "Shaderul " << id << " nu a fost gasit \n";
			exit(0);
		}
		
		s->Load();
		srMap[id] = s;
	}
	return srMap[id];
}

ResourceManager::~ResourceManager()
{

}


