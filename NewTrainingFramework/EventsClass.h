#pragma once
#include "stdafx.h"
#include <iostream>
#include "../Utilities/utilities.h"
#include "Sound.h"
#include "SceneObject.h"
#include <map>

enum EventsEnum {
	NULLEVENT, FIRSTEVENT, COLLISION
};
class EventsClass {
public:
	EventsClass();
	EventsEnum firstEventC;
	EventsEnum firstEventN;
	EventsEnum eveniment1;
	EventsEnum eveniment2;
	int idSound;
	map<int, Sound*> soundMap;
	void Collision(int id);
	void Action();
	vector<pair<int, int>> objColl;
	void playbackgroundSound(int n);
	int ver;
};