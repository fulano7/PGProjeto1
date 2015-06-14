#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cmath>

// indice de um elemento (i, j) (1<=i<=linhas e 1<=j<=colunas) de uma matriz column-major com 'l' linhas
#define INDICE(i, j, l) (((j-1)*l)+(i-1))

class Camera {
// atencao! todas as matrizes sao column-major!
public:
	Camera();
	~Camera();

	void nossoLookat(
		float eyeX, float eyeY, float eyeZ,
		float centerX, float centerY, float centerZ,
		float upX, float upY, float upZ);
	void nossoRotate(float angle, float x, float y, float z); // angle esta em graus.
	void nossoTranslate(float x, float y, float z);
	float* extrinsic;
	static float grau_para_rad(float grau);
	void nossoLoadIdentity();
private:
	static void produto_vetorial(float* prod, float* v1, float* v2);
	static void normalizar(float* v);
	void multiplicaExtrinsicPorMatriz(float *m);
	static const float PI_SOBRE_180;
};

#endif// _CAMERA_H_
