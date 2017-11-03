#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "../Utilities/memDbg.h"
#include "Shaders.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <string>
#include "Sound.h"
Sound::Sound() {};
void Sound::LoadSound() {
	ResourceManager::getInstance()->fmodSystem->createSound(soR->path.c_str(), FMOD_LOOP_OFF, 0, &soundA);
}
void Sound::play() {
	ResourceManager::getInstance()->fmodSystem->playSound(soundA, 0, false, 0);
}