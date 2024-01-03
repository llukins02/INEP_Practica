#pragma once
#include "Transaccio.h"

class TxIniciSessio : Transaccio
{
private:
	std::string sobrenomU;
	std::string contrasenyaU;
public:
	void crear(std::string sU, std::string cU);

	void executar();
};

