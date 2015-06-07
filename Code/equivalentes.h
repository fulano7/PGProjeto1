#ifndef _EQUIVALENTES_H_
#define _EQUIVALENTES_H_

#include <cmath>

#include "common.h"

namespace equivalentes {
	void nosso_gluLookAt(
		double eyeX, double eyeY, double eyeZ,
		double centerX, double centerY, double centerZ,
		double upX, double upY, double upZ);
	void nosso_glTranslatef(float x, float y, float z);
	void nosso_glRotatef(float angle, float x, float y, float z);
	void nosso_glScalef(float x, float y, float z);
}
#endif // _EQUIVALENTES_H_