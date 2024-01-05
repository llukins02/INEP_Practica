#include "CercadorUsuari.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>


PasarelaUsuari CercadorUsuari::cercadorUsuari(std::string sobrenomU) {
	PasarelaUsuari u;
	try {
		configBD& bd = configBD::getInstance();
		pqxx::connection conn = pqxx::connection(bd.getString());
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT * FROM public.\"Usuari\" WHERE sobrenom = '" + sobrenomU + "';");
		if (!res.empty()) {
			u.crear(res[0][0].c_str(), res[0][1].c_str(), res[0][2].c_str(), res[0][3].c_str(), res[0][4].c_str());
		}
		txn.commit();
	}catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return u;
}