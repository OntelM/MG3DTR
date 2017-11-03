#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "../Utilities/memDbg.h"
#include "Shaders.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <string>
#include "TextRendering.h"

TextRendering::TextRendering() {};



void TextRendering::Draw() {


	if (FT_Init_FreeType(&ft)) {
		fprintf(stderr, "Could not init freetype library\n");
	}


	if (FT_New_Face(ft, (texture->tr->path).c_str(), 0, &face)) {
		fprintf(stderr, "Could not open font\n");
	}

	FT_Set_Pixel_Sizes(face, 0, 48);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER)) {
	fprintf(stderr, "Could not load character 'X'\n");
	}
	g = face->glyph;



	glUseProgram(shader->program);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//GLuint tex;
	

	/*Vertex *listVer = new Vertex[4];

	listVer[0].pos = Vector3(0.0, 0.0, 0.0);
	listVer[1].pos = Vector3(0.0, 1.0, 0.0);
	listVer[2].pos = Vector3(1.0, 1.0, 0.0);
	listVer[3].pos = Vector3(1.0, 0.0, 0.0);

	GLuint *listInd = new GLuint[6];
	listInd[0] = 0; listInd[1] = 1; listInd[2] = 2;
	listInd[3] = 2; listInd[4] = 1; listInd[5] = 4;




	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Vertex), listVer, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLushort), listInd, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	delete[] listVer;
	delete[] listInd;*/

	GLuint tex;
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(shader->uText, 0);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);


	GLuint vbo;
	glGenBuffers(1, &vbo);
	glEnableVertexAttribArray(shader->attribute_coord);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(shader->attribute_coord, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
	glVertexAttribPointer(shader->attribute_uv, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3) + sizeof(Vector2)));

	/*if (shader->attribute_coord != -1) {
		glEnableVertexAttribArray(shader->attribute_coord);
		glVertexAttribPointer(shader->attribute_coord, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	}*/
	/*if (shader->attribute_coord != -1) {
		glEnableVertexAttribArray(shader->attribute_uv);
		glVertexAttribPointer(shader->attribute_uv, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
	}*/
	/*if (shader->uText != -1) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->idTexture);
		glUniform1i(shader->uText, 0);
	}*/

	display();
}

void TextRendering::render_text(const char *text, float x, float y, float sx, float sy) {

	const char *p;

	for (p = text; *p; p++) {
		if (FT_Load_Char(face, *p, FT_LOAD_RENDER))
			continue;

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED_BITS,
			g->bitmap.width,
			g->bitmap.rows,
			0,
			GL_RED_BITS,
			GL_UNSIGNED_BYTE,
			g->bitmap.buffer
		);

		float x2 = x + g->bitmap_left * sx;
		float y2 = -y - g->bitmap_top * sy;
		float w = g->bitmap.width * sx;
		float h = g->bitmap.rows * sy;

		GLfloat box[4][4] = {
			{ x2,     -y2    , 0, 0 },
			{ x2 + w, -y2    , 1, 0 },
			{ x2,     -y2 - h, 0, 1 },
			{ x2 + w, -y2 - h, 1, 1 },
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof box, box, GL_DYNAMIC_DRAW);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		x += (g->advance.x / 64) * sx;
		y += (g->advance.y / 64) * sy;
	}
}
void TextRendering::display() {
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);

	GLfloat width = 0.2;

	GLfloat black[4] = { 0, 0, 0, 1 };
	glUniform4fv(width, 1, black);

	
	
	float sx = 2.0 / Globals::screenWidth;
	float sy = 2.0 / Globals::screenHeight;

	render_text("The Quick Brown Fox Jumps Over The Lazy Dog",
		-1 + 8 * sx, 1 - 50 * sy, sx, sy);
	//render_text("The Misaligned Fox Jumps Over The Lazy Dog",
	//	-1 + 8.5 * sx, 1 - 100.5 * sy, sx, sy);

	
}