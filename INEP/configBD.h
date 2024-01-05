#pragma once
#include <string>
#include <pqxx/pqxx>

class configBD
{
private:
	std::string BDstring = "dbname=vINEP user=postgres password=admin hostaddr = 127.0.0.1 port = 5432";
	configBD(){}
public:
	static configBD& getInstance() {
		static configBD instance;
		return instance;
	}

	void create(std::string n, std::string u, std::string p, std::string a, std::string po);

	std::string getString();
};

