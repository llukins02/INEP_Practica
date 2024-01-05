#include "configBD.h"
#include <iostream>
#include <pqxx/pqxx>

bool configBD::create(std::string n, std::string u, std::string p, std::string a, std::string po) {
	BDstring = "dbname="+n+" user="+u+" password="+p+" hostaddr = "+a+" port = "+po;
	try {
		pqxx::connection conn = pqxx::connection(BDstring);
		return true;
	}
	catch (const std::exception& e) {
		return false;
	}
}

std::string configBD::getString() {
	return BDstring;
}