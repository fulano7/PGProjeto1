#ifndef _OBJETO_H_
#define _OBJETO_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

#include "common.h"

#define MAX_CHARS_LINHA 201
#define MAX_OBJS_ARQUIVO 2

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
	string nome;

	Objeto(); // construtor padrao
	Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs);
	Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs, const string* nm);
	~Objeto();

	void renderizar();

	/*
	conforme especificado, se destinara a ler estes arquivos .obj:
	http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
	outros .obj podem nao ser suportados.
	carrega um arquivo .obj cujo caminho eh caminho_arquivo,
	armazena os objetos que estavam no arquivo no array 'array_de_objetos'
	e retorna a quantidade de objetos que estavam no arquivo.
	o numero maximo de objetos suportado num arquivo .obj eh fixado
	em MAX_OBJS_ARQUIVO.
	*/
	static int carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo);

private:
	
	vector <float*> vertices;
	vector <float*> normais;
	vector <int*> faces;

	void calcular_normais();

	/*
	retorna quantas vezes o caractere 'caractere' aparece na palavra 'palavra'
	*/
	static int ocorrencias(const char* palavra, const char caractere);
};

#endif // _OBJETO_H_
