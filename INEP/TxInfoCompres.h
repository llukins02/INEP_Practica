#pragma once
#include "Transaccio.h"
class TxInfoCompres : Transaccio
{
private:
	std::string sobrenomU;
	int totalVideo;
	int totalPaquet;
	float totalEuros;

public:
	void crear();

	float executar(int& tV, int& tP);
};

