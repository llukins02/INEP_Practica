#pragma once
#include <string>
#include <ctime>
class PasarelaUsuari
{
private:
	std::string nomU;
	std::string sobrenomU;
	std::string contrasenyaU;
	std::string correuElectronicU;
	std::string dataNaixamentU;
public:
	void crear(std::string n, std::string s, std::string c, std::string ce, std::string dn);

	void insereix(); //exc{usuariExisteix, correuExisteix}

	void modifica(); //exc{usuariNoExisteix}

	void esborra(); //exc{usuariNoExisteix}

	std::string obteNom();

	std::string obteSobrenom();

	std::string obteContrasenya();

	std::string obteCorreu();

	std::string obteNaixament();
};

