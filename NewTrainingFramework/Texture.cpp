#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "../Utilities/memDbg.h"
#include "Shaders.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include <string>
#include "Texture.h"

using namespace std;

Texture::Texture(){
	idTexture = 0;
}

void Texture::loadTexture() {
	
	glGenTextures(1, &idTexture);
	GLuint glTextureType;
	if (tr->type == "2d") {
		glTextureType = GL_TEXTURE_2D;
		
	}
	else if(tr->type == "cube"){
		glTextureType = GL_TEXTURE_CUBE_MAP;
	}

	glBindTexture(glTextureType, idTexture);


	
	if (tr->wrap_s == "CLAMP_TO_EDGE") {
		glTexParameteri(glTextureType, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(glTextureType, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	}
	else if (tr->wrap_s == "REPEAT") {
		glTexParameteri(glTextureType, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(glTextureType, GL_TEXTURE_WRAP_T, GL_REPEAT);
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	
	
	GLint width, height, bpp;

	//const char* link2 = tr->path.c_str();
	GLchar* array_pixeli = LoadTGA(tr->path.c_str(), &width, &height, &bpp);

	GLuint textureRGB;

	if (bpp == 24) {
		textureRGB = GL_RGB;
	}
	else {
		textureRGB = GL_RGBA;
	}


	if (tr->type == "2d") {
		glTexImage2D(GL_TEXTURE_2D, 0, textureRGB, width, height, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)array_pixeli);

	}
	else if(tr->type == "cube"){


		
		GLchar* buffer = new GLchar[width/4 * height /3 * (bpp /8)];

		int offSetWPX = (2 * (width / 4)) * (bpp / 8);
		int offSetHPX = height / 3;
		int offSetWNX = 0;
		int offSetHNX = height / 3;

		int offSetWPY = (width / 4) * (bpp / 8);
		int offSetHPY = 0;
		int offSetWNY =  (width / 4) * (bpp / 8);
		int offSetHNY = 2 * (height / 3);

		int offSetWPZ = (width / 4) * (bpp / 8);
		int offSetHPZ = height / 3;
		int offSetWNZ = (3 * (width / 4)) * (bpp / 8);
		int offSetHNZ = height / 3;


		//------------PX---------------
		int k = 0;
		for (int i = 0; i < height / 3; i++) {
			for (int j = 0; j < (width * (bpp / 8)) / 4; j++) {
				buffer[k] = array_pixeli[offSetWPX + offSetHPX * (bpp / 8) * width + (i * width * (bpp / 8)) + j];
				k += 1;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, textureRGB, width / 4, height / 3, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)buffer);


		//-----------NX------------------
		k = 0;
		for (int i = 0; i < height / 3; i++) {
			for (int j = 0; j < (width * (bpp/8)) /4; j++) {
				buffer[k] = array_pixeli[offSetWNX + offSetHNX * (bpp/8) * width + (i * width * (bpp / 8)) + j];
				k += 1;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, textureRGB, width / 4, height / 3, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)buffer);
		

		//-----------PY---------------------
		k = 0;
		for (int i = 0; i < height / 3; i++) {
			for (int j = 0; j < (width * (bpp / 8)) / 4; j++) {
				buffer[k] = array_pixeli[offSetWPY + offSetHPY * (bpp / 8) * width + (i * width * (bpp / 8)) + j];
				
				k += 1;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, textureRGB, width / 4, height / 3, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)buffer);
		

		//-----------NY----------------------
		k = 0;
		for (int i = 0; i < height / 3; i++) {
			for (int j = 0; j < (width * (bpp / 8)) / 4; j++) {
				buffer[k] = array_pixeli[offSetWNY + offSetHNY * (bpp / 8) * width + (i * width * (bpp / 8)) + j];
				k += 1;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, textureRGB, width / 4, height / 3, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)buffer);
		

		//------------PZ----------------------
		k = 0;
		for (int i = 0; i < height / 3; i++) {
			for (int j = 0; j < (width * (bpp / 8)) / 4; j++) {
				buffer[k] = array_pixeli[offSetWPZ + offSetHPZ * (bpp / 8) * width + (i * width * (bpp / 8)) + j];
				k += 1;
			}
		}
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, textureRGB, width / 4, height / 3, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)buffer);
		

		//--------------NZ---------------------
		k = 0;
		for (int i = 0; i < height / 3; i++) {
			for (int j = 0; j < (width * (bpp / 8)) / 4; j++) {
				buffer[k] = array_pixeli[offSetWNZ + offSetHNZ * (bpp / 8) * width + (i * width * (bpp / 8)) + j];
				k += 1;
			}
		}



		glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, textureRGB, width / 4, height / 3, 0, textureRGB, GL_UNSIGNED_BYTE, (const GLvoid*)buffer);
		


		
	
	}


	glGenerateMipmap(glTextureType);
	glTexParameteri(glTextureType, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); //GL_LINEAR | GL_LINEAR_MIPMAP_LINEAR
	glTexParameteri(glTextureType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	
	delete[] array_pixeli;
}
Texture::~Texture() {

}

