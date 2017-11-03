#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "rapidxml.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"
#include "../Utilities/memDbg.h"
#include "Shaders.h"
#include "Vertex.h";
#include "SceneManager.h"
#include "ResourceManager.h"
#include <string>
#include "Terrain.h"
#include "ReflectSkyBox.h"
#include "Fire.h"
#include "SkyBox.h"




using namespace std;
using namespace rapidxml;

SceneManager::SceneManager(){
	w = 1;
}
SceneManager::~SceneManager() {}

SceneManager* SceneManager::spInstance = NULL;
SceneManager* SceneManager::getInstance() {
	if (!spInstance)
	{
		spInstance = new SceneManager();
		
	}
	return spInstance;
}

void SceneManager::Init() {
	Vector4 backgroundColor;
	eveniment = new EventsClass();
	xml_document<> doc;
	file<> xmlFile("../Resources/Xml/sceneManager.xml");
	doc.parse<0>(xmlFile.data());

	xml_node<> *node = doc.first_node(doc.first_node()->name());


	Camera* c;
	//--------------------------models/shaders/textures---------------------------------------
	

		backgroundColor.x = atof(node->first_node("backgroundColor")->first_node("r")->value());
		backgroundColor.y = atof(node->first_node("backgroundColor")->first_node("g")->value());
		backgroundColor.z = atof(node->first_node("backgroundColor")->first_node("b")->value());


		//------------------------------------------Camera----------------------------------------------------------------------

		for (xml_node<> *camNode = node->first_node("cameras")->first_node("camera"); camNode; camNode = camNode->next_sibling()) {
			
			c = new Camera;
			xml_node<> *posNode = camNode->first_node("position");
			c->position.x = atof(posNode->first_node("x")->value());
			c->position.y = atof(posNode->first_node("y")->value());
			c->position.z = atof(posNode->first_node("z")->value());
			c->position.w = 1;

			xml_node<> *rotNode = camNode->first_node("rotation");
			c->rotation.x = atof(rotNode->first_node("x")->value());
			c->rotation.y = atof(rotNode->first_node("y")->value());
			c->rotation.z = atof(rotNode->first_node("z")->value());
			c->rotation.w = 1;

			xml_node<> *tarNode = camNode->first_node("target");
			c->target.x = atof(tarNode->first_node("x")->value());
			c->target.y = atof(tarNode->first_node("y")->value());
			c->target.z = atof(tarNode->first_node("z")->value());
			c->target.w = 0;

			xml_node<> *upNode = camNode->first_node("up");
			c->up.x = atof(upNode->first_node("x")->value());
			c->up.y = atof(upNode->first_node("y")->value());
			c->up.z = atof(upNode->first_node("z")->value());
			c->up.w = 0;

			c->translationSpeed = atof(camNode->first_node("translationSpeed")->value());
			c->rotationSpeed = atof(camNode->first_node("rotationSpeed")->value());
			c->fov = atof(camNode->first_node("fov")->value());
			c->vfar = atof(camNode->first_node("far")->value());
			c->vnear = atof(camNode->first_node("near")->value());
			int idNode = atoi(camNode->first_attribute("id")->value());
			cameraMap[idNode] = c;
		}

		//------------------------------------Lumini---------------------------------------------------------------------------


		for (xml_node<> *lightNode = node->first_node("lights")->first_node("light"); lightNode; lightNode = lightNode->next_sibling())
		{
			Light* newLight = new Light();

			newLight->id = atoi(lightNode->first_attribute("id")->value());
			newLight->associatedObject = atoi(lightNode->first_node("associatedObject")->value());
			string type = lightNode->first_node("type")->value();
			if (type == "directional") {
				newLight->type = 0.0;
			}
			else if (type == "point") {
				newLight->type = 1.0;
			}
			
			newLight->specCoef = atof(lightNode->first_node("specCoef")->value());
			newLight->specPower = atof(lightNode->first_node("specPower")->value());
			newLight->diffCoef = atof(lightNode->first_node("diffCoef")->value());
			newLight->shininess = atof(lightNode->first_node("shininess")->value());
			newLight->attenuation = atof(lightNode->first_node("attenuation")->value());
			newLight->ratio = atof(lightNode->first_node("ratio")->value());

			newLight->position = Vector3(atof(lightNode->first_node("position")->first_node("x")->value()),
										atof(lightNode->first_node("position")->first_node("y")->value()),
										atof(lightNode->first_node("position")->first_node("z")->value()));

			newLight->ambiental = Vector3(atof(lightNode->first_node("ambiental")->first_node("r")->value()),
										atof(lightNode->first_node("ambiental")->first_node("g")->value()),
										atof(lightNode->first_node("ambiental")->first_node("b")->value()));

			newLight->diffuseColor = Vector3(atof(lightNode->first_node("diffuseColor")->first_node("r")->value()),
										atof(lightNode->first_node("diffuseColor")->first_node("g")->value()),
										atof(lightNode->first_node("diffuseColor")->first_node("b")->value()));

			newLight->specularColor = Vector3(atof(lightNode->first_node("specularColor")->first_node("r")->value()),
											atof(lightNode->first_node("specularColor")->first_node("g")->value()),
											atof(lightNode->first_node("specularColor")->first_node("b")->value()));
			

			lightMap[atoi(lightNode->first_attribute("id")->value())] = newLight;

			int asffff = 3;
		}

		//-------------------------------------------------------obiecte--------------------------------------------------------



		//verificare daca exisa nod 
		for (xml_node<> *objectNode = node->first_node("objects")->first_node("object"); objectNode; objectNode = objectNode->next_sibling())
		{

			SceneObject* objNou;
			
			
			
			if (!strcmp(objectNode->first_node("type")->value(), "Terrain")) {

				Terrain* teren = new Terrain();
				teren->nrCel = atoi(objectNode->first_node("nrCel")->value());
				teren->dimCel = atof(objectNode->first_node("dimCel")->value());
				teren->inaltimi = Vector3(atof(objectNode->first_node("inaltimi")->first_node("r")->value()),
										  atof(objectNode->first_node("inaltimi")->first_node("g")->value()),
										  atof(objectNode->first_node("inaltimi")->first_node("b")->value()));
				int activeCam = atoi(objectNode->first_node("followingCamera")->first_node("cameras")->first_node("camera")->value());
				teren->cam = cameraMap[activeCam];
				teren->generate();


				objNou = (SceneObject*)teren;
			}
			else if (!strcmp(objectNode->first_node("type")->value(), "ReflectSkyBox")) {
				ReflectSkyBox* reflexteObj = new ReflectSkyBox();


				objNou = (SceneObject*)reflexteObj;
			}
			else if (!strcmp(objectNode->first_node("type")->value(), "fire")) {
				Fire* newFire = new Fire();


				objNou = (SceneObject*)newFire;
			}
			else if (!strcmp(objectNode->first_node("type")->value(), "skyBox")) {
				SkyBox* newSkyBox = new SkyBox();



				objNou = (SceneObject*)newSkyBox;
			}
			else {
				objNou = new SceneObject();
				
				
			}
			if (!strcmp(objectNode->first_node("model")->value(), "generated")) {

			}
			else {
				objNou->model = ResourceManager::getInstance()->getModel(atof(objectNode->first_node("model")->value()));
			}
				objNou->myShaders = ResourceManager::getInstance()->getShader(atoi(objectNode->first_node("shader")->value()));
				
				objNou->w = 1;

				objNou->id = atof(objectNode->first_attribute("id")->value());

				objNou->type = objectNode->first_node("type")->value();
				
				for (xml_node<> *textureNode = objectNode->first_node("textures")->first_node("texture"); textureNode; textureNode = textureNode->next_sibling())
				{
					objNou->texture.push_back(ResourceManager::getInstance()->getTexture(atoi(textureNode->first_attribute("id")->value())));
				}
				

				if (objectNode->first_node("depthTest") != NULL) {
					objNou->depthTest = objectNode->first_node("depthTest")->value();
				}
				if (objectNode->first_node("blend") != NULL) {
					objNou->blend = objectNode->first_node("blend")->value();
				}
				if (objectNode->first_node("name") != NULL) {
					objNou->name = objectNode->first_node("name")->value();
				}
				if (objectNode->first_node("dispMax") != NULL) {
					objNou->dispMax = atof(objectNode->first_node("dispMax")->value());
				}
				

				objNou->position.x = atof(objectNode->first_node("position")->first_node("x")->value());
				objNou->position.y = atof(objectNode->first_node("position")->first_node("y")->value());
				objNou->position.z = atof(objectNode->first_node("position")->first_node("z")->value());

				objNou->pointPosition.push_back(Vector3(atof(objectNode->first_node("position")->first_node("x")->value()),
														atof(objectNode->first_node("position")->first_node("y")->value()),
														atof(objectNode->first_node("position")->first_node("z")->value())));


				objNou->rotation.x = atof(objectNode->first_node("rotation")->first_node("x")->value());
				objNou->rotation.y = atof(objectNode->first_node("rotation")->first_node("y")->value());
				objNou->rotation.z = atof(objectNode->first_node("rotation")->first_node("z")->value());

				objNou->scale.x = atof(objectNode->first_node("scale")->first_node("x")->value());
				objNou->scale.y = atof(objectNode->first_node("scale")->first_node("y")->value());
				objNou->scale.z = atof(objectNode->first_node("scale")->first_node("z")->value());

				if (objectNode->first_node("selfRotateSpeed")->value() != NULL) {
					objNou->selfRotateSpeed = atof(objectNode->first_node("selfRotateSpeed")->value());
				}
				if (objectNode->first_node("lights") != NULL) {
					objNou->lights = atof(objectNode->first_node("lights")->value());
				}
				if (objectNode->first_node("followingCamera") != NULL) {
					objNou->followingCamera = atoi(objectNode->first_node("followingCamera")->first_node("cameras")->first_node("camera")->value());
				}
				

				if (objectNode->first_node("trajectory") != NULL) {
					objNou->startPoint = objNou->position;


					objNou->directionTrajectory = objectNode->first_node("trajectory")->first_attribute("direction")->value();
					objNou->speed = atof(objectNode->first_node("trajectory")->first_attribute("speed")->value());
					string altTr = "alternate", normTr = "normal";
					if (objectNode->first_node("trajectory")->first_attribute("direction")->value() == altTr) {
						if (atoi(objectNode->first_node("trajectory")->first_attribute("iteration")->value()) == -1) {
							objNou->iterationTrajectory = atoi(objectNode->first_node("trajectory")->first_attribute("iteration")->value());

						}
						else {
							objNou->iterationTrajectory = (2 * atoi(objectNode->first_node("trajectory")->first_attribute("iteration")->value())) - 1;
						}

					}
					else if (objectNode->first_node("trajectory")->first_attribute("direction")->value() == normTr) {
						if (atoi(objectNode->first_node("trajectory")->first_attribute("iteration")->value()) == -1) {
							objNou->iterationTrajectory = atoi(objectNode->first_node("trajectory")->first_attribute("iteration")->value());
						}
						else {
							objNou->iterationTrajectory = atoi(objectNode->first_node("trajectory")->first_attribute("iteration")->value()) - 1;
						}

					}





					if (!strcmp(objectNode->first_node("trajectory")->first_attribute("type")->value(), "linear")) {
						objNou->typeTrajectory = SceneObject::TypeTraj::T_LINEAR;
						for (xml_node<> *positionNode = objectNode->first_node("trajectory")->first_node("points")->first_node("point"); positionNode; positionNode = positionNode->next_sibling()) {
							objNou->pointPosition.push_back(Vector3(atof(positionNode->first_node("x")->value()),
								atof(positionNode->first_node("y")->value()),
								atof(positionNode->first_node("z")->value())));
						}
						objNou->pointSize = objNou->pointPosition.size() - 1;

					}
					else if (!strcmp(objectNode->first_node("trajectory")->first_attribute("type")->value(), "line_strip")) {
						objNou->typeTrajectory = SceneObject::TypeTraj::T_LINE_STRIP;
						for (xml_node<> *positionNode = objectNode->first_node("trajectory")->first_node("points")->first_node("point"); positionNode; positionNode = positionNode->next_sibling()) {
							objNou->pointPosition.push_back(Vector3(atof(positionNode->first_node("x")->value()),
								atof(positionNode->first_node("y")->value()),
								atof(positionNode->first_node("z")->value())));
						}
						objNou->pointSize = objNou->pointPosition.size() - 1;





					}
					else if (!strcmp(objectNode->first_node("trajectory")->first_attribute("type")->value(), "line_loop")) {
						objNou->typeTrajectory = SceneObject::TypeTraj::T_LINE_LOOP;
						for (xml_node<> *positionNode = objectNode->first_node("trajectory")->first_node("points")->first_node("point"); positionNode; positionNode = positionNode->next_sibling()) {
							objNou->pointPosition.push_back(Vector3(atof(positionNode->first_node("x")->value()),
								atof(positionNode->first_node("y")->value()),
								atof(positionNode->first_node("z")->value())));
						}
						objNou->pointPosition.push_back(Vector3(atof(objectNode->first_node("position")->first_node("x")->value()),
							atof(objectNode->first_node("position")->first_node("y")->value()),
							atof(objectNode->first_node("position")->first_node("z")->value())));
						objNou->pointSize = objNou->pointPosition.size() - 1;
					}
					else if (!strcmp(objectNode->first_node("trajectory")->first_attribute("type")->value(), "circle")) {
						objNou->typeTrajectory = SceneObject::TypeTraj::T_CIRCLE;
						xml_node<> *trajNode = objectNode->first_node("trajectory");
						objNou->center = Vector3(atof(trajNode->first_node("center")->first_node("x")->value()),
							atof(trajNode->first_node("center")->first_node("y")->value()),
							atof(trajNode->first_node("center")->first_node("z")->value()));
						objNou->radius = atoi(trajNode->first_node("radius")->value());
						xml_node<> * rotPlaneNode = objectNode->first_node("trajectory")->first_node("rotationPlane");
						objNou->rotPlane = Vector3(atof(rotPlaneNode->first_node("x")->value()),
							atof(rotPlaneNode->first_node("y")->value()),
							atof(rotPlaneNode->first_node("z")->value()));

					}

				}

				objectMap[objNou->id] = objNou;

		}


		

		xml_node<> *fogNode = node->first_node("fog");
			colorFog = Vector3(atof(fogNode->first_node("color")->first_node("r")->value()),
									atof(fogNode->first_node("color")->first_node("g")->value()),
									atof(fogNode->first_node("color")->first_node("b")->value()));

			rFog = atof(fogNode->first_node("r")->value());
			RFog = atof(fogNode->first_node("R")->value());
			rFogFull = atof(fogNode->first_node("Rfog")->value());


			xml_node<> *soundNode = node->first_node("sounds");

			for (xml_node<> *sounsEnumNode = soundNode->first_node("sound"); sounsEnumNode; sounsEnumNode = sounsEnumNode->next_sibling()) {
				Sound *soNou = new Sound();
				soNou = ResourceManager::getInstance()->getSound(atoi(sounsEnumNode->first_attribute("id")->value()));
				soNou->name = sounsEnumNode->first_node("name")->value();
				soundMap[soNou->id] = soNou;
			}
			xml_node<> *textNode = node->first_node("texts");
			textNou = new TextRendering();
			for (xml_node<> *textEnumNode = textNode->first_node("text"); textEnumNode; textEnumNode = textEnumNode->next_sibling()) {
				
				textNou->id = atoi(textEnumNode->first_attribute("id")->value());
				textNou->value = textEnumNode->first_node("value")->value();
				textNou->shader = ResourceManager::getInstance()->getShader(atoi(textEnumNode->first_node("shader")->value()));
				textNou->texture = ResourceManager::getInstance()->getTexture(atoi(textEnumNode->first_node("textures")->first_node("texture")->first_attribute("id")->value()));
			}

	textNou->Draw();
}
void SceneManager::Draw(GLfloat deltaTime) {
		cameraMap[1]->updateWorldView();
		for (map<GLint, SceneObject*>::iterator it = objectMap.begin(); it != objectMap.end(); ++it) {
			it->second->Draw(w);
		}
		
		//textNou->display();
}
void SceneManager::Update(GLfloat deltaTime) {
	for (map<GLint, SceneObject*>::iterator it = objectMap.begin(); it != objectMap.end(); ++it) {
		it->second->Update(deltaTime);
		it->second->w = w;
	}

	
	eveniment->Collision(2);
	eveniment->playbackgroundSound(1);
	
}
void SceneManager::wired() {
	if (w == 1) {
		w = 2;
	}
	else if(w == 2){
		w = 1;
	}

}