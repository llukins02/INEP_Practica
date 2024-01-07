#pragma once
#include <string>

class PasarelaElemCompra
{
protected:
	std::string nom;
	std::string descripcio;
	float preu;
	std::string tipus;
	
public: 
	void crear(std::string n, std::string d, float p, std::string t);

	std::string getNom();
	std::string getDescripcio();
	float getPreu();
	std::string getTipus();
};

