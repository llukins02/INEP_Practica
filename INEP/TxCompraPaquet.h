#pragma once
#include "Transaccio.h"
#include "PasarelaPaquetVideojoc.h"
class TxCompraPaquet : Transaccio
{
private:
	PasarelaPaquetVideojoc pv;
public:
	std::string crear(std::string nom, bool &error);

	std::string executa();
};

