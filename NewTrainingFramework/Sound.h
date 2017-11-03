#pragma once
#include "../Utilities/utilities.h"
#include "Structuri.h"
#include <vector>
#include "Vertex.h"
#include "FMOD\fmod.h"
#include "FMOD\fmod.hpp"
class Sound {
public:
	Sound();
	int id;
	string path;
	string name;
	SoundResource* soR;
	void LoadSound();
	FMOD::Sound* soundA;

	void play();
};