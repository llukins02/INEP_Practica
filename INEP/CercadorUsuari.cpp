#include "CercadorUsuari.h"
#include <pqxx/pqxx>
#include <iostream>


PasarelaUsuari CercadorUsuari::cercadorUsuari(std::string sobrenomU) {
	PasarelaUsuari u;
	try {
		pqxx::connection conn = pqxx::connection("dbname=vINEP user=postgres password=admin hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT * FROM public.\"Usuari\"" + sobrenomU);
		u.crear(res[0][0].c_str(), res[0][1].c_str(), res[0][2].c_str(), res[0][3].c_str(), res[0][4].c_str());
		txn.commit();
	}catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
	return u;
}