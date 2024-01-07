#include "PasarelaCompra.h"
#include <iostream>

void PasarelaCompra::create(PasarelaUsuari u, std::string d, float p) {
	usuari = u;
	data = d;
	preuPagat = p;
}

void PasarelaCompra::createV(PasarelaVideojoc video) {
	v = video;
	tipus = "videojoc";
}

void PasarelaCompra::createPV(PasarelaPaquetVideojoc paquet) {
	pv = paquet;
	tipus = "paquet";
}

PasarelaUsuari PasarelaCompra::getUsuari() {
	return usuari;
}


std::string PasarelaCompra::getTipus() {
	return tipus;
}

PasarelaVideojoc PasarelaCompra::getVideojoc() {
	return v;
}

PasarelaPaquetVideojoc PasarelaCompra::getPaquet() {
	return pv;
}

std::string PasarelaCompra::getData() {
	return data;
}

float PasarelaCompra::getPreuPagat() {
	return preuPagat;
}