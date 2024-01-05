#include "configBD.h"
#include <iostream>
#include <pqxx/pqxx>

void configBD::create(std::string n, std::string u, std::string p, std::string a, std::string po) {
	BDstring = "dbname="+n+" user="+u+" password="+p+" hostaddr = "+a+" port = "+po;
	try {
		pqxx::connection conn = pqxx::connection(BDstring);
		std::cout << "Connexio a la base de dades feta correctament!\n\n";
	}
	catch (const std::exception& e) {
		std::cerr << "No es possible connectar-se a la BD, dades incorrectes" << std::endl;
	}
}

std::string configBD::getString() {
	return BDstring;
}