#include "TxInfoCompres.h"
#include "Videoconsola.h"
#include <pqxx/pqxx>

void TxInfoCompres::crear() {
	Videoconsola& v = Videoconsola::getInstance();
	sobrenomU = v.obteUsuari().obteSobrenom();
}

float TxInfoCompres::executar(int& tV, int& tP) {
	pqxx::connection conn = pqxx::connection("dbname=vINEP user=postgres password=admin hostaddr = 127.0.0.1 port = 5432");
	pqxx::work txn(conn);
	pqxx::result res = txn.exec("SELECT count(*) FROM public.\"Compra\", public.\"ElementCompra\" WHERE \"Compra\".usuari = '" + sobrenomU + "' and \"Compra\".element = \"ElementCompra\".nom and \"ElementCompra\".tipus = 'videojoc';");
	tV = std::stoi(res[0][0].c_str());
	res = txn.exec("SELECT count(*) FROM public.\"Compra\", public.\"ElementCompra\" WHERE \"Compra\".usuari = '" + sobrenomU + "' and \"Compra\".element = \"ElementCompra\".nom and \"ElementCompra\".tipus = 'paquet';");
	tP = std::stoi(res[0][0].c_str());
	res = txn.exec("SELECT sum(\"Compra\".\"preuPagat\") FROM public.\"Compra\" WHERE \"Compra\".usuari = '" + sobrenomU + "';");
	return std::stod(res[0][0].c_str());
}