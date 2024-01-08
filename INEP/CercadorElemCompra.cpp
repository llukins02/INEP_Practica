#include "CercadorElemCompra.h"
#include "PasarelaElemCompra.h"
#include "CercadorVideojoc.h"
#include "CercadorPaquetVideojoc.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

void CercadorElemCompra::cerca(std::string nom, PasarelaCompra& PC){;
	PasarelaElemCompra ElemCompra;
	CercadorVideojoc cv;
	CercadorPaquetVideojoc cpv;
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
	try {
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("SELECT * FROM public.\"ElementCompra\" WHERE nom = '" + nom + "';");
		if (!res.empty()) {
			ElemCompra.crear(res[0][0].c_str(), res[0][1].c_str(), std::stof(res[0][2].c_str()), res[0][3].c_str());
			if (ElemCompra.getTipus()=="videojoc") {
				PC.createV(cv.cerca(nom, ElemCompra));
			}
			else {
				PasarelaPaquetVideojoc pv = cpv.cerca(nom, ElemCompra);
				PC.createPV(pv);
			}
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}