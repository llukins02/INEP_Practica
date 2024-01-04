#include "TxConsultaUsuari.h"
#include "Videoconsola.h"
#include <pqxx/pqxx>
#include <iostream>

void TxConsultaUsuari::crear(){
	Videoconsola& v = Videoconsola::getInstance();
	usuari = v.obteUsuari();
}

std::vector<std::string> TxConsultaUsuari::executar(){
	std::vector<std::string> vector;
	vector.push_back(usuari.obteNom());
	vector.push_back(usuari.obteSobrenom());
	vector.push_back(usuari.obteCorreu());
	vector.push_back(usuari.obteNaixament());
	return vector;
}