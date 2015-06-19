#ifndef _LUZ_H_
#define _LUZ_H_

#include "common.h"

class Luz{
public:
	Luz();
	Luz(float* p);
	~Luz(); // destrutor padrao

	double Tx, Ty, Tz;
	double Scale;
	float* posicao;
};

#endif//_LUZ_H_
