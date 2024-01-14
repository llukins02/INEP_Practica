#include "CercadorCompres.h"
#include "CercadorElemCompra.h"
#include "CercadorVideojoc.h"
#include "CercadorPaquetVideojoc.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

std::vector<PasarelaCompra> CercadorCompres::obteCompresUsuari(PasarelaUsuari u) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	std::vector<PasarelaCompra> compres;
	CercadorElemCompra CEC;
	CercadorVideojoc cv;
	CercadorPaquetVideojoc cpv;
	pqxx::work txn(conn);
	pqxx::result res = txn.exec("SELECT * FROM public.\"Compra\" WHERE usuari = '" + u.obteSobrenom() + "' ORDER BY data;");
	for (size_t i = 0; i < res.size(); ++i) {
		PasarelaCompra c;
		c.create(u, res[i][2].c_str(), std::stof(res[i][3].c_str()));
		PasarelaElemCompra ec = CEC.cerca(res[i][1].c_str());
		if (ec.getTipus() == "videojoc") {
			c.createV(cv.cerca(res[i][1].c_str(), ec));
		}
		else {
			c.createPV(cpv.cerca(res[i][1].c_str(), ec));
		}
		compres.push_back(c);
	}
	return compres;
}

void CercadorCompres::countCompres(std::string sobrenomU, int& tV, int& tP) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	try {
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT count(*) FROM public.\"Compra\", public.\"ElementCompra\" WHERE \"Compra\".usuari = '" + sobrenomU + "' and \"Compra\".element = \"ElementCompra\".nom and \"ElementCompra\".tipus = 'videojoc';");
		tV = std::stoi(res[0][0].c_str());
		res = txn.exec("SELECT count(*) FROM public.\"Compra\", public.\"ElementCompra\" WHERE \"Compra\".usuari = '" + sobrenomU + "' and \"Compra\".element = \"ElementCompra\".nom and \"ElementCompra\".tipus = 'paquet';");
		tP = std::stoi(res[0][0].c_str());
	}
	catch (const std::exception& e) {
		std::cerr << "Hi ha hagut un error amb la base de dades." << std::endl;
	}
}

float CercadorCompres::sumPreuCompres(std::string sobrenomU) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	try {
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT sum(\"Compra\".\"preuPagat\") FROM public.\"Compra\" WHERE \"Compra\".usuari = '" + sobrenomU + "';");
		if(!res.empty()){
			return std::stof(res[0][0].c_str());
		}
		return std::stof("0");
	}
	catch (const std::exception& e) {
		std::cerr << "Hi ha hagut un error amb la base de dades." << std::endl;
	}
}