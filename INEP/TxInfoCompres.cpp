#include "TxInfoCompres.h"
#include "Videoconsola.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

void TxInfoCompres::crear() {
	Videoconsola& v = Videoconsola::getInstance();
	sobrenomU = v.obteUsuari().obteSobrenom();
}

float TxInfoCompres::executar(int& tV, int& tP) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	try {
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT count(*) FROM public.\"Compra\", public.\"ElementCompra\" WHERE \"Compra\".usuari = '" + sobrenomU + "' and \"Compra\".element = \"ElementCompra\".nom and \"ElementCompra\".tipus = 'videojoc';");
		tV = std::stoi(res[0][0].c_str());
		res = txn.exec("SELECT count(*) FROM public.\"Compra\", public.\"ElementCompra\" WHERE \"Compra\".usuari = '" + sobrenomU + "' and \"Compra\".element = \"ElementCompra\".nom and \"ElementCompra\".tipus = 'paquet';");
		tP = std::stoi(res[0][0].c_str());
		if (tV > 0 || tP > 0) {
			res = txn.exec("SELECT sum(\"Compra\".\"preuPagat\") FROM public.\"Compra\" WHERE \"Compra\".usuari = '" + sobrenomU + "';");
			return std::stof(res[0][0].c_str());
		}
		return std::stof("0");
	}catch (const std::exception& e) {
		std::cerr << "Hi ha hagut un error amb la base de dades." << std::endl;
	}
}