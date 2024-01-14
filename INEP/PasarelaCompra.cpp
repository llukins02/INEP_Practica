#include "PasarelaCompra.h"
#include "configBD.h"
#include <iostream>
#include <pqxx/pqxx>

void PasarelaCompra::create(PasarelaUsuari u, std::string d, float p) {
	usuari = u;
	data = d;
	preuPagat = p;
}

void PasarelaCompra::createV(PasarelaVideojoc video) {
	v = video;
	tipus = "videojoc";
}

void PasarelaCompra::createPV(PasarelaPaquetVideojoc paquet) {
	pv = paquet;
	tipus = "paquet";
}

std::string PasarelaCompra::insereix() {
	try {
		std::string nom = pv.getNom();
		if (tipus == "videojoc") { nom = v.getNom(); }
		configBD& bd = configBD::getInstance();
		pqxx::connection conn = pqxx::connection(bd.getString());
		pqxx::work txn(conn);
		pqxx::result res = txn.exec("INSERT INTO public.\"Compra\"(usuari, element, data, \"preuPagat\")VALUES('" + usuari.obteSobrenom() + "', '" + nom + "', '" + data + "', '" + std::to_string(preuPagat) + "'); ");
		txn.commit();
		return "Compra Registrada: "+data;
	}
	catch (const std::exception& e) {
			return e.what();
	}
}

PasarelaUsuari PasarelaCompra::getUsuari() {
	return usuari;
}


std::string PasarelaCompra::getTipus() {
	return tipus;
}

PasarelaVideojoc PasarelaCompra::getVideojoc() {
	return v;
}

PasarelaPaquetVideojoc PasarelaCompra::getPaquet() {
	return pv;
}

std::string PasarelaCompra::getData() {
	return data;
}

float PasarelaCompra::getPreuPagat() {
	return preuPagat;
}