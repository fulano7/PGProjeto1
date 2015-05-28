#ifndef _CARREGA_OBJ_H_
#define _CARREGA_OBJ_H_

#include <vector>
#include <iostream>
#include <fstream>

#include "common.h"
#include "Objeto.h"

#define MAX_CHARS_LINHA 201

/*
carrega um arquivo .obj cujo caminho eh caminho_arquivo.
*/
Objeto* carregar_obj(const char *caminho_arquivo);

#endif//_CARREGA_OBJ_H_