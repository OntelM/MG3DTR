#include "stdafx.h"
#include "Shaders.h"

int Shaders::Load()
{
	vertexShader = esLoadShader(GL_VERTEX_SHADER, (char*)sr->vs.c_str());

	if ( vertexShader == 0 )
		return -1;

	fragmentShader = esLoadShader(GL_FRAGMENT_SHADER, (char*)sr->fs.c_str());

	if ( fragmentShader == 0 )
	{
		glDeleteShader( vertexShader );
		return -2;
	}

	program = esLoadProgram(vertexShader, fragmentShader);

	
	positionAttribute	= glGetAttribLocation(program, "a_posL");
	normalLoc			= glGetAttribLocation(program, "a_normalL");
	binorm				= glGetAttribLocation(program, "a_binormL");
	tgt					= glGetAttribLocation(program, "a_tgtL");

	colorAttribute		= glGetAttribLocation(program, "a_color");

	mvpUniform			= glGetUniformLocation(program, "u_MVP");
	modelUniform		= glGetUniformLocation(program, "Model");
	viewUniform			= glGetUniformLocation(program, "View");
	projectionUniform	= glGetUniformLocation(program, "Projection");


	uvAttribute			= glGetAttribLocation(program, "a_uv");
	uvtAttribute		= glGetAttribLocation(program, "a_uvt");
	
	
	

	uTime				= glGetUniformLocation(program, "u_Time");
	dispMax				= glGetUniformLocation(program, "u_DispMax");

	nrCel				= glGetUniformLocation(program, "nrCel");
	

	heightTerrainU		= glGetUniformLocation(program, "u_height");
	
	rr					= glGetUniformLocation(program, "u_r");
	rR					= glGetUniformLocation(program, "u_R");
	rFog				= glGetUniformLocation(program, "u_rFog");
	colorFog			= glGetUniformLocation(program, "u_colorFog");

	

	posLight			= glGetUniformLocation(program, "u_posLight");
	ambientalColor		= glGetUniformLocation(program, "u_ambiental");
	diffuseColor		= glGetUniformLocation(program, "u_diffuseColor");
	specularColor		= glGetUniformLocation(program, "u_specularColor");
	specCoef			= glGetUniformLocation(program, "u_specCoef");
	diffCoef			= glGetUniformLocation(program, "u_diffCoef");
	shininess			= glGetUniformLocation(program, "u_shininess");
	ratio				= glGetUniformLocation(program, "u_ratio");
	cam					= glGetUniformLocation(program, "u_cam");
	specPower			= glGetUniformLocation(program, "u_specPower");
	attenuation			= glGetUniformLocation(program, "u_attenuation");
	type				= glGetUniformLocation(program, "u_type");
	
	attribute_coord		= glGetAttribLocation(program, "coord");
	attribute_uv		= glGetAttribLocation(program, "coorduv");
	uText				= glGetUniformLocation(program, "tex");



	texture = new GLint[10];
	texture[0] = glGetUniformLocation(program, "t_texture_0");
	texture[1] = glGetUniformLocation(program, "t_texture_1");
	texture[2] = glGetUniformLocation(program, "t_texture_2");
	texture[3] = glGetUniformLocation(program, "t_texture_3");

	return 0;
}

Shaders::~Shaders()
{
	glDeleteProgram(program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

}