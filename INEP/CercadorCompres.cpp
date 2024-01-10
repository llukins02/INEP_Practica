#include "CercadorCompres.h"
#include "CercadorElemCompra.h"
#include "CercadorVideojoc.h"
#include "CercadorPaquetVideojoc.h"
#include "configBD.h"
#include <pqxx/pqxx>

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