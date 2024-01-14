#include "TxInfoCompres.h"
#include "Videoconsola.h"
#include "CercadorCompres.h"
#include "configBD.h"
#include <pqxx/pqxx>
#include <iostream>

void TxInfoCompres::crear() {
	Videoconsola& v = Videoconsola::getInstance();
	sobrenomU = v.obteUsuari().obteSobrenom();
}

float TxInfoCompres::executar(int& tV, int& tP) {
	CercadorCompres cc;
	cc.countCompres(sobrenomU, tV, tP);
	if (tV > 0 || tP > 0) {
		return cc.sumPreuCompres(sobrenomU);
	}
	return 0;
}