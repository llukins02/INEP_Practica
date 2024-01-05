#include "PasarelaUsuari.h"
#include "configBD.h"
#include <iostream>
#include <pqxx/pqxx>

void PasarelaUsuari::crear(std::string n, std::string s, std::string c, std::string ce, std::string dn) {
	nomU = n;
	sobrenomU = s;
	contrasenyaU = c;
	correuElectronicU = ce;
	dataNaixamentU =  dn;
}

std::string PasarelaUsuari::insereix() {
	try {
		configBD& bd = configBD::getInstance();
		pqxx::connection conn = pqxx::connection(bd.getString());
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("INSERT INTO public.\"Usuari\"(nom, sobrenom, contrasenya, \"correuElectronic\", \"dataNaixement\")VALUES('"+nomU+"', '"+sobrenomU+"', '"+contrasenyaU+"', '"+correuElectronicU+"', '"+dataNaixamentU+"'); ");
		txn.commit();
		return "Usuari " + sobrenomU + ", registrat correctament!\n\n";
	}
	catch (const std::exception& e) {
		std::string error = e.what();
		if (error.find("sobrenom") != std::string::npos) {
			return "Ja existeix aquest sobrenom, siusplau tria'n un altre.\n\n";
		}
		else if (error.find("correuElectronic") != std::string::npos) {
			return "Ja existeix un compte amb aquest correu electronic, siusplau tria'n un altre.\n\n";
		}
		else if (error.find("dataNaixement") != std::string::npos) {
			return "Data de naixement amb format incorrecte, siusplau torna-ho a posar amb el format segent¨: DD/MM/AAAA\n\n";
		}	
		else {
			return error;
		}
		
	}
} //exc{usuariExisteix, correuExisteix}

void PasarelaUsuari::modifica() {} //exc{usuariNoExisteix}

void PasarelaUsuari::esborra() {
	try {
		configBD& bd = configBD::getInstance();
		pqxx::connection conn = pqxx::connection(bd.getString());
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("DELETE FROM public.\"Compra\" WHERE \"Compra\".usuari = '" + sobrenomU + "';");
		res = txn.exec("DELETE FROM public.\"Usuari\" WHERE \"Usuari\".nom = '" + sobrenomU + "';");
		txn.commit();
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
} //exc{usuariNoExisteix}

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