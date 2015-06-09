#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cmath>

#include "common.h"

// indice de um elemento (i, j) (1<=i<=linhas e 1<=j<=colunas) de uma matriz column-major com 'l' linhas
#define INDICE(i, j, l) (((j-1)*l)+(i-1))

namespace camera {
// atencao! todas as matrizes sao column-major!
	void nossoLookat(
		float eyeX, float eyeY, float eyeZ,
		float centerX, float centerY, float centerZ,
		float upX, float upY, float upZ);
	void nossoRotate(float angle, float x, float y, float z);
	void nossoTranslate(float x, float y, float z);
	float* extrinsic = new float[16];
	/*{ 1.f, 0.f, 0.f, 0.f,
						0.f, 1.f, 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f,
						0.f, 0.f, 0.f, 1.f };*/
	void produto_vetorial(float* prod, float* v1, float* v2);
	void normalizar(float* v);
	void multiplicaExtrinsicPorMatriz(float *m);
};

#endif// _CAMERA_H_
