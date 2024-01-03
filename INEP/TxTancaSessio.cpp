#include "TxTancaSessio.h"
#include "Videoconsola.h"
#include <iostream>

void TxTancaSessio::crear(){}

void TxTancaSessio::executar(){
	Videoconsola& v = Videoconsola::getInstance();
	v.tancaSessio();
	std::cout << "Sessio tancada correctament!" << std::endl;
}