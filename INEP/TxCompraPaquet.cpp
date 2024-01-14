#include "TxCompraPaquet.h"
#include "CercadorElemCompra.h"
#include "CercadorPaquetVideojoc.h"
#include "CercadorCompres.h"
#include "Videoconsola.h"

std::string TxCompraPaquet::crear(std::string nom, bool &error) {
	CercadorElemCompra cec;
	CercadorPaquetVideojoc cpv;
	std::string ret;
	PasarelaElemCompra ec = cec.cerca(nom);
	pv = cpv.cerca(nom, ec);
	if (pv.getTipus() != "paquet") {
		ret = "Error: aquest paquet no existeix!"+ec.getTipus();
		error = true;
	}
	else {
		float preuVideojocs = 0;
		std::string aux = "";
		for (int i = 0; i < pv.getVideojocs().size(); i++) {
			preuVideojocs += pv.getVideojocs()[i].getPreu();
			aux += "\n- " + pv.getVideojocs()[i].getNom() + "; " + pv.getVideojocs()[i].getDescripcio() + "; " + std::to_string(pv.getVideojocs()[i].getPreu()) + " euros";
		}
		ret = "Informacio paquet ...\nNom paquet: " + pv.getNom() + "\nDescripcio: " + pv.getDescripcio() + "\nPreu: " + std::to_string(pv.getPreu()) +
			" euros (estalvi de " + std::to_string(preuVideojocs - pv.getPreu()) + " euros)\n\nJocs inclosos:"+aux;
	}
	return ret;
}

std::string TxCompraPaquet::executa() {
	std::string nom = pv.getNom();
	Videoconsola vc = Videoconsola::getInstance();
	CercadorPaquetVideojoc cpv;
	CercadorCompres cc;
	std::string ret;
	std::vector<PasarelaCompra> vpc = cc.obteCompresUsuari(vc.obteUsuari());
	bool teElPaquet = false;

	int i = 0;
	while (i < vpc.size() && !teElPaquet) {
		if (vpc[i].getTipus() == "paquet") {
			if (vpc[i].getVideojoc().getNom() == nom) {
				teElPaquet = true;
			}
		}
		i++;
	}
	if (teElPaquet) {
		ret = "Error: l'usuari ja te en propietat el paquet: " + nom + "!";
	}
	else {
		auto now = (std::chrono::system_clock::now());
		std::string data = std::format("{:%d}", now) + "-" + std::format("{:%m}", now) + "-" + std::format("{:%Y}", now) + " " + std::format("{:%X}", now);
		PasarelaCompra pc;
		pc.create(vc.obteUsuari(), data, pv.getPreu());
		pc.createPV(pv);
		ret = pc.insereix();
	}
	return ret;
}