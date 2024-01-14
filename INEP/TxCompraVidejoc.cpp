#include "TxCompraVidejoc.h"
#include "Videoconsola.h"
#include "CercadorElemCompra.h"
#include "CercadorVideojoc.h"
#include "CercadorPaquetVideojoc.h"
#include "CercadorCompres.h"
#include <ctime>
#include <iostream>
#include <format>
#include <chrono>
#include <regex>

int getEdat(std::string naix) {
	int da, dm, dd, na, nm, nd;
	std::regex dateRegex(R"((\d{4})-(\d{2})-(\d{2}))");
	std::smatch match;
	std::regex_match(naix, match, dateRegex);
	da = std::stoi(match[1]);
	dm = std::stoi(match[2]);
	dd = std::stoi(match[3]);
	auto now = (std::chrono::system_clock::now());
	na = std::stoi(std::format("{:%Y}", now));
	nm = std::stoi(std::format("{:%m}", now));
	nd = std::stoi(std::format("{:%d}", now));
	int edat = na - da +1;
	if (nm < dm || (nm == dm && nd < dd)) {
		edat--;
	}
	return edat;
}

std::string TxCompraVidejoc::crear(std::string nom, bool &error){
	CercadorElemCompra cec;
	CercadorVideojoc cv;
	std::string ret;
	PasarelaElemCompra ec = cec.cerca(nom);
	v = cv.cerca(nom, ec);
	if (v.getTipus() != "videojoc") {
		ret = "Error: aquest videojoc no existeix!";
		error = true;
	}
	else {
		ret = "Informacio videojoc...\nNom videojoc: " + v.getNom() + "\nDescripcio: " + v.getDescripcio() + "\nQualificacio edat: " +
			std::to_string(v.getQualificacioEdat()) + "\nGenere: " + v.getGenere() + "\nData llansament: " + v.getDataLlansament() + "\nPreu: " +
			std::to_string(v.getPreu()) + " euros\n";
	}
	return ret;
}

std::string TxCompraVidejoc::executa(){
	std::string nom = v.getNom();
	Videoconsola vc = Videoconsola::getInstance();
	CercadorPaquetVideojoc cpv;
	CercadorCompres cc;
	std::string ret;
	std::vector<PasarelaCompra> vpc = cc.obteCompresUsuari(vc.obteUsuari());
	bool teElJoc = false;

	int i = 0;
	while (i < vpc.size() && !teElJoc) {
		if (vpc[i].getTipus() == "videojoc") {
			if (vpc[i].getVideojoc().getNom() == nom) {
				teElJoc = true;
			}
		}
		else {
			int j = 0;
			while (j < vpc[i].getPaquet().getVideojocs().size() && teElJoc) {
				if (vpc[i].getPaquet().getVideojocs()[j].getNom() == nom) {
					teElJoc = true;
				}
				j++;
			}
		}
		i++;
	}
	if (teElJoc) {
		ret = "Error: l'usuari ja te en propietat el videojoc: " + nom + "!";
	}
	else {
		int edatUsuari = getEdat(vc.obteUsuari().obteNaixament())-1;
		if(edatUsuari < v.getQualificacioEdat()){
			ret = "Error: El videojoc: " + nom + " es per majors de "+std::to_string(v.getQualificacioEdat()) + " anys!";
		}
		else {
			auto now = (std::chrono::system_clock::now());
			std::string data = std::format("{:%d}", now) + "-" + std::format("{:%m}", now) + "-" + std::format("{:%Y}", now) + " " + std::format("{:%X}", now);
			PasarelaCompra pc;
			pc.create(vc.obteUsuari(), data, v.getPreu());
			pc.createV(v);
			ret = pc.insereix();
			std::vector<PasarelaVideojoc> vpv = cpv.cercaVidejocsRelacionats(nom);
			ret += "\nJocs relacionats:";
			for (int i = 0; i < vpv.size(); i++) {
				if (getEdat(vpv[i].getDataLlansament()) > 0) {
					ret += "\n- " + vpv[i].getNom() + "; " + vpv[i].getDescripcio() + "; " + std::to_string(vpv[i].getPreu()) + " euros.";
				}
			}
		}
	}

	return ret;
}