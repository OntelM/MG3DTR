#pragma once
#include "../Utilities/utilities.h"
#include "Structuri.h"

class Shaders 
{
public:
	ShaderResource* sr;
	GLuint idShader;
	GLuint program, vertexShader, fragmentShader;
	GLint positionAttribute, normalLoc, binorm, tgt, mvpUniform, modelUniform, colorAttribute, heightTerrainU;
	GLint nrCel, uvAttribute, uvtAttribute, BlendMapU, grassU, rockU, dirtU;
	GLint textureUniform, normalMap;
	GLint skyBoxTextureU;

	GLint fireMask, displacementMap;
	GLint uTime, dispMax;

	GLint rr, rR, rFog, colorFog;
	GLint viewUniform, projectionUniform;
	GLint ambientalColor, diffuseColor, specularColor, specCoef, diffCoef,
		shininess, ratio, cam, posLight, specPower, attenuation, type;

	GLuint attribute_coord, attribute_uv;
	GLint uText;


	GLint* texture;

	int Load();
	~Shaders();
};