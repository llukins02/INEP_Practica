#include "TxEsborraUsuari.h"
#include "Videoconsola.h"
#include "PasarelaUsuari.h"

void TxEsborraUsuari::create(std::string cU) {
	contraU = cU;
}

bool TxEsborraUsuari::execute(){
	Videoconsola v = Videoconsola::getInstance();
	PasarelaUsuari usuari = v.obteUsuari();
	if (usuari.obteContrasenya() == contraU) {
		usuari.esborra();
		return true;
	}
	return false;
}