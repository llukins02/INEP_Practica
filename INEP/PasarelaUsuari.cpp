#include "PasarelaUsuari.h"
#include <iostream>
#include <pqxx/pqxx>

void PasarelaUsuari::crear(std::string n, std::string s, std::string c, std::string ce, std::string dn) {
	nomU = n;
	sobrenomU = s;
	contrasenyaU = c;
	correuElectronicU = ce;
	dataNaixamentU =  dn;
}

void PasarelaUsuari::insereix() {
	try {
		pqxx::connection conn = pqxx::connection("dbname=vINEP user=postgres password=admin hostaddr = 127.0.0.1 port = 5432");
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("INSERT INTO public.\"Usuari\"(nom, sobrenom, contrasenya, \"correuElectronic\", \"dataNaixement\")VALUES('"+nomU+"', '"+sobrenomU+"', '"+contrasenyaU+"', '"+correuElectronicU+"', '"+dataNaixamentU+"'); ");
		txn.commit();
		std::cout << "Usuari " << sobrenomU << ", registrat correctament!" << std::endl;
	}
	catch (const std::exception& e) {
		std::string error = e.what();
		std::cerr << error << std::endl;
		if (error.find("sobrenom") != std::string::npos) {
			std::cerr << "Ja existeix aquest sobrenom, siusplau tria'n un altre." << std::endl;
		}
		else if (error.find("correuElectronic") != std::string::npos) {
			std::cerr << "Ja existeix un compte amb aquest correu electronic, siusplau tria'n un altre." << std::endl;
		}
		else if (error.find("dataNaixement") != std::string::npos) {
			std::cerr << "Data de naixement amb format incorrecte, siusplau torna-ho a posar amb el format segent¨: DD/MM/AAAA" << std::endl;
		}
		
		else {
			std::cerr << error << std::endl;
		}
		
	}
} //exc{usuariExisteix, correuExisteix}

void PasarelaUsuari::modifica() {} //exc{usuariNoExisteix}

void PasarelaUsuari::esborra() {} //exc{usuariNoExisteix}

std::string PasarelaUsuari::obteNom(){
	return nomU;
}

std::string PasarelaUsuari::obteSobrenom(){
	return sobrenomU;
}

std::string PasarelaUsuari::obteContrasenya() {
	return contrasenyaU;
}

std::string PasarelaUsuari::obteCorreu(){
	return correuElectronicU;
}

std::string PasarelaUsuari::obteNaixament(){
	return dataNaixamentU;
}