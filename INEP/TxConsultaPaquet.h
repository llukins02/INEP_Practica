#pragma once
#include "Transaccio.h"
#include "TxCompraPaquet.h"

class TxConsultaUsuari : Transaccio
{
private:
	std::string cp;

public:
	void crear();

	std::vector<std::string> executar();
};