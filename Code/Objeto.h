#ifndef _OBJETO_H_
#define _OBJETO_H_

#include <vector>
#include <string>

#include "common.h"

using std::vector;
using std::string;

/*
modela um objeto.
o atributo 'vertices' eh um vector de coordenadas (x,y,z) que representam cada ponto do objeto.
o atributo 'normais' eh um vector de coordenadas (x, y, z) que representam os vetores normais descritos no arquivo
  ou calculados internamente conforme necessario.
o atributo 'faces' eh um vector de array de inteiros (i1, i2, ... in) em que cada elemento do vector
  representa o conjunto de vetices que forma a face.
*/
class Objeto
{
public:
	vector <float*> vertices;
	vector <float*> normais;
	vector <int*> faces;
	string nome;

	Objeto(); // construtor padrao
	Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs);
	Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs, const string* nm);
	~Objeto();

	void renderizar();
	void calcular_normais();
};

#endif // _OBJETO_H_
