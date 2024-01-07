#include "TxConsultaCompres.h"
#include "CercadorCompres.h"

void TxConsultaCompres::consultaVideojocs() {
	Videoconsola v = Videoconsola::getInstance();
	CercadorCompres cc;
	pcs = cc.obteCompresUsuari(v.obteUsuari());
}

std::vector<PasarelaCompra> TxConsultaCompres::getCompres() {
	return pcs;
}