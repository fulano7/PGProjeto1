#include "camera.h"

// atencao! todas as matrizes sao column-major!

float* camera::extrinsic;

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
	float M[16] = 
	{ 
		s[0], u[0], -f[0], 0.f,
		s[1], u[1], -f[1], 0.f,
		s[2], u[2], -f[2], 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	multiplicaExtrinsicPorMatriz(M);
	nossoTranslate(-eyeX, -eyeY, -eyeZ);
}

void camera::nossoRotate(float angle, float x, float y, float z)
{
	float s = (float)sin(angle);
	float c = (float)cos(angle);
	float v[3] = {x, y, z};
	normalizar(v);
	x = v[0];
	y = v[1];
	z = v[2];
	float M[16] =
	{
		x*x*(1.f-c)+c, y*x*(1.f-c)+z*s, x*z*(1.f-c)-y*s, 0.f,
		x*y*(1.f - c)-z*s, y*y*(1.f - c)+c, y*z*(1.f - c)+x*s, 0.f,
		x*z*(1.f - c)+y*s, y*z*(1.f - c)-x*s, z*z*(1.f - c)+c, 0.f,
		0.f, 0.f, 0.f, 1.f
	};
	multiplicaExtrinsicPorMatriz(M);
}

void camera::nossoTranslate(float x, float y, float z)
{
	float M[16] =
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		x, y, z, 1.f
	};
	multiplicaExtrinsicPorMatriz(M);
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

// inicializando extrinsic com a identidade
void camera::iniciar()
{
	extrinsic = new float[16];
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++) extrinsic[INDICE(i,j,4)] = i == j ? 1.f : 0.f;
	}
}

// libera a memoria alocada para extrinsic.
void camera::liberar()
{
	delete[] extrinsic;
}
