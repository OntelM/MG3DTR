#include "stdafx.h"
#include "SceneObject.h"
#include "Terrain.h"
#include "SceneManager.h"
#include "Globals.h"
#include "ResourceManager.h"

Terrain::Terrain() {
	f1 = 0;
	f2 = 0;
}
void Terrain::generate() {
	
	model = new Model();
	nrVer = (nrCel + 1) * (nrCel + 1);
	nrInd = ((nrCel * nrCel) * 2) * 3;
	listVertex = new Vertex[nrVer];
	GLuint* listIndicis = new GLuint[nrInd];
	

	offsetY = 0;
	int nrV = 0;



	

	for (int i = 0; i <= nrCel; i++) {
		for (int j = 0; j <= nrCel; j++) {
			GLfloat z = cam->position.z - ((nrCel / 2)*dimCel) + (i * dimCel);
			GLfloat x = cam->position.x - ((nrCel / 2)*dimCel) + (j * dimCel);

			listVertex[nrV].pos.x = x;		listVertex[nrV].pos.y = offsetY;	listVertex[nrV].pos.z = z;
			listVertex[nrV].norm.x = 0;		listVertex[nrV].norm.y = 1;		listVertex[nrV].norm.z = 0;

			listVertex[nrV].uv.x = j; listVertex[nrV].uv.y = i;

			listVertex[nrV].uvt.x = (float)j / nrCel; listVertex[nrV].uvt.y = (float)i / nrCel;

			nrV += 1;
		}
	}


		int nrI = 0;
		for (int i = 0; i < nrCel; i++) {
			for (int j = 0; j < nrCel; j++) {

				GLuint a = ((nrCel + 1) * i) + j;
				GLuint b = ((nrCel + 1) * i) + j + 1;
				GLuint c = nrCel * (i + 1) + i + j + 1;
				GLuint d = nrCel * (i + 1 ) + i + j + 2;


				listIndicis[nrI] = a; listIndicis[nrI + 1] = b; listIndicis[nrI + 2] = c;
				listIndicis[nrI + 3] = b; listIndicis[nrI + 4] = c; listIndicis[nrI + 5] = d;


				
				
				nrI += 6;
			}
		}




nrWired = nrInd * 2;
GLuint* listWired = new GLuint[nrWired];
int k = 0;
for (int i = 0; i < nrInd; i += 3) {
	//-----------------Triunghi------------------------------------
	listWired[k] = listIndicis[i];
	k++;
	listWired[k] = listIndicis[i + 1];
	k++;
	listWired[k] = listIndicis[i + 1];
	k++;
	listWired[k] = listIndicis[i + 2];
	k++;
	listWired[k] = listIndicis[i + 2];
	k++;
	listWired[k] = listIndicis[i];
	k++;
	//-------------------end---------------------------------------
}

glGenBuffers(1, &vboId);
glBindBuffer(GL_ARRAY_BUFFER, vboId);
glBufferData(GL_ARRAY_BUFFER, nrVer * sizeof(Vertex), listVertex, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

glGenBuffers(1, &iboId);
glBindBuffer(GL_ARRAY_BUFFER, iboId);
glBufferData(GL_ARRAY_BUFFER, nrInd * sizeof(GLuint), listIndicis, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

glGenBuffers(1, &wiredIboId);
glBindBuffer(GL_ARRAY_BUFFER, wiredIboId);
glBufferData(GL_ARRAY_BUFFER, nrWired * sizeof(GLuint), listWired, GL_STATIC_DRAW);
glBindBuffer(GL_ARRAY_BUFFER, 0);

//------------------------------------------


delete[] listIndicis;
delete[] listWired;






model->nrIndici = nrInd;
model->nrIndiciWired = nrWired;
model->iboId = iboId;
model->vboId = vboId;
model->wiredIboId = wiredIboId;

}
void Terrain::Draw(int w) {
	glUseProgram(myShaders->program);

	SendData();

	//if (myShaders->grassU != -1) {
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, texture[0]->idTexture);
	//	glUniform1i(myShaders->grassU, 0);
	//}
	//if (myShaders->rockU != -1) {
	//	glActiveTexture(GL_TEXTURE1);
	//	glBindTexture(GL_TEXTURE_2D, texture[1]->idTexture);
	//	glUniform1i(myShaders->rockU, 1);
	//}
	//if (myShaders->dirtU != -1) {
	//	glActiveTexture(GL_TEXTURE2); // Texture unit 0
	//	glBindTexture(GL_TEXTURE_2D, texture[2]->idTexture);
	//	glUniform1i(myShaders->dirtU, 2);
	//}
	//if (myShaders->BlendMapU != -1) {
	//	glActiveTexture(GL_TEXTURE3);
	//	glBindTexture(GL_TEXTURE_2D, texture[3]->idTexture);
	//	glUniform1i(myShaders->BlendMapU, 3);
	//}


	if (myShaders->uvtAttribute != -1) {
		glEnableVertexAttribArray(myShaders->uvtAttribute);
		glVertexAttribPointer(myShaders->uvtAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3) + sizeof(Vector2)));
	}

	if (myShaders->heightTerrainU != -1)
	{
		glUniform3f(myShaders->heightTerrainU, inaltimi.x, inaltimi.y, inaltimi.z);
		int test = 3;
	}




	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (w == 1) {
		glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_INT, 0);
	}
	else if (w == 2) {
		glDrawElements(GL_LINES, model->nrIndiciWired, GL_UNSIGNED_INT, 0);

	}



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}
void Terrain::Update(GLfloat deltaTime) {
	Matrix trans, rotx, roty, rotz, rot, scal;



	int test = 0;
	if ((cam->position.z - position.z) < -dimCel){
		position.z -= dimCel;
		f1 = 0;
		f2 = -1;
		test = 1;
	}
	else if ((cam->position.z - position.z) > dimCel) {
		position.z += dimCel;
		f1 = 0;
		f2 = 1;
		test = 1;
	}
	else if ((cam->position.x - position.x) < -dimCel) {
		position.x -= dimCel;
		f1 = -1;
		f2 = 0;
		test = 1;
	}
	else if ((cam->position.x - position.x) > dimCel) {
		position.x += dimCel;
		f1 = 1;
		f2 = 0;
		test = 1;
	}


	if (test == 1) {
		test = 0;


		for (int i = 0; i < nrVer; i++) {

				listVertex[i].uvt.x += f1/nrCel; listVertex[i].uvt.y += f2 / nrCel;

		}


		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, nrVer * sizeof(Vertex), listVertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}
	
	trans.SetTranslation(position);
	rotx.SetRotationX(rotation.x);
	roty.SetRotationY(rotation.y);
	rotz.SetRotationZ(rotation.z);
	rot = rotx * roty * rotz;
	scal.SetScale(scale);
	M = scal * rot * trans;

}