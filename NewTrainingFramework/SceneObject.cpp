#include "stdafx.h"
#include <iostream>
#include <string>
#include <map>
#include "Globals.h"
#include "../Utilities/memDbg.h"
#include "Vertex.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "SceneObject.h"
#include "Terrain.h"


using namespace std;
SceneObject::SceneObject() {
	sens = 1;
	inc = 0;
	unghi = 0;
	AABB = new Vector3[2];
	
};
SceneObject::~SceneObject() {};


GLfloat delta = 0;
GLfloat deltaX = 0;
GLfloat deltaY = 0;
GLfloat deltaZ = 0;
void SceneObject::Draw(int w) {

		glUseProgram(myShaders->program);
		

		SendData();

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		if (w == 1) {
			glDrawElements(GL_TRIANGLES, model->nrIndici, GL_UNSIGNED_SHORT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		else if (w == 2) {
			glDrawElements(GL_LINES, model->nrIndiciWired, GL_UNSIGNED_SHORT, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}





		
		
		

}


void SceneObject::Update(GLfloat deltaTime) {

	//Camera* cam = SceneManager::getInstance()->cameraMap[followingCamera];
	Matrix trans, rotx, roty, rotz, rot, scal;
	trans.SetTranslation(position);
	rotx.SetRotationX(rotation.x);
	roty.SetRotationY(rotation.y);
	rotz.SetRotationZ(rotation.z);
	rot = rotx * roty * rotz;
	scal.SetScale(scale);
	M = scal * rot * trans;


	//-----------Normal Obj-------------------
	if (typeTrajectory == T_LINEAR) {
		
		endPoint = pointPosition[inc + sens];
		if ((endPoint - startPoint).Dot(endPoint - position) > 0) {
			position += (endPoint - startPoint).Normalize() * deltaTime * speed;
		}
		else if (iterationTrajectory != 0) {
			if (directionTrajectory == "normal") {
				position = pointPosition[0];
				if (iterationTrajectory != -1) {
					iterationTrajectory -= 1;
				}
			}
			else if(directionTrajectory == "alternate"){
				sens = -sens;
				if (sens == -1) {
					position = pointPosition[1];
					startPoint = pointPosition[1];
					inc = 1;
				}
				else if(sens == 1){
					startPoint = pointPosition[0];
					position = pointPosition[0];
					inc = 0;
				}
				rotation.y += PI;
				if (iterationTrajectory != -1) {
					iterationTrajectory -= 1;
				}
			}
		}
	}
	else if (typeTrajectory == T_LINE_STRIP || typeTrajectory == T_LINE_LOOP) {


		if (pointSize > 0) {

			endPoint = pointPosition[inc + sens];

			if ((endPoint - startPoint).Dot(endPoint - position) > 0) {
				position += (endPoint - startPoint).Normalize() * deltaTime * speed;
			}
			else {
				pointSize -= 1;
				position = endPoint;
				if (pointSize > 0) {
					startPoint = endPoint;
					inc += sens;
				}
			}

		}
	 if ((pointSize == 0) && (iterationTrajectory != 0)){
		 
			 if (directionTrajectory == "normal") {
				 inc = 0;
				 pointSize = pointPosition.size() - 1;
				 startPoint = pointPosition[inc];
				 position = startPoint;
				 if (iterationTrajectory != -1) {
					 iterationTrajectory -= 1;
				 }
			 }
			 else if (directionTrajectory == "alternate") {
				 if (sens == 1) {
					 inc = pointPosition.size() - 1;
				 }
				 else if (sens == -1) {
					 inc = 0;
				 }
				 sens = -sens;

				 pointSize = pointPosition.size() - 1;
				 startPoint = pointPosition[inc];
				 if (iterationTrajectory != -1) {
					 iterationTrajectory -= 1;
				 }
				 rotation.y += PI;
			 }
		}
	}
	else if (typeTrajectory == T_CIRCLE) {
		if (unghi > (2 * PI)) {
			unghi = unghi - (2 * PI);
		}
		unghi += speed * deltaTime;

		Matrix scaleM, RinitX, RinitY, RinitZ, Traza, Ry, RplaneX, RplaneZ, T;
		

		scaleM.SetScale(scale);
		RinitX.SetRotationX(rotation.x);
		RinitY.SetRotationY(rotation.y);
		RinitZ.SetRotationZ(rotation.z);
		Traza.SetTranslation(0, 0, radius);

		Ry.SetRotationY(unghi);

		RplaneX.SetRotationX(rotPlane.x);
		RplaneZ.SetRotationZ(rotPlane.z);

		T.SetTranslation(center);
		
		M = scaleM * RinitX * RinitY * RinitZ * Traza * Ry * RplaneX * RplaneZ * T;

		int test = 1;

	}

	//-------------------------------------------------------------------------------------------------------------------------

	listVertex = new Vertex[model->nrVer];
	for (int i = 0; i < model->nrVer; i++) {
		Vector4 listVertexUpdate = Vector4(model->listVertex[i].pos.x, model->listVertex[i].pos.y, model->listVertex[i].pos.z, 1.0) * M;
		listVertex[i].pos = Vector3(listVertexUpdate.x, listVertexUpdate.y, listVertexUpdate.z);
	}
	


	xMin = listVertex[0].pos.x;
	yMin = listVertex[0].pos.y;
	zMin = listVertex[0].pos.z;

	xMax = listVertex[0].pos.x;
	yMax = listVertex[0].pos.y;
	zMax = listVertex[0].pos.z;


	for (int i = 1; i < model->nrVer; i++) {
		if (listVertex[i].pos.x < xMin) {
			xMin = listVertex[i].pos.x;
		}
		if (listVertex[i].pos.y < yMin) {
			yMin = listVertex[i].pos.y;
		}
		if (listVertex[i].pos.z < zMin) {
			zMin = listVertex[i].pos.z;
		}

		if (listVertex[i].pos.x > xMax) {
			xMax = listVertex[i].pos.x;
		}
		if (listVertex[i].pos.y > yMax) {
			yMax = listVertex[i].pos.y;
		}
		if (listVertex[i].pos.z > zMax) {
			zMax =listVertex[i].pos.z;
		}
	}
	delete[] listVertex;

	
	AABB[0] = Vector3(xMin, yMin, zMin);
	AABB[1] = Vector3(xMax, yMax, zMax);



	

}
void SceneObject::SendData() {



	glBindBuffer(GL_ARRAY_BUFFER, model->vboId);


	if (w == 1) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->iboId);
	}
	else if (w == 2) {
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->wiredIboId);
	}




	if (myShaders->positionAttribute != -1) //daca exista variabila a_posL in vs
	{
		glEnableVertexAttribArray(myShaders->positionAttribute); //porneste o lista de atribute generice vertex
		glVertexAttribPointer(myShaders->positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //defineste o multime de date vertex
	}
	if (myShaders->normalLoc != -1) {
		glEnableVertexAttribArray(myShaders->normalLoc);
		glVertexAttribPointer(myShaders->normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(2 * sizeof(Vector3)));
	}
	if (myShaders->binorm != -1) {
		glEnableVertexAttribArray(myShaders->binorm);
		glVertexAttribPointer(myShaders->binorm, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(Vector3)));
	}
	if (myShaders->tgt != -1) {
		glEnableVertexAttribArray(myShaders->tgt);
		glVertexAttribPointer(myShaders->tgt, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(4 * sizeof(Vector3)));
	}


	if (myShaders->colorAttribute != -1) {
		glEnableVertexAttribArray(myShaders->colorAttribute);
		glVertexAttribPointer(myShaders->colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
	}





	Matrix view = SceneManager::getInstance()->cameraMap[followingCamera]->viewMatrix;
	GLfloat ratio = (GLfloat)Globals::screenWidth / Globals::screenHeight;
	Matrix perspective;

	Camera* cam = SceneManager::getInstance()->cameraMap[followingCamera];

	perspective.SetPerspective(cam->fov, ratio, cam->vnear, cam->vfar);
	Matrix MVP = M * view * perspective;



	if (myShaders->mvpUniform != -1) {
		glUniformMatrix4fv(myShaders->mvpUniform, 1, GL_FALSE, (GLfloat*)MVP.m); //specifica valorile a unei variabile imoform pentru obiectul provram curent
	}
	if (myShaders->modelUniform != -1) {
		glUniformMatrix4fv(myShaders->modelUniform, 1, GL_FALSE, (GLfloat*)M.m); //specifica valorile a unei variabile imoform pentru obiectul provram curent
	}
	if (myShaders->viewUniform != -1) {
		glUniformMatrix4fv(myShaders->viewUniform, 1, GL_FALSE, (GLfloat*)view.m); //specifica valorile a unei variabile imoform pentru obiectul provram curent
	}
	if (myShaders->projectionUniform != -1) {
		glUniformMatrix4fv(myShaders->projectionUniform, 1, GL_FALSE, (GLfloat*)perspective.m); //specifica valorile a unei variabile imoform pentru obiectul provram curent
	}
	if (myShaders->uvAttribute != -1) {
		glEnableVertexAttribArray(myShaders->uvAttribute);
		glVertexAttribPointer(myShaders->uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
	}

	for (int i = 0; i < texture.size(); i++) {
		if (texture[i]->tr->type == "2d") {
			if (myShaders->texture[i] != -1) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, texture[i]->idTexture);
				glUniform1i(myShaders->texture[i], i);
			}
		}
		else {
			if (myShaders->texture[i] != -1) {
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_CUBE_MAP, texture[i]->idTexture);
				glUniform1i(myShaders->texture[i], i);
			}
		}
	}


	

	
	if (myShaders->posLight != -1) {
		Vector3 posLight = SceneManager::getInstance()->lightMap[0]->position;
		glUniform3f(myShaders->posLight, posLight.x, posLight.y, posLight.z);
		int testtt = 0;
	}
	if (myShaders->ambientalColor != -1) {
		Vector3 ambiental = SceneManager::getInstance()->lightMap[0]->ambiental;
		glUniform3f(myShaders->ambientalColor, ambiental.x, ambiental.y, ambiental.z);
		int testtt = 0;
	}
	if (myShaders->diffuseColor != -1) {
		Vector3 difuseColor = SceneManager::getInstance()->lightMap[0]->diffuseColor;
		glUniform3f(myShaders->diffuseColor, difuseColor.x, difuseColor.y, difuseColor.z);
		int testtt = 0;
	}
	if (myShaders->specularColor != -1) {
		Vector3 specularColor = SceneManager::getInstance()->lightMap[0]->specularColor;
		glUniform3f(myShaders->specularColor, specularColor.x, specularColor.y, specularColor.z);
	}
	if (myShaders->specCoef != -1) {
		glUniform1f(myShaders->specCoef, SceneManager::getInstance()->lightMap[0]->specCoef);
	}
	if (myShaders->diffCoef != -1) {
		glUniform1f(myShaders->diffCoef, SceneManager::getInstance()->lightMap[0]->diffCoef);
	}
	if (myShaders->specPower != -1) {
		glUniform1f(myShaders->specPower, SceneManager::getInstance()->lightMap[0]->specPower);
	}
	if (myShaders->shininess != -1) {
		glUniform1f(myShaders->shininess, SceneManager::getInstance()->lightMap[0]->shininess);
	}
	if (myShaders->ratio != -1) {
		glUniform1f(myShaders->ratio, SceneManager::getInstance()->lightMap[0]->ratio);
	}
	if (myShaders->attenuation != -1) {
		glUniform1f(myShaders->attenuation, SceneManager::getInstance()->lightMap[0]->attenuation);
	}
	if (myShaders->type != -1) {
		glUniform1f(myShaders->type, SceneManager::getInstance()->lightMap[0]->type);
	}







	if (myShaders->cam != -1) {
		glUniform3f(myShaders->cam, cam->position.x, cam->position.y, cam->position.z);
	}
	if (myShaders->rr != -1) {
		glUniform1f(myShaders->rr,SceneManager::getInstance()->rFog);
	}
	if (myShaders->rR != -1) {
		glUniform1f(myShaders->rR, SceneManager::getInstance()->RFog);
	}
	if (myShaders->rFog != -1) {
		glUniform1f(myShaders->rFog, SceneManager::getInstance()->rFogFull);
	}
	if (myShaders->colorFog != -1) {
		Vector3 colorFog = SceneManager::getInstance()->colorFog;
		glUniform3f(myShaders->colorFog, colorFog.x, colorFog.y, colorFog.z);
	}



	
	


}
