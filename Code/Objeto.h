#ifndef _OBJETO_H_
#define _OBJETO_H_

#include <vector>
#include <string>

#include "common.h"

using std::vector;
using std::string;

/*
modela um objeto.
o atributo 'vertices' eh um vector de coordenadas (x,y,z) que representam
o atributo 'normais' é um vector de coordenadas (x, y, z)
o atributo 'faces'
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

private:
	void calcular_normais();
};

#endif // _OBJETO_H_
