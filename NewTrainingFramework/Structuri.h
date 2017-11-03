#pragma once
#include "stdafx.h"
#include <iostream>
#include "../Utilities/utilities.h"
#include <string>

using namespace std;

struct ModelResource {
public:
	GLuint idModel;
	string path;
};
struct ShaderResource {
public:
	GLuint idShader;
	string vs;
	string fs;
};
struct TextureResource {
public:
	GLuint idTexture;
	GLuint id;
	string type;
	string path;
	string min_filter;
	string mag_filter;
	string wrap_s;
	string wrap_t;
};
struct SoundResource {
public:
	int id;
	string path;
};