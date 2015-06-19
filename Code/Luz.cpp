#include "Luz.h"

Luz::Luz()
{
	Tx = Ty = Tz = 0.;
	Scale = 1.;
}

Luz::Luz(float *p) : posicao(p)
{
	Tx = Ty = Tz = 0.;
	Scale = 1.;
}

Luz::~Luz(){} // destrutor padrao
