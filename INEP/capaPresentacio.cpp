// INEP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "TxIniciSessio.h"
#include "TxTancaSessio.h"
#include "TxRegistraUsuari.h"
#include "Videoconsola.h"
#include "TxConsultaUsuari.h"
#include "TxInfoCompres.h"
#include <iostream>
#include <pqxx/pqxx>

using namespace std;

void usuariIS();

void gUsuari() {
	int opcio = 0;
	while (opcio != 4) {
		cout << "------------------" << endl << "  Gestionar Usuari" << endl << "------------------" << endl
			<< "1. Consultar Usuari" << endl << "2. Modificar Usuari" << endl << "3. Esborrar Usuari" << endl << "4. Tornar"
			<< endl << "Opcio: ";
		cin >> opcio;
		cout << endl;
		if (opcio > 4 || opcio < 1) {
			cerr << "Opcio no valida!" << endl;
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
			//Esborrar Usuari
		}
	}
}

void noUsuariIS() {
	int opcio = 0;
	while (opcio != 3) {
		cout << "******************\n  Menu Principal\n******************" << endl
			<< "1. Iniciar Sessio" << endl << "2. Registrar Usuari" << endl << "3. Sortir" << endl << "Opcio: ";

		cin >> opcio;
		cout << endl;
		if (opcio > 3 || opcio < 1) {
			cerr << "Opcio no valida!" << endl;
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
			tx.executar();
			cout << endl;
		}
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
			cerr << "Opcio no valida!" << endl;
		}
		else if (opcio == 1) {
			gUsuari();
		}
		else if (opcio == 2) {
			//consulta compres
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
					noUsuariIS();
					opcio = 5;
				}
			}
		}
	}
}

int main() {
	noUsuariIS();
}
