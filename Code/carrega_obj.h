#ifndef _CARREGA_OBJ_H_
#define _CARREGA_OBJ_H_

#include <vector>
#include <iostream>
#include <fstream>

#include "common.h"

#define MAX_CHARS_LINHA 201

/*
carrega um arquivo .obj cujo caminho eh caminho_arquivo.
*/
void carregar_obj(char *caminho_arquivo);

#endif//_CARREGA_OBJ_H_