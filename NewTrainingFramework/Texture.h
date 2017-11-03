#pragma once
#include "../Utilities/utilities.h"
#include "Structuri.h"

using namespace std;



class Texture {
public:
	TextureResource* tr;
	string file;
	GLuint idTexture;
	void loadTexture();
	Texture();
	~Texture();
	char* ExtractFace(int offx, int offy, char* buffer, int width, int bpp);

};

