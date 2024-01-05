#pragma once
#include "PasarelaElemCompra.h"
#include "PasarelaVideojoc.h"
#include <vector>
class PasarelaPaquetVideojoc : public PasarelaElemCompra
{
private:
	std::vector<PasarelaVideojoc> videojocs;
};

