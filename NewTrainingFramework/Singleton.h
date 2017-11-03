#pragma once
#include "../Utilities/utilities.h"


class Singleton {
protected:
	static Singleton* spInstance;
	Singleton();
public:
	void Init();
	static Singleton* getInstance();		// verifica daca exista deja o instanta a clasei
											// daca da returneaza un pointer catre acea instanta
											// daca nu creaza o noua instanta si returneaza pointerul catre aceasta

	void metodaInstanta();
	void freeResource();				//eliberarea zonelor de memorie, se poate realiza si in destructor
	~Singleton();

};