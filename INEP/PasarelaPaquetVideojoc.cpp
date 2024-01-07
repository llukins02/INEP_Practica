#include "PasarelaPaquetVideojoc.h"

void PasarelaPaquetVideojoc::add(PasarelaVideojoc v) {
	videojocs.push_back(v);
}

void PasarelaPaquetVideojoc::crear(PasarelaElemCompra eC) {
	nom = eC.getNom();
	descripcio = eC.getDescripcio();
	preu = eC.getPreu();
	tipus = "videojoc";
}

std::vector<PasarelaVideojoc> PasarelaPaquetVideojoc::getVideojocs() {
	return videojocs;
}