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
carrega um arquivo .obj cujo caminho eh caminho_arquivo.
*/
int carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo);

#endif//_CARREGA_OBJ_H_
