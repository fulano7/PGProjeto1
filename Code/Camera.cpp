#include "camera.h"

// inicializando extrinsic
Camera::Camera()
{
	extrinsic = new float[16];
}

// libera a memoria alocada para extrinsic.
Camera::~Camera()
{
	delete[] extrinsic;
}

void Camera::nossoLookat(
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

// angle esta em graus.
void Camera::nossoRotate(float angle, float x, float y, float z)
{
	float angle_rad = grau_para_rad(angle);
	float s = (float)sin(angle_rad);
	float c = (float)cos(angle_rad);
	float v[3] = {x, y, z};
	normalizar(v);
	x = v[0];
	y = v[1];
	z = v[2];
	// M eh a matriz de rotacao construida conforme a formula de rodrigues
	float M[16] =
	{  
		x*x*(1.f - c)+c,     y*x*(1.f - c)+z*s,     x*z*(1.f - c)-y*s,      0.f,
		x*y*(1.f - c)-z*s,   y*y*(1.f - c)+c,       y*z*(1.f - c)+x*s,      0.f,
		x*z*(1.f - c)+y*s,   y*z*(1.f - c)-x*s,     z*z*(1.f - c)+c,        0.f,
		0.f,                  0.f,                  0.f,                    1.f
	};
	multiplicaExtrinsicPorMatriz(M);
}

void Camera::nossoTranslate(float x, float y, float z)
{
	// construindo matriz de translacao
	float M[16] =
	{
		1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		x, y, z, 1.f
	};
	multiplicaExtrinsicPorMatriz(M);
}

void Camera::produto_vetorial(float* prod, float* v1, float* v2)
{
	prod[0] = v1[1] * v2[2] - v1[2] * v2[1];
	prod[1] = v1[2] * v2[0] - v1[0] * v2[2];
	prod[2] = v1[0] * v2[1] - v1[1] * v2[0];
}

void Camera::normalizar(float* v)
{
	float norma = (float)sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);
	v[0] /= norma;
	v[1] /= norma;
	v[2] /= norma;
}

// m eh uma matriz 4x4 column-major
void Camera::multiplicaExtrinsicPorMatriz(float *m)
{
	float soma;
	float* resultado = new float[16];
	for (int linha = 1; linha <= 4; linha++)
	{
		for (int coluna = 1; coluna <= 4; coluna++)
		{
			soma = 0.f;
			for (int i = 1; i<=4; i++) soma += extrinsic[INDICE(linha, i, 4)] * m[INDICE(i, coluna,4)];
			resultado[INDICE(linha, coluna, 4)] = soma;
		}
	}
	delete[] extrinsic;
	extrinsic = resultado;
}

float Camera::grau_para_rad(float grau)
{
	return (grau*PI_SOBRE_180);
}

const float Camera::PI_SOBRE_180 = 3.141459f / 180.f;

void Camera::nossoLoadIdentity()
{
	for (int i = 1; i <= 4; i++)
	{
		for (int j = 1; j <= 4; j++) extrinsic[INDICE(i, j, 4)] = i == j ? 1.f : 0.f;
	}
}
