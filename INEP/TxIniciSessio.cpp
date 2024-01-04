#include "TxIniciSessio.h"
#include "CercadorUsuari.h"
#include "Videoconsola.h"
#include <string>
#include <iostream>

void TxIniciSessio::crear(std::string sU, std::string cU) {
	sobrenomU = sU;
	contrasenyaU = cU;
}

void TxIniciSessio::executar() {
	CercadorUsuari cu;
	PasarelaUsuari u = cu.cercadorUsuari(sobrenomU);
	if (u.obteSobrenom().empty()) {
		std::cerr << "Usuari inexistent" << std::endl;
	}
	else if (u.obteContrasenya() == contrasenyaU) {
		Videoconsola& v = Videoconsola::getInstance();
		v.iniciaSessio(u);
		std::cout << "Hola " << sobrenomU << ", sessio iniciada correctament!" << std::endl;
	}
	else {
		std::cerr << "Hi ha hagut un error amb el sobrenom o la contrasenya" << std::endl;
		std::cout << u.obteContrasenya() << "=" << sobrenomU << "?\n";
	}
}