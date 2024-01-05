// INEP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "configBD.h"
#include "TxIniciSessio.h"
#include "TxTancaSessio.h"
#include "TxRegistraUsuari.h"
#include "Videoconsola.h"
#include "TxConsultaUsuari.h"
#include "TxInfoCompres.h"
#include "TxEsborraUsuari.h"
#include <iostream>
#include <pqxx/pqxx>

using namespace std;

void usuariIS();
void noUsuariIS();

void gUsuari() {
	int opcio = 0;
	while (opcio != 4) {
		cout << "------------------" << endl << "  Gestionar Usuari" << endl << "------------------" << endl
			<< "1. Consultar Usuari" << endl << "2. Modificar Usuari" << endl << "3. Esborrar Usuari" << endl << "4. Tornar"
			<< endl << "Opcio: ";
		cin >> opcio;
		cout << endl;
		if (opcio > 4 || opcio < 1) {
			cerr << "Opcio no valida!\n" << endl;
		}
		else if (opcio == 1) {
			cout << "** Consulta usuari **\n";
			TxConsultaUsuari txCU;
			TxInfoCompres txIC;
			txCU.crear();
			txIC.crear();
			std::vector<std::string> infoUsuari = txCU.executar();
			int tVideojocs, tPaquets;
			cout << "Nom Complet: " << infoUsuari[0] << "\nSobrenom: " << infoUsuari[1] << "\nCorreu Electronic: " << infoUsuari[2] << "\nData Naixement: " << infoUsuari[3];
			float tEuros = txIC.executar(tVideojocs, tPaquets);
			cout << endl << tVideojocs << " videojocs comprats\n" << tPaquets << " paquets de videojocs comprats\n" << tEuros << " euros gastats en total\n\n";
		}
		else if (opcio == 2) {
			//Modificar Usuari
		}
		else if (opcio == 3) {
			string c;
			cout << "** Esborrar usuari **\nAdvertencia! El proces d'esborrar no es reversible, perdàs tots els teus videojocs i el teu compte"
				"\nPer confirmar l'esborrat, s'ha d'entrar la contrasenya...\nContrasenya: ";
			cin.ignore();
			getline(cin, c);
			TxEsborraUsuari tx;
			tx.create(c);
			bool borrat = tx.execute();
			if (borrat) { 
				cout << "Usuari borrat correctament!\n\n";
				TxTancaSessio tx;
				tx.crear();
				tx.executar();
				noUsuariIS();
				opcio = 4;
			}
			else { cout << "Contrasenya incorrecta, no s'ha borrat l'usuari.\n\n"; }
		}
		cout << endl;
	}
}

void gCompra() {
	int opcio = 0;
	while (opcio != 4) {
		cout << "------------------" << endl << "  Gestionar Compres" << endl << "------------------" << endl
			<< "1. Comprar Videojoc" << endl << "2. Comprar Paquet" << endl << "3. Consultar Compres" << endl << "4. Tornar"
			<< endl << "Opcio: ";
		cin >> opcio;
		if (opcio > 4 || opcio < 1) {
			cerr << "Opcio no valida!\n" << endl;
		}
		else if (opcio == 1) {
			//Comprar videojoc	
		}
		else if (opcio == 2) {
			//Modificar Usuari
		}
		else if (opcio == 3) {
			//Veure compres
		}
		cout << endl;
	}
}

void noUsuariIS() {
	int opcio = 0;
	while (opcio != 3) {
		cout << "******************\n  Menu Principal\n******************" << endl << "0. Configurar BD\n"
			<< "1. Iniciar Sessio" << endl << "2. Registrar Usuari" << endl << "3. Sortir" << endl << "Opcio: ";

		cin >> opcio;
		cout << endl;
		if (opcio > 3 || opcio < 0) {
			cerr << "Opcio no valida!\n" << endl;
		}
		else if (opcio == 0) {
			configBD bd = configBD::getInstance();
			string n, u, p, a, po;
			cout << "BD actual = (" + bd.getString() + ")\n"
			"Introdueix els seguents camps en l'ordre donat:\ndbname:\nuser:\npassword:\nhostaddr:\nport:\n";
			cin >> n >> u >> p >> a >> po;
			bool created = bd.create(n, u, p, a, po);
			if (created){ cout << "Connexio a la base de dades feta correctament!\n\n"; }
			else { cerr << "No es possible connectar-se a la BD, dades incorrectes\n\n"; }
		}
		else if (opcio == 1) {
			string s, c;
			cout << "** Inici Sessio **\nSobrenom: ";
			cin >> s;
			cout << "Contrasenya: ";
			cin >> c;
			TxIniciSessio tx;
			tx.crear(s, c);
			tx.executar();
			Videoconsola& v = Videoconsola::getInstance();
			if (!v.obteUsuari().obteSobrenom().empty()) {
				cout << endl;
				usuariIS();
				opcio = 3;
			}
		}
		else if (opcio == 2) {
			string n, s, c, ce, dn;
			cout << "** Registrar usuari **\n Omplir la informacio que es demana ..." << endl << "Nom Complet: ";
			cin.ignore();
			getline(cin, n);
			cout << "Sobrenom: ";
			getline(cin, s);
			cout << "Contrasenya: ";
			getline(cin, c);
			cout << "Correu Electronic: ";
			getline(cin, ce);
			cout << "Data Naixement (DD/MM/AAAA): ";
			getline(cin, dn);
			TxRegistraUsuari tx;
			tx.crear(n, s, c, ce, dn);
			cout << tx.executar();
		}
		cout << endl;
	}
}

void usuariIS() {
	int opcio = 0;
	while (opcio != 5) {
		cout << "******************" << endl << "  Menu Principal" << endl << "******************" << endl
			<< "1. Gestionar Usuari" << endl << "2. Consultar Compres" << endl << "3. Consultar Videojocs" << endl << "4. Tancar Sessio"
			<< endl << "5. Sortir" << endl << "Opcio: ";
		cin >> opcio;
		cout << endl;
		if (opcio > 5 || opcio < 1) {
			cerr << "Opcio no valida!\n" << endl;
		}
		else if (opcio == 1) {
			gUsuari();
		}
		else if (opcio == 2) {
			gCompra();
		}
		else if (opcio == 3) {
			//consulta videojoc
		}
		else if (opcio == 4) {
			string confirmacio = "";
			while (confirmacio != "S" && confirmacio != "N") {
				cout << "** Tancar sessio **\nSegur que vols tancar la sessio? (S/N): ";
				cin >> confirmacio;
				if (confirmacio != "S" && confirmacio != "N"){
					cout << "caracter no valid, escriu 'S' per tancar la sessio i 'N' per mantenir-la" << endl;
				}
			}
			if (confirmacio == "S") {
				TxTancaSessio tx;
				tx.crear();
				tx.executar();
				Videoconsola& v = Videoconsola::getInstance();
				if (v.obteUsuari().obteSobrenom().empty()) {
					cout << "Sessio tancada correctament!\n" << endl;
					noUsuariIS();
					opcio = 5;
				}
			}
		}
		cout << endl;
	}
}

int main() {
	noUsuariIS();
}

