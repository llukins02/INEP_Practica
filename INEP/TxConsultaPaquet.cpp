#include "TxCompraPaquet.h"
#include "CercadorElemCompra.h"
#include "CercadorPaquetVideojoc.h"
#include "CercadorCompres.h"
#include <pqxx/pqxx>
#include <iostream>

void TxConsultaPaquet::crear(std::string nom, bool &error) {
	CercadorElemCompra cec;
	CercadorPaquetVideojoc cpv;
	std::string ret;
	PasarelaElemCompra ec = cec.cerca(nom);
	pv = cpv.cerca(nom, ec);
	if (pv.getTipus() != "paquet") {
		ret = "Error: aquest paquet no existeix!"+ec.getTipus();
		error = true;
	}
	else {
		float preuVideojocs = 0;
		std::string aux = "";
		for (int i = 0; i < pv.getVideojocs().size(); i++) {
			preuVideojocs += pv.getVideojocs()[i].getPreu();
			aux += "\n- " + pv.getVideojocs()[i].getNom() + "; " + pv.getVideojocs()[i].getDescripcio() + "; " + std::to_string(pv.getVideojocs()[i].getPreu()) + " euros";
		}
		ret = "Informacio paquet ...\nNom paquet: " + pv.getNom() + "\nDescripcio: " + pv.getDescripcio() + "\nPreu: " + std::to_string(pv.getPreu()) +
			" euros (estalvi de " + std::to_string(preuVideojocs - pv.getPreu()) + " euros)\n\nJocs inclosos:"+aux;
	}
	cp = ret;
}

std::vector<std::string> TxConsultaPaquet::executar(){
	return cp;
}