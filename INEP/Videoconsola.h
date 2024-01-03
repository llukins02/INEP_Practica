#pragma once
#include "PasarelaUsuari.h"
class Videoconsola
{
private:
	PasarelaUsuari usuari;
	Videoconsola(){}
public:
	static Videoconsola& getInstance() {
		static Videoconsola instance;
		return instance;
	}

	PasarelaUsuari obteUsuari();

	void iniciaSessio(PasarelaUsuari u);

	void tancaSessio();
};

