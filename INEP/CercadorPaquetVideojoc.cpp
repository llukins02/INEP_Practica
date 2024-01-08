#include "CercadorPaquetVideojoc.h"
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
