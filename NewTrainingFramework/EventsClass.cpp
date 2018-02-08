#include "stdafx.h"
#include "EventsClass.h"
#include "SceneManager.h"
#include <algorithm>

using namespace std;

EventsClass::EventsClass() {
	firstEventC = NULLEVENT;
	firstEventN = NULLEVENT;
	eveniment1 = NULLEVENT;
	eveniment2 = NULLEVENT;
}
void EventsClass::Action() {

}
string terrainS = "Terrain"; string skyBoxS = "skyBox";
void EventsClass::Collision(int id) {
	idSound = id;
	map<GLint, SceneObject*> obj = SceneManager::getInstance()->objectMap;
	for (map<GLint, SceneObject*>::iterator objA = obj.begin(); objA != obj.end(); objA++) {
		for (map<GLint, SceneObject*>::iterator objB = obj.begin(); objB != obj.end(); objB++) {

			if (objA->second->id != objB->second->id && (objA->second->type != terrainS) && (objB->second->type != terrainS) &&
				(objA->second->type != skyBoxS) && (objB->second->type != skyBoxS)) {



				if (objA->second->AABB[0].x <= objB->second->AABB[1].x && objA->second->AABB[1].x >= objB->second->AABB[0].x &&
					objA->second->AABB[0].y <= objB->second->AABB[1].y && objA->second->AABB[1].y >= objB->second->AABB[0].y &&
					objA->second->AABB[0].z <= objB->second->AABB[1].z && objA->second->AABB[1].z >= objB->second->AABB[0].z) {
					
					
					pair<int, int> objC = pair<int, int>(objA->second->id, objB->second->id);
					if (std::find(objColl.begin(), objColl.end(), objC) == objColl.end()) {
						objColl.push_back(objC);
						SceneManager::getInstance()->soundMap[idSound]->play();
						cout << objA->second->name << ", " << objB->second->name << endl;
					}
					
					

					
				}
				else {

					pair<int, int> objC = pair<int, int>(objA->second->id, objB->second->id);
					if (std::find(objColl.begin(), objColl.end(), objC) != objColl.end()) {
						objColl.erase(std::remove(objColl.begin(), objColl.end(), objC), objColl.end());
					}

				}

			}
		}
	}
}
void EventsClass::playbackgroundSound(int n) {
	if (ver != 1) {
		SceneManager::getInstance()->soundMap[n]->play();
		ver = 1;
	}
}