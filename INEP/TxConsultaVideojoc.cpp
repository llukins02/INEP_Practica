#include "TxConsultaVideojoc.h"
#include "CercadorVideojoc.h"
#include "CercadorElemCompra.h"
#include <string>
#include <iostream>

void TxConsultaVideojoc::crear(std::string nom) {
	nom = nom;
	CercadorElemCompra cec;
	ec = cec.cerca(nom);
}

std::vector<std::string> TxConsultaVideojoc::executar() {
	CercadorVideojoc cv;
	PasarelaVideojoc pv = cv.cerca(nom, ec);
	std::vector<std::string> vector;
	if (pv.getNom().empty()) {
		std::cerr << "Videojoc inexistent\n" << std::endl;
	}
	else {
		vector.push_back(pv.getNom());
		vector.push_back(pv.getDescripcio());
		vector.push_back(std::to_string(pv.getQualificacioEdat()));
		vector.push_back(pv.getGenere());
		vector.push_back(pv.getDataLlansament());
		vector.push_back(std::to_string(pv.getPreu()));
		//vector.push_back(pv.getPaquets());
	}
	return vector;
}