#pragma once
#include "PasarelaElemCompra.h"
class PasarelaVideojoc : public PasarelaElemCompra
{
private:
	int qualificacioEdat;
	std::string dataLlansament;
	int minsEstimat;
	std::string genere;
public:
	int getQualificacioEdat();
	std::string getDataLlansament();
	int getMinsEstimat();
	std::string getGenere();

	void crear(int q, std::string dL, int mE, std::string g, PasarelaElemCompra eC);
};

