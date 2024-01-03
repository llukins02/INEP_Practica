#pragma once
#include "Transaccio.h"

class TxConsultaUsuari : Transaccio
{
private:
	std::vector<std::string> resultat;
	PasarelaUsuari usuari;

public:
	void crear();

	void executar();

	std::vector<std::string> getResultat();

	PasarelaUsuari getUsuari();
};

