#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <cmath>

#include "common.h"

namespace camera {
// atencao! todas as matrizes sao column-major!
	void nossoLookat(
		float eyeX, float eyeY, float eyeZ,
		float centerX, float centerY, float centerZ,
		float upX, float upY, float upZ);
	void nossoRotate(float angle, float x, float y, float z);
	void nossoTranslate(float x, float y, float z);
	float extrinsic[] = {1.f, 0.f, 0.f, 0.f,
						0.f, 1.f, 0.f, 0.f,
						0.f, 0.f, 1.f, 0.f,
						0.f, 0.f, 0.f, 1.f };
	void produto_vetorial(float* prod, float* v1, float* v2);
	void normalizar(float* v);
};

#endif// _CAMERA_H_
