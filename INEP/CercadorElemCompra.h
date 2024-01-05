#pragma once
#include "PasarelaPaquetVideojoc.h"

class CercadorElemCompra
{
private:
	std::string tipus;
	PasarelaVideojoc v;
	PasarelaPaquetVideojoc pv;
public:
	void cerca(std::string nom);

	std::string getTipus();

	PasarelaVideojoc getVideojoc();

	PasarelaPaquetVideojoc getPaquet();
};

