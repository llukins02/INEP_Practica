#include "CercadorCompres.h"
#include "CercadorElemCompra.h"
#include "configBD.h"
#include <pqxx/pqxx>

std::vector<PasarelaCompra> CercadorCompres::obteCompresUsuari(PasarelaUsuari u) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	std::vector<PasarelaCompra> compres;
	CercadorElemCompra CEC;
	pqxx::work txn(conn);
	pqxx::result res = txn.exec("SELECT * FROM public.\"Compra\" WHERE usuari = '" + u.obteSobrenom() + "';");
	for (size_t i = 0; i < res.size(); ++i) {
		PasarelaCompra c;
		c.create(u, res[i][2].c_str(), std::stof(res[i][3].c_str()));
		CEC.cerca(res[i][1].c_str(), c);
		compres.push_back(c);
	}
	return compres;
}