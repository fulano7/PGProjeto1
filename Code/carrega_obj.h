#ifndef _CARREGA_OBJ_H_
#define _CARREGA_OBJ_H_

/*
conforme especificado, se destinara a ler estes arquivos .obj:
http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
outros .obj podem nao ser suportados.
*/

#include <vector>
#include <iostream>
#include <fstream>
#include <cstring>

#include "common.h"
#include "Objeto.h"

#define MAX_CHARS_LINHA 201
#define MAX_OBJS_ARQUIVO 2

/*
retorna quantas vezes o caractere 'caractere' aparece na palavra 'palavra'
*/
int ocorrencias(const char* palavra, const char caractere);

/*
carrega um arquivo .obj cujo caminho eh caminho_arquivo e retorna
um array com os objetos que estavam no arquivo.
o numero maximo de objetos suportado num arquivo .obj eh fixado
em MAX_OBJS_ARQUIVO.
*/
int carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo);

#endif//_CARREGA_OBJ_H_
