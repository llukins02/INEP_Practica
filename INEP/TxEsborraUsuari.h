#pragma once
#include "Transaccio.h"

class TxEsborraUsuari : Transaccio
{
private:
	std::string contraU;
public:
	void create(std::string cU);

	bool execute();
};

