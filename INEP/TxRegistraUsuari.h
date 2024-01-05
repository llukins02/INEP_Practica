#pragma once
#include "Transaccio.h"

class TxRegistraUsuari : Transaccio
{
private:
	std::string nomU;
	std::string sobrenomU;
	std::string contrasenyaU;
	std::string correuElectronicU;
	std::string dataNaixamentU;

public:
	void crear(std::string nU, std::string sU, std::string cU, std::string ceU, std::string dU);

	std::string executar();
};

