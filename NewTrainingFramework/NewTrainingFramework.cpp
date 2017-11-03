// NewTrainingFramework.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include
#include "Vertex.h"
#include "Shaders.h"
#include "stdio.h"
#include <iostream>
#include <conio.h>
#include "Globals.h"
#include "Camera.h"
#include <GL/gl.h>
#include "ResourceManager.h"
#include "SceneManager.h"



Matrix model, trans, rot, scale;
//Shaders myShaders;
Camera c;
Matrix MVP;
GLfloat time;
GLfloat deltaTime;


short int Globals::keypressed = 0;
short int Globals::effectpressed = 0;

int Init ( ESContext *esContext )
{
	
	glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_VERTEX_);
	//glLineWidth(80);


	ResourceManager::getInstance() -> Init();
	SceneManager::getInstance() -> Init();

	return 0;


}
GLfloat alpha = 0;
GLfloat alpha2 = 0;
void Draw ( ESContext *esContext ) //ESContext este clasa care contie datele despre ecran
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //sterge bufferul de valorile precedente (obiecte 3d, culori, ...)
	

	

	SceneManager::getInstance()->Draw(deltaTime);


//-------------------------------------------------------end----------------------------------------------------------------

	eglSwapBuffers ( esContext->eglDisplay, esContext->eglSurface );	//in timp ce afiseaza frameul, deseneaza altu
																		// post EGL surface color buffer to a native window
}

void Update(ESContext *esContext, float dTime)
{
	//c.setDeltaTime(dTime);
	//deltaTime = dTime;
	
	int idCam = 1;
	SceneManager::getInstance()->cameraMap[idCam]->setDeltaTime(dTime);
	SceneManager::getInstance()->Update(dTime);


	if (Globals::keypressed & (1 << Globals::moveF))
		SceneManager::getInstance()->cameraMap[idCam]->moveOz(-1);
	if (Globals::keypressed & (1 << Globals::moveB))
		SceneManager::getInstance()->cameraMap[idCam]->moveOz(1);
	if (Globals::keypressed & (1 << Globals::moveL))
		SceneManager::getInstance()->cameraMap[idCam]->moveOx(-1);
	if (Globals::keypressed & (1 << Globals::moveR))
		SceneManager::getInstance()->cameraMap[idCam]->moveOx(1);
	if (Globals::keypressed & (1 << Globals::moveU))
		SceneManager::getInstance()->cameraMap[idCam]->moveOy(1);
	if (Globals::keypressed & (1 << Globals::moveD))
		SceneManager::getInstance()->cameraMap[idCam]->moveOy(-1);
	if (Globals::keypressed & (1 << Globals::rotU))
		SceneManager::getInstance()->cameraMap[idCam]->rotateOx(1);
	if (Globals::keypressed & (1 << Globals::rotD))
		SceneManager::getInstance()->cameraMap[idCam]->rotateOx(-1);
	if (Globals::keypressed & (1 << Globals::rotL))
		SceneManager::getInstance()->cameraMap[idCam]->rotateOy(1);
	if (Globals::keypressed & (1 << Globals::rotR))
		SceneManager::getInstance()->cameraMap[idCam]->rotateOy(-1);



}

void Key ( ESContext *esContext, unsigned char key, bool bIsPressed)
{
	if (bIsPressed) {
		/*
			POINT pct;
			GetCursorPos(&pct);			//coord pe ecran
			HWND hWnd;
			UINT uCmd;
			GetWindow(hWnd, uCmd);
			ScreenToClient(hWnd, &pct);	// coord in fereastra
		*/

		switch (key) {
		case 'W':
			Globals::keypressed |= 1 << Globals::moveF;
			break;
		case 'S':
			Globals::keypressed |= 1 << Globals::moveB;
			break;
		case 'A':
			Globals::keypressed |= 1 << Globals::moveL;
			break;
		case 'D':
			Globals::keypressed |= 1 << Globals::moveR;
			break;
		case 'R':
			Globals::keypressed |= 1 << Globals::moveU;
			break;
		case 'F':
			Globals::keypressed |= 1 << Globals::moveD;
			break;
		case 'T':
			Globals::keypressed |= 1 << Globals::rotU;
			break;
		case 'G':
			Globals::keypressed |= 1 << Globals::rotD;
			break;
		case 'E':
			Globals::keypressed |= 1 << Globals::rotR;
			break;
		case 'Q':
			Globals::keypressed |= 1 << Globals::rotL;
			break;
		case '1':
			SceneManager::getInstance()->wired();
			break;
		default:
			break;
		}
	}
	else {
		switch (key) {
		case 'W':
			Globals::keypressed &= ~(1 << Globals::moveF);
			break;
		case 'S':
			Globals::keypressed &= ~(1 << Globals::moveB);
			break;
		case 'A':
			Globals::keypressed &= ~(1 << Globals::moveL);
			break;
		case 'D':
			Globals::keypressed &= ~(1 << Globals::moveR);
			break;
		case 'R':
			Globals::keypressed &= ~(1 << Globals::moveU);
			break;
		case 'F':
			Globals::keypressed &= ~(1 << Globals::moveD);
			break;
		case 'T':
			Globals::keypressed &= ~(1 << Globals::rotU);
			break;
		case 'G':
			Globals::keypressed &= ~(1 << Globals::rotD);
			break;
		case 'E':
			Globals::keypressed &= ~(1 << Globals::rotR);
			break;
		case 'Q':
			Globals::keypressed &= ~(1 << Globals::rotL);
			break;
		default:
			break;
		}
	}

}

void CleanUp()
{
	//glDeleteBuffers(1, &vboId);
	//glDeleteBuffers(1, &lineBuffer);
	//glDeleteBuffers(1, &idIndicesBuffer);
}

int _tmain(int argc, _TCHAR* argv[])
{
	//identifying memory leaks
	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); 

	ESContext esContext;

    esInitContext ( &esContext );

	esCreateWindow ( &esContext, "Hello Triangle", Globals::screenWidth, Globals::screenHeight, ES_WINDOW_RGB | ES_WINDOW_DEPTH);

	if ( Init ( &esContext ) != 0 )
		return 0;




	esRegisterDrawFunc ( &esContext, Draw );
	esRegisterUpdateFunc ( &esContext, Update );
	esRegisterKeyFunc ( &esContext, Key);

	esMainLoop ( &esContext );


	



	//releasing OpenGL resources
	CleanUp();


	printf("Press any key...\n");
	_getch();

	
	return 0;
}

