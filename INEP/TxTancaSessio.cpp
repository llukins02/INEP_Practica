#include "TxTancaSessio.h"
#include "Videoconsola.h"
#include <iostream>

void TxTancaSessio::crear(){}

void TxTancaSessio::executar(){
	Videoconsola& v = Videoconsola::getInstance();
	v.tancaSessio();
}