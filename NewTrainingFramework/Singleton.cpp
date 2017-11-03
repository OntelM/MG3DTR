#include "stdafx.h"
#include <iostream>
#include "Globals.h"
#include "Shaders.h"
#include "Singleton.h"
#include "../Utilities/memDbg.h"

Singleton::Singleton() {};
Singleton* Singleton::spInstance = NULL;
Singleton* Singleton::getInstance() {
	if (!spInstance) {
		spInstance = new Singleton();
	}
	return spInstance;
}
void Singleton::metodaInstanta() {

}


