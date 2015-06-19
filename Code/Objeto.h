#ifndef _OBJETO_H_
#define _OBJETO_H_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>

#include "common.h"

#define MAX_CHARS_LINHA 201
#define MAX_OBJS_ARQUIVO 12

using std::vector;
using std::string;


/*
modela um objeto.
o atributo 'vertices' eh um vector de coordenadas (x,y,z) que representam cada ponto do objeto.
o atributo 'normais' eh um vector de coordenadas (x, y, z) que representam os vetores normais descritos no arquivo
  ou calculados internamente conforme necessario.
o atributo 'faces' eh um vector de array de inteiros em que cada elemento do vector
  eh um array no formato:
  (quant_vertices, v1, v2, ..., vn) -> array de tamanho (quant_vertices+1).
                                       na primeira posicao a quantidade de vertices da face
									   e nas seguintes o conjunto de vetices que formam a face.
o atributo 'indNormais' eh um vector de array de inteiros em que cada elemento do vector
  eh um array no formato:
  (quant_normais, vn1, vn2, ..., vnn) -> (analogo a 'faces')
*/
class Objeto
{
public:
	string nome;

	Objeto(); // construtor padrao
	~Objeto();

	// desenha o objeto com a biblioteca opengl.
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

	//translada o obj no eixo selecionado em 0.2
	void translateObj(int t, float s);
	//translada entre a origem e a pos inicial
	void tOriPos(double x, double y, double z);

	//aplia a operação de escala
	void escale(float i);

	void directEscale(float s);

	//roda o obj em um dos eixos
	void Objeto::rotateObj(int eixo);

	static float grau_para_rad(float grau);
	
private:
	bool firstLoad = true;
	static const float PI_SOBRE_180;
	float initMod[4];//informações de escala [0] e translacao iniciais pra num criar um em cima do outro
	float cores[3];
	double translacoes[3]; //guarda a translacao do eixo do mundo para a atual posicao do obj
	vector <float*> vertices;
	vector <int> vNormais;//contador de normais associadas aos vertices
	vector <float*> normais;
	vector <int*> faces; // lista de faces na forma (v1, v2, ..., vn)
	vector <int*> indNormais; //para o caso de "//" : lista de faces na forma (vn1, vn2, ..., vnn)

	// calcula as normais da face se for necessario.
	float* calcular_normais_face(int *atual);

	// calcula as normais dos vertices
	void calcular_normais_vert();

	//retorna quantas vezes o caractere 'caractere' aparece na palavra 'palavra'
	static int ocorrencias(const char* palavra, const char caractere);

	
};

#endif // _OBJETO_H_
