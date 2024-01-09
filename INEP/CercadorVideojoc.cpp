#include "CercadorVideojoc.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

PasarelaVideojoc CercadorVideojoc::cerca(std::string nom, PasarelaElemCompra elemCompra) {
	PasarelaVideojoc v;
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	try {
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT * FROM public.\"Videojoc\" WHERE nom = '" + nom + "';");
		if (!res.empty()) {
			v.crear(std::stoi(res[0][2].c_str()), res[0][3].c_str(), std::stoi(res[0][4].c_str()), res[0][1].c_str(), elemCompra);
		}
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
	return v;
}
