#include "Objeto.h"

Objeto::Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs) : vertices(*vs), normais(*ns), faces(*fs)
{}

Objeto::Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs, const string* nm) : vertices(*vs), normais(*ns), faces(*fs), nome(*nm)
{}

Objeto::~Objeto()
{
	for (int i = 0; i < vertices.size(); i++) delete[] vertices.at(i);
	for (int i = 0; i < normais.size(); i++) delete[] normais.at(i);
	for (int i = 0; i < faces.size(); i++) delete[] faces.at(i);
}
