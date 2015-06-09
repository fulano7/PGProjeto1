#include "camera.h"

// atencao! todas as matrizes sao column-major!

void camera::nossoLookat(
	float eyeX, float eyeY, float eyeZ,
	float centerX, float centerY, float centerZ,
	float upX, float upY, float upZ)
{

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
