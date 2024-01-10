#include "CercadorPaquetVideojoc.h"
#include "CercadorElemCompra.h"
#include "PasarelaElemCompra.h"
#include <iostream>

PasarelaPaquetVideojoc CercadorPaquetVideojoc::cerca(std::string nom, PasarelaElemCompra elemCompra) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	PasarelaPaquetVideojoc pv;
	CercadorVideojoc cv;
	try {
		pqxx::work txn(conn);
		pqxx::result result = txn.exec("SELECT * FROM public.\"Conte\" WHERE paquet = '" + nom + "';");
		pv.crear(elemCompra);
		for (size_t i = 0; i < result.size(); ++i) {
			pqxx::result res = txn.exec("SELECT * FROM public.\"ElementCompra\" WHERE nom = '" + result[i][1].as<std::string>() + "';");
			PasarelaElemCompra eC;
			eC.crear(res[0][0].c_str(), res[0][1].c_str(), std::stof(res[0][2].c_str()), res[0][3].c_str());
			pv.add(cv.cerca(result[i][1].as<std::string>(), eC));
		}

		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return pv;
}

std::vector<PasarelaVideojoc> CercadorPaquetVideojoc::cercaVidejocsRelacionats(std::string nom) {
	std::vector<PasarelaVideojoc> vpv;
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	CercadorElemCompra cec;
	try {
		pqxx::work txn(conn);
		pqxx::result result = txn.exec("SELECT * FROM public.\"Conte\" WHERE videojoc = '" + nom + "';");
		for (size_t i = 0; i < result.size(); ++i) {
			PasarelaElemCompra ec = cec.cerca(result[i][0].c_str());
			PasarelaPaquetVideojoc pv = cerca(result[i][0].c_str(), ec);
			for (int j = 0; j < pv.getVideojocs().size(); j++) {
				if (pv.getVideojocs()[j].getNom() != nom) {
					vpv.push_back(pv.getVideojocs()[j]);
				}
			}
		}

		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return vpv;
}