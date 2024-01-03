#pragma once
#include "Transaccio.h"

class CtrlModificaUsuari : Transaccio
{
private:
	PasarelaUsuari usuari;

public:
	void consultaUsuari();
	void modificaUsuari(std::string nU, std::string cU, std::string ceU, std::string dU);
};

