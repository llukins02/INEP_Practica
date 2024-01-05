#pragma once
#include "PasarelaElemCompra.h"
#include "PasarelaUsuari.h"
#include <string>
#include <vector>

class PasarelaCompra
{
private:
	PasarelaElemCompra ElemCompra;
	PasarelaUsuari usuari;

public:
	void create(PasarelaElemCompra EC, PasarelaUsuari u);
};

