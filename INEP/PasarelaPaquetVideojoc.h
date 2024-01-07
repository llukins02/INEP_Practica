#pragma once
#include "PasarelaElemCompra.h"
#include "PasarelaVideojoc.h"
#include <vector>
class PasarelaPaquetVideojoc : public PasarelaElemCompra
{
private:
	std::vector<PasarelaVideojoc> videojocs;

public:
	void add(PasarelaVideojoc v);

	void crear(PasarelaElemCompra eC);

	std::vector<PasarelaVideojoc> getVideojocs();
};

