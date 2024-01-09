#include "TxCompraVidejoc.h"
#include "Videoconsola.h"
#include "CercadorElemCompra.h"
#include "CercadorVideojoc.h"
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
	int edat = na - da;

	// Adjust for the month and day
	if (nm < dm || (nm == dm && nd < dd)) {
		edat--;
	}
	return edat;
}

std::string TxCompraVidejoc::crear(std::string nom){
	CercadorElemCompra cec;
	CercadorVideojoc cv;
	std::string ret;
	PasarelaElemCompra ec = cec.cerca(nom);
	PasarelaVideojoc v = cv.cerca(nom, ec);
	if (v.getTipus() != "videojoc") {
		ret = "Error: aquest videojoc no existeix!";
	}
	return ret;
}

std::string TxCompraVidejoc::executa(){
	std::string nom = v.getNom();
	Videoconsola vc = Videoconsola::getInstance();
	CercadorElemCompra cec;
	CercadorVideojoc cv;
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
		int edatUsuari = getEdat(vc.obteUsuari().obteNaixament());
		if(edatUsuari < v.getQualificacioEdat()){
			ret = "Error: El videojoc: " + nom + "te una restriccio d'edat que l'usuari no compleix! (edatUsuari = "+std::to_string(edatUsuari) + "; restricioEdat = " + std::to_string(v.getQualificacioEdat());
		}
		else if (true) {
			ret = " meh";
		}
	}

	return ret;
}