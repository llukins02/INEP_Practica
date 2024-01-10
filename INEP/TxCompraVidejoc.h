#pragma once
#include "Transaccio.h"
#include "PasarelaVideojoc.h"
class TxCompraVidejoc : public Transaccio
{
private:
	PasarelaVideojoc v;
public:
	std::string crear(std::string nom, bool &error);

	std::string executa(bool &error);
};

