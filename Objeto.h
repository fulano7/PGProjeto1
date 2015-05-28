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
	vector <unsigned int *> faces;
	string nome;

	Objeto(const float *vertices, const float* normais, const unsigned int * faces);
	~Objeto();
};