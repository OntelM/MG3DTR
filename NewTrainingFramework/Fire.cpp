#include "stdafx.h"
#include "../Utilities/utilities.h"
#include "Fire.h"
#include <time.h> 

Fire::Fire() {};
void Fire::Draw(int w) {




	glUseProgram(myShaders->program);
	SendData();

	
	/*if (myShaders->fireMask != -1) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture[1]->idTexture);
		glUniform1i(myShaders->fireMask, 1);
	}
	if (myShaders->displacementMap != -1) {
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, texture[2]->idTexture);
		glUniform1i(myShaders->displacementMap, 2);
	}*/

	if (myShaders->uTime != -1) {
		glUniform1f(myShaders->uTime, time); // transmitere timp
	}
	if (myShaders->dispMax != -1) {
		glUniform1f(myShaders->dispMax, dispMax);
	}





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



	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);




	
}
void Fire::Update(GLfloat deltaTime) {

	Matrix trans, rotx, roty, rotz, rot, scal;
	trans.SetTranslation(position);
	rotx.SetRotationX(rotation.x);
	roty.SetRotationY(rotation.y);
	rotz.SetRotationZ(rotation.z);
	rot = rotx * roty * rotz;
	scal.SetScale(scale);
	M = scal * rot * trans;


	clock_t t = clock();
	char buffer[64];
	snprintf(buffer, sizeof buffer, "%f", (float)t / CLOCKS_PER_SEC);
	int length = 0;
	int secunde = (int)t / CLOCKS_PER_SEC;
	while (secunde /= 10) {
		length++;
	}

	char *d = buffer + length;
	time = atof(d) / 1;
	//float fireSpeed = 0.9;
	//time = deltaTime ;
}