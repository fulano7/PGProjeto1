#ifndef _OBJETO_H_
#define _OBJETO_H_

#include <vector>
#include <string>

#include "common.h"

using std::vector;
using std::string;

class Objeto
{
public:
	vector <float*> vertices;
	vector <float*> normais;
	vector <int*> faces;
	string nome;

	Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs);
	Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs, const string* nm);
	~Objeto();
};

#endif // _OBJETO_H_
