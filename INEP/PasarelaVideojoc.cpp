#include "PasarelaVideojoc.h"

int PasarelaVideojoc::getQualificacioEdat() {
	return qualificacioEdat;
}

std::string PasarelaVideojoc::getDataLlansament() {
	return dataLlansament;
}

int PasarelaVideojoc::getMinsEstimat() {
	return minsEstimat;
}

std::string PasarelaVideojoc::getGenere() {
	return genere;
}

void PasarelaVideojoc::crear(int q, std::string dL, int mE, std::string g) {
	qualificacioEdat = q;
	dataLlansament = dL;
	minsEstimat = mE;
	genere = g;
}