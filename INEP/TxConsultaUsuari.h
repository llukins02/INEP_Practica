#pragma once
#include "Transaccio.h"

class TxConsultaUsuari : Transaccio
{
private:
	PasarelaUsuari usuari;

public:
	void crear();

	std::vector<std::string> executar();
};

