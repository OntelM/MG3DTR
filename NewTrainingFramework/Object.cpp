#include "stdafx.h"
#include <iostream>
#include "Object.h"
#include "Vertex.h"
#include "Globals.h"
#include "Shaders.h"
#include "Model2.h"
#include "Camera.h"
#include "../Utilities/memDbg.h"

Object::Object() {};
Shaders myShaders;
Model2 *model;
int Object::addObject(char *linkObject, char *linkTexture) {
	model = new Model2[2];
	
	return 1;
}
void Object::showObject(Matrix m, int n, int w) {

	int i = n;
		glBindBuffer(GL_ARRAY_BUFFER, model[i].vertexBuffer);
		glUseProgram(myShaders.program);


		if (w == 1) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model[i].indexBuffer);
			glBindTexture(GL_TEXTURE_2D, model[i].textureBuffer);
		}
		else if (w == 2) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model[i].wBuffer);
		}
		else if (w == 3) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model[i].indexBuffer);
			glBindTexture(GL_TEXTURE_2D, model[i].textureBuffer);
		}

		if (myShaders.positionAttribute != -1) //daca exista variabila a_posL in vs
		{
			glEnableVertexAttribArray(myShaders.positionAttribute); //porneste o lista de atribute generice vertex
			glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //defineste o multime de date vertex
		}

		if (myShaders.colorAttribute != -1) {
			glEnableVertexAttribArray(myShaders.colorAttribute);
			glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
		}
		if (myShaders.mvpUniform != -1) {
			glUniformMatrix4fv(myShaders.mvpUniform, 1, GL_FALSE, (GLfloat*)m.m); //specifica valorile a unei variabile imoform pentru obiectul provram curent
		}
		if (myShaders.uvAttribute != -1) {
			glEnableVertexAttribArray(myShaders.uvAttribute);
			glVertexAttribPointer(myShaders.uvAttribute, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(5 * sizeof(Vector3)));
		}
		if (myShaders.textureUniform != -1) {
			glUniform1i(myShaders.textureUniform, 0);
		}


		if (w == 1) {
			glDrawElements(GL_TRIANGLES, model[i].nrInd, GL_UNSIGNED_SHORT, 0);
		}
		else if (w == 2) {
			glDrawElements(GL_LINES, model[i].nrLinii, GL_UNSIGNED_SHORT, 0);

		}
		else if (w == 3) {
			glDrawElements(GL_TRIANGLES, model[i].nrInd, GL_UNSIGNED_SHORT, 0);
		}


		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		glBindTexture(GL_TEXTURE_2D, 0);


		if (w == 3) {
			glBindBuffer(GL_ARRAY_BUFFER, model[i].vertexBuffer);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model[i].wBuffer);

			if (myShaders.positionAttribute != -1) //daca exista variabila a_posL in vs
			{
				glEnableVertexAttribArray(myShaders.positionAttribute); //porneste o lista de atribute generice vertex
				glVertexAttribPointer(myShaders.positionAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0); //defineste o multime de date vertex
			}
			if (myShaders.colorAttribute != -1) {
				glEnableVertexAttribArray(myShaders.colorAttribute);
				glVertexAttribPointer(myShaders.colorAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)sizeof(Vector3));
			}
			if (myShaders.mvpUniform != -1) {
				glUniformMatrix4fv(myShaders.mvpUniform, 1, GL_FALSE, (GLfloat*)m.m); //specifica valorile a unei variabile imoform pentru obiectul provram curent
			}

			glDrawElements(GL_LINES, model[i].nrLinii, GL_UNSIGNED_SHORT, 0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
	
	

}

