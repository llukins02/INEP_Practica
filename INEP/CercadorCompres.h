#pragma once
#include "PasarelaCompra.h"
#include <string>
#include <vector>
class CercadorCompres
{
public:
	std::vector<PasarelaCompra> obteCompresUsuari(PasarelaUsuari u);

	void countCompres(std::string sobrenomU, int &tv, int &tp);

	float sumPreuCompres(std::string sobrenomU);
};

