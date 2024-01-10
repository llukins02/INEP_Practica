#pragma once
#include "PasarelaElemCompra.h"
#include "PasarelaVideojoc.h"
#include "PasarelaPaquetVideojoc.h"
#include "PasarelaUsuari.h"
#include <string>
#include <vector>

class PasarelaCompra
{
private:
	PasarelaUsuari usuari;
	std::string tipus;
	PasarelaVideojoc v;
	PasarelaPaquetVideojoc pv;
	std::string data;
	float preuPagat;

public:
	void create(PasarelaUsuari u, std::string data, float p);

	void createV(PasarelaVideojoc video);

	void createPV(PasarelaPaquetVideojoc paquet);

	std::string insereix();

	PasarelaUsuari getUsuari();

	std::string getTipus();

	PasarelaVideojoc getVideojoc();

	PasarelaPaquetVideojoc getPaquet();

	std::string getData();

	float getPreuPagat();
};

