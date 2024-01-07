#include "CercadorElemCompra.h"
#include "PasarelaElemCompra.h"
#include "CercadorVideojoc.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

void CercadorElemCompra::cerca(std::string nom, PasarelaCompra& PC){;
	PasarelaElemCompra ElemCompra;
	CercadorVideojoc cv;
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
				pqxx::result result = txn.exec("SELECT * FROM public.\"Conte\" WHERE paquet = '" + nom + "';");
				PasarelaPaquetVideojoc pv;
				pv.crear(ElemCompra);
				for (size_t i = 0; i < result.size(); ++i) {
					res = txn.exec("SELECT * FROM public.\"ElementCompra\" WHERE nom = '" + result[i][1].as<std::string>() + "';");
					PasarelaElemCompra eC;
					eC.crear(res[0][0].c_str(), res[0][1].c_str(), std::stof(res[0][2].c_str()), res[0][3].c_str());
					pv.add(cv.cerca(result[i][1].as<std::string>(), eC));
				}
				PC.createPV(pv);
			}
		}
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}
}