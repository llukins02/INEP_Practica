#include "CercadorCompres.h"
#include "configBD.h"
#include <pqxx/pqxx>

std::vector<PasarelaCompra> CercadorCompres::obteCompresUsuari(std::string sobrenom) {
	configBD& bd = configBD::getInstance();
	pqxx::connection conn = pqxx::connection(bd.getString());
}