#include "TxRegistraUsuari.h"
#include "PasarelaUsuari.h"

// mirar que fer amb el std::string
void TxRegistraUsuari::crear(std::string nU, std::string sU, std::string cU, std::string ceU, std::string dU) {
	nomU = nU;
	sobrenomU = sU;
	contrasenyaU = cU;
	correuElectronicU = ceU;
	dataNaixamentU = dU;
}

void TxRegistraUsuari::executar(){
	PasarelaUsuari u;
	u.crear(nomU, sobrenomU, contrasenyaU, correuElectronicU, dataNaixamentU);
	u.insereix();
}