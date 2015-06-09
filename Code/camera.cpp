#include "camera.h"

// atencao! todas as matrizes sao column-major!

void camera::nossoLookat(
	float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ)
{
	float f[3];
	f[0] = centerX - eyeX;
	f[1] = centerY - eyeY;
	f[2] = centerZ - eyeZ;
	float up[3] = {upX, upY, upZ};
	normalizar(f);
	normalizar(up);
	float s[3];
	produto_vetorial(s, f, up);
	normalizar(s);
	float u[3];
	produto_vetorial(u, s, f);
	float M[16];
	for (int i = 1; i <= 3; i++) M[INDICE(1, i, 4)] = s[i - 1];
	for (int i = 1; i <= 3; i++) M[INDICE(2, i, 4)] = u[i - 1];
	for (int i = 1; i <= 3; i++) M[INDICE(3, i, 4)] = -(f[i - 1]);
	for (int i = 1; i <= 3; i++) M[INDICE(4, i, 4)] = 0.f;
	for (int i = 1; i <= 3; i++) M[INDICE(i, 4, 4)] = 0.f;
	M[INDICE(4, 4, 4)] = 1.f;
	multiplicaExtrinsicPorMatriz(M);
	// TODO restante
}

void camera::nossoRotate(float angle, float x, float y, float z)
{

}

void camera::nossoTranslate(float x, float y, float z)
{

}

void camera::produto_vetorial(float* prod, float* v1, float* v2)
{
	prod[0] = v1[1]*v2[2] - v1[2]*v2[1];
	prod[1] = v1[2] * v2[0] - v1[0] * v2[2];
	prod[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void camera::normalizar(float* v)
{
	float norma = (float)sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] /= norma;
	v[1] /= norma;
	v[2] /= norma;
}

// m eh uma matriz 4x4 column-major
void camera::multiplicaExtrinsicPorMatriz(float *m)
{
	float soma;
	float* resultado = new float[16];
	for (int linha = 1; linha <= 4; linha++)
	{
		for (int coluna = 1; coluna <= 4; coluna++)
		{
			soma = 0.f;
			for (int i = 0; i<4; i++) soma += extrinsic[INDICE(linha, i, 4)] * m[INDICE(i, coluna,4)];
			resultado[INDICE(linha, coluna, 4)] = soma;
		}
	}
	// ver se nao vai dar bronca
	delete[] extrinsic;
	extrinsic = resultado;
}

// libera a memoria alocada para extrinsic.
void camera::liberar()
{
	delete[] extrinsic;
}
