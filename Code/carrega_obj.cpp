#include "carrega_obj.h"

/* (versao inicial) 
TODO: normais
conforme especificado, se destinara a ler estes arquivos .obj:
http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
outros .obj podem nao ser suportados, e este algoritmo nao detecta erros no arquivo.
*/

int ocorrencias(const char* palavra, const char caractere)
{
	int resposta = 0;
	int i = 0;
	char atual = palavra[i];
	while (atual != '\0')
	{
		if (atual == caractere) resposta++;
		atual = palavra[++i];
	}
	return resposta;
}

int carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo)
{
	array_de_objetos = new Objeto[MAX_OBJS_ARQUIVO]();
	std::ifstream arquivo (caminho_arquivo, std::ifstream::in);
	char linha[MAX_CHARS_LINHA];
	
	bool precisa_normais = true;// variavel que diz se precisa calcular as normais

	int indice = -1; // armazena a proxima posicao livre do array recebido como parametro.
	// um mesmo arquivo pode ter varios objetos.
	// se o arquivo tiver mais de um objeto, vamos adicionando os seguintes ao array.

	// primeira chamada de leitura do arquivo.
	arquivo.getline(linha, MAX_CHARS_LINHA);

	// enquanto o arquivo nao terminar
	while (!arquivo.eof())
	{
		#ifdef DEBUG
		std::cout << linha << std::endl;
		#endif
		if (linha[0] == 'v' && linha[1] == 'n') // normal
		{
			precisa_normais = false;
		}
		else if (linha[0] == 'v') // vertice
		{
			precisa_normais = true; // resetando esta variavel
			indice++; // avancando no array
			char* proximo; // gamb
			do
			{
				// colocando coordenadas x, y e z
				proximo = strtok(linha, " ");
				array_de_objetos[indice].vertices.push_back(new float[3]);
				array_de_objetos[indice].vertices.back()[0] = strtof((strtok(NULL, " ")), &proximo);
				array_de_objetos[indice].vertices.back()[1] = strtof((strtok(NULL, " ")), &proximo);
				array_de_objetos[indice].vertices.back()[2] = strtof((strtok(NULL, " ")), &proximo);
				arquivo.getline(linha, MAX_CHARS_LINHA);
			}while (linha[0] == 'v');

		}
		else if (linha[0] == 'f') // face
		{
			
			if (strstr(linha, "/") != NULL) // com normal.
			{
				if (strstr(linha, "//") != NULL) // com normal e sem textura
				{
				}
				else // com normal e com indice da textura que deve ser ignorado.
				{
				}
			}
			else // sem normal.
			{
				char* proximo; // gamb
				do
				{
					// colocando faces
					int num_faces = ocorrencias(linha, ' ');
					proximo = strtok(linha, " ");
					array_de_objetos[indice].faces.push_back(new int[num_faces]);
					for (int i = 0; i < num_faces; i++) array_de_objetos[indice].faces.back()[i] = atoi((strtok(NULL, " "))); // cuidado com atoi
					arquivo.getline(linha, MAX_CHARS_LINHA);
				} while (linha[0] == 'f');
			}
		}
		else if (linha[0] == '#')arquivo.getline(linha, MAX_CHARS_LINHA); // comentario
		else arquivo.getline(linha, MAX_CHARS_LINHA); // nao suportado; nao tratado
	}
	return (indice+1);
}
