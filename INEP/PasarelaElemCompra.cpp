#include "PasarelaElemCompra.h"

void PasarelaElemCompra::crear(std::string n, std::string d, float p, std::string t) {
	nom = n;
	descripcio = d;
	preu = p;
	tipus = t;
}

std::string PasarelaElemCompra::getNom() {
	return nom;
}

std::string PasarelaElemCompra::getDescripcio() {
	return descripcio;
}

float PasarelaElemCompra::getPreu() {
	return preu;
}

std::string PasarelaElemCompra::getTipus() {
	return tipus;
}
