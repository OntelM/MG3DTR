#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "../Utilities/memDbg.h"
#include "Shaders.h"
#include "Vertex.h"
#include "ResourceManager.h"
#include "Model.h"
#include <string>

using namespace std;

Model::Model() {
}
void Model::LoadModel() {
	string extensie = Extension(mr->path);
	string nfg = "nfg"; string obj = "obj";
	if (extensie == nfg) {
		LoadNFG();
	}
	else if (extensie == obj) {
		LoadOBJ();
	}
}
void Model::LoadNFG() {

	vboId = 0;
	iboId = 0;
	wiredIboId = 0;
	
	nrVer = 0;
	nrIndici = 0;
	nrIndiciWired = 0;

	float px, py, pz, nx, ny, nz, bx, by, bz, tx, ty, tz, ux, uy;

	FILE *f;
	

	
	Vertex *listCubeDebug;
	GLushort *w;

	char a[250], b[10];
	errno_t e = fopen_s(&f, mr->path.c_str(), "r");
	if (e) {
		printf_s("Fisierul .nfg nu a fost gasit!");
	}
	else {
		fscanf_s(f, "%s", a, 250);
		fscanf_s(f, "%d", &nrVer);

		listVertex = new Vertex[nrVer];


		for (int i = 0; i < nrVer; i++) {
			fscanf_s(f, "%*d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];",
				&px, &py, &pz, &nx, &ny, &nz, &bx, &by, &bz, &tx, &ty, &tz, &ux, &uy);
			listVertex[i].pos.x = px;	listVertex[i].pos.y = py; listVertex[i].pos.z = pz;
			listVertex[i].norm.x = nx;	listVertex[i].norm.y = ny; listVertex[i].norm.z = nz;
			listVertex[i].binorm.x = bx; listVertex[i].binorm.y = by; listVertex[i].binorm.z = bz;
			listVertex[i].tangent.x = tx; listVertex[i].tangent.y = ty; listVertex[i].tangent.z = tz;
			listVertex[i].uv.x = ux; listVertex[i].uv.y = uy;
		}
		




		fscanf_s(f, "%s", a, 250);
		fscanf_s(f, "%d", &nrIndici);

		listIndici = new GLushort[nrIndici];
		GLint index;
		for (int i = 0; i < nrIndici / 3; i++) {
			fscanf_s(f, "%d", &index);
			fscanf_s(f, "%1c%hu%1c%hu%1c%hu", b, 10, &listIndici[3 * i], b, 10, &listIndici[3 * i + 1], b, 10, &listIndici[3 * i + 2]);
		}
		fclose(f);

		//--------wired-----------
		nrIndiciWired = nrIndici * 2;
		w = new GLushort[nrIndiciWired];
		int k = 0;
		for (int i = 0; i < nrIndici; i += 3) {
			//-----------------Triunghi------------------------------------
			w[k] = listIndici[i];
			k++;
			w[k] = listIndici[i + 1];
			k++;
			w[k] = listIndici[i + 1];
			k++;
			w[k] = listIndici[i + 2];
			k++;
			w[k] = listIndici[i + 2];
			k++;
			w[k] = listIndici[i];
			k++;
			//-------------------end---------------------------------------
		}

		




		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, nrVer * sizeof(Vertex), listVertex, GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &iboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndici * sizeof(GLushort), listIndici, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glGenBuffers(1, &wiredIboId);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wiredIboId);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndiciWired * sizeof(GLushort), w, GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


		delete[] listIndici;
		delete[] w;
	}
}
void Model::LoadOBJ() {
	vboId = 0;
	iboId = 0;
	wiredIboId = 0;

	nrVer = 0;
	nrIndici = 0;
	nrIndiciWired = 0;
	bool conditie = true;

	float px, py, pz, nx, ny, nz, bx, by, bz, tx, ty, tz, ux, uy;
	int a0 = 0, a1 = 0, a2 = 0, a3 = 0, a4 = 0, a5 = 0, a6 = 0, a7 = 0, a8 = 0;
	int nrv = 0, nrn = 0, nruv = 0, nrind = 0;
	
	string randS;

	FILE *f, *file;

	Vertex *listCubeDebug;
	GLushort *w;

	

	char a[250], b[10];
	errno_t er = fopen_s(&file, mr->path.c_str(), "r");
	if (er) {
		printf_s("Fisierul .obj nu a fost gasit!");
	}
	else {
		while (1) {

			char lineHeader[128];
			int res = fscanf(file, "%s", lineHeader);
			if (!strcmp(lineHeader, "v")) {
				fscanf_s(file, "%f %f %f\n", &px, &py, &pz);
				nrVer += 1;
			}
			if (!strcmp(lineHeader, "vt")) {
				fscanf_s(file, "%f %f\n", &px, &py);
				nruv += 1;
			}
			if (!strcmp(lineHeader, "vn")) {
				fscanf_s(file, "%f %f %f\n", &px, &py, &pz);
				nrn += 1;
			}
			if (!strcmp(lineHeader, "f")) {
				if (res != 1) {
					break;
				}
				if (nruv == 0) {
					fscanf(file, "%d//%d %d//%d %d//%d\n", &a0, &a2, &a3, &a5, &a6, &a8);
				}
				else {
					fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
				}
				
				
				nrIndici += 3;
			}
		}
	}
	listVertex = new Vertex[nrVer];
	listIndici = new GLushort[nrIndici];
	vector<Vector3> pos;
	vector<Vector2> uv;
	vector<Vector3> norm;
	vector<GLushort> indici;
	errno_t e = fopen_s(&f, mr->path.c_str(), "r");
	if (e) {
		printf_s("Fisierul .obj nu a fost gasit!");
	}
	else {

		char lineHeader[128];
		
		
		while (1) {

			char lineHeader[128];
			int res = fscanf(f, "%s", lineHeader);
			
			if (!strcmp(lineHeader, "v")) {
				fscanf_s(f, "%f %f %f\n", &px, &py, &pz);
				pos.push_back(Vector3(px, py, pz));
				//listVertex[nrv].pos = Vector3(px, py, pz);
				//nrv++;
				int test = 3;
			}
			else if (!strcmp(lineHeader, "vt")) {
				fscanf_s(f, "%f %f\n", &px, &py);
				uv.push_back(Vector2(px, py));
				int test = 3;
			}
			else if (!strcmp(lineHeader, "vn")) {
				fscanf_s(f, "%f %f %f\n", &px, &py, &pz);
				norm.push_back(Vector3(px, py, pz));
				int test = 3;
			}
		
			if (!strcmp(lineHeader, "f")) {
				if (res != 1) {
					break;
				}
				if (nruv == 0) {
					fscanf(f, "%d//%d %d//%d %d//%d\n", &a0, &a2, &a3, &a5, &a6, &a8);

					int test = 3;
				}
				else {
					fscanf(f, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &a0, &a1, &a2, &a3, &a4, &a5, &a6, &a7, &a8);
				}
				listVertex[a0 - 1].pos = pos[a0 - 1];
				listVertex[a3 - 1].pos = pos[a3 - 1];
				listVertex[a6 - 1].pos = pos[a6 - 1];

				if (size(uv) != NULL) {
					listVertex[a0 - 1].uv = uv[a1 - 1];
					listVertex[a3 - 1].uv = uv[a4 - 1];
					listVertex[a6 - 1].uv = uv[a7 - 1];
				}
				

				listVertex[a0 - 1].norm = norm[a2 - 1];
				listVertex[a3 - 1].norm = norm[a5 - 1];
				listVertex[a6 - 1].norm = norm[a8 - 1];

				
				indici.push_back(a0 - 1);
				indici.push_back(a3 - 1);
				indici.push_back(a6 - 1);

				int test = 3;
			}
		}

		for (int i = 0; i < nrIndici; i++) {
			listIndici[i] = indici[i];
			int test = 10;
		}
		cout << endl;

	}
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, nrVer * sizeof(Vertex), listVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nrIndici * sizeof(GLushort), listIndici, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//delete[] listVertex;
	//delete[] listIndici;

	std::cout << "obj incarcat cu succes" << endl;

	delete[] listIndici;
}

Model::~Model() {

}
string Model::Extension(string str) {
	size_t found = str.find_last_of(".");
	return str.substr(found + 1);
}
