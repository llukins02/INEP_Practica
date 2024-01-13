#pragma once
#include "PasarelaVideojoc.h"
#include "Transaccio.h"

class TxConsultaVideojoc : Transaccio
{
private:
	std::string nom;
	PasarelaElemCompra ec;
public:
	void crear(std::string nom);
	std::vector<std::string> executar();
};

