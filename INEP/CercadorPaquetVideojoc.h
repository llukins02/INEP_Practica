#pragma once
#include "configBD.h"
#include "PasarelaElemCompra.h"
#include "PasarelaPaquetVideojoc.h"
#include "CercadorVideojoc.h"

class CercadorPaquetVideojoc
{
public:
	PasarelaPaquetVideojoc cerca(std::string nom, PasarelaElemCompra elemCompra);
};

