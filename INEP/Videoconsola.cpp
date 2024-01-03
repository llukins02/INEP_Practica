#include "Videoconsola.h"

PasarelaUsuari Videoconsola::obteUsuari(){
	return usuari;
}

void Videoconsola::iniciaSessio(PasarelaUsuari u){
	usuari = u;
}

void Videoconsola::tancaSessio(){
	PasarelaUsuari u;
	usuari = u;
}