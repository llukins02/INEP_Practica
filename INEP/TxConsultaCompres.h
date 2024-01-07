#pragma once
#include "Videoconsola.h"
#include "PasarelaCompra.h"
#include <vector>
#include <string>

class TxConsultaCompres
{
private:
	std::vector<PasarelaCompra> pcs;
public:
	void consultaVideojocs();

	std::vector<PasarelaCompra> getCompres();
};

