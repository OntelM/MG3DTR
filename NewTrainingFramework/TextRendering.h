#pragma once
#include "../Utilities/utilities.h"
#include "Globals.h"
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_STROKER_H



class TextRendering {
public:
	TextRendering();

	int id;
	char* value;
	Shaders* shader;
	Texture* texture;
	GLuint vboId, vbo;
	void Init();
	void Draw();
	void render_text(const char *text, float x, float y, float sx, float sy);
	void display();

	FT_Library ft;
	FT_Face face;
	FT_GlyphSlot g;

};