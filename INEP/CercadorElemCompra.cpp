#include "CercadorElemCompra.h"
#include "PasarelaElemCompra.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

void CercadorElemCompra::cerca(std::string nom){
	PasarelaElemCompra ElemCompra;
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	try {
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT * FROM public.\"ElementCompra\" WHERE nom = '" + nom + "';");
		if (!res.empty()) {
			ElemCompra.crear(res[0][0].c_str(), res[0][1].c_str(), std::stof(res[0][1].c_str()), res[0][1].c_str());
			tipus = ElemCompra.getTipus();
			if (tipus=="videojoc") {
				res = txn.exec("SELECT * FROM public.\"Videojoc\" WHERE nom = '" + nom + "';");
				v.crear(std::stoi(res[0][1].c_str()), res[0][1].c_str(), std::stoi(res[0][1].c_str()), res[0][1].c_str());
			}
			else {

			}
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

std::string CercadorElemCompra::getTipus(){
	return tipus;
}

PasarelaVideojoc CercadorElemCompra::getVideojoc(){
	return v;
}

PasarelaPaquetVideojoc CercadorElemCompra::getPaquet() {
	return pv;
}