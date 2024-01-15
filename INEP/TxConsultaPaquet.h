#pragma once
#include "Transaccio.h"
#include "PasarelaPaquetVideojoc.h"

class TxConsultaPaquet : Transaccio
{
private:
	std::string cp;
	PasarelaPaquetVideojoc pv;
public:
	void crear(std::string nom, bool &error);

	std::vector<std::string> executar();
};