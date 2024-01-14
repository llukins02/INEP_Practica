#pragma once
#include "Transaccio.h"

class TxConsultaVideojocs : Transaccio
{
private:
	std::vector<std::string> vec;
public:
	void crear(std::string nom);
	std::vector<std::string> executar();
};

