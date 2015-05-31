#include "Objeto.h"

Objeto::Objeto(){}; // construtor padrao

/*
os 2 construtores abaixo devem ser reavaliados (devido a operacao custosa de inicializacao dos atributos, com copia)
e podem ficar fora da versao final
*/
Objeto::Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs) : vertices(*vs), normais(*ns), faces(*fs)
{}

Objeto::Objeto(const vector<float*>* vs, const vector<float*>* ns, const vector<int*>* fs, const string* nm) : vertices(*vs), normais(*ns), faces(*fs), nome(*nm)
{}

Objeto::~Objeto()
{
	// podemos fazer cast de unsigned para int jah que o tamanho do vetor nao sera absurdamente grande
	for (int i = 0; i < (int)vertices.size(); i++) delete[] vertices.at(i);
	for (int i = 0; i < (int)normais.size(); i++) delete[] normais.at(i);
	for (int i = 0; i < (int)faces.size(); i++) delete[] faces.at(i);
}

int Objeto::ocorrencias(const char* palavra, const char caractere)
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

/* (versao inicial)
TODO: normais
conforme especificado, se destinara a ler estes arquivos .obj:
http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
outros .obj podem nao ser suportados, e este algoritmo nao detecta erros no arquivo.
*/
int Objeto::carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo)
{
	array_de_objetos = new Objeto[MAX_OBJS_ARQUIVO]();
	std::ifstream arquivo(caminho_arquivo, std::ifstream::in);
	char linha[MAX_CHARS_LINHA];

	int indice = -1; // armazena a proxima posicao livre do array recebido como parametro.
	// um mesmo arquivo pode ter varios objetos.
	// se o arquivo tiver mais de um objeto, vamos adicionando os seguintes ao array.

	// primeira chamada de leitura do arquivo.
	arquivo.getline(linha, MAX_CHARS_LINHA);

	// enquanto o arquivo nao terminar
	while (!arquivo.eof())
	{

		if (linha[0] == 'v' && linha[1] == 'n') // normal
		{
			char* proximo; // gamb
			do // este laco le todas as normais
			{
				// colocando coordenadas x, y e z das normais
				proximo = strtok(linha, " ");
				array_de_objetos[indice].normais.push_back(new float[3]);
				array_de_objetos[indice].normais.back()[0] = strtof((strtok(NULL, " ")), &proximo);
				array_de_objetos[indice].normais.back()[1] = strtof((strtok(NULL, " ")), &proximo);
				array_de_objetos[indice].normais.back()[2] = strtof((strtok(NULL, " ")), &proximo);
				arquivo.getline(linha, MAX_CHARS_LINHA);
			} while (linha[0] == 'v' && linha[1] == 'n');
		}
		else if (linha[0] == 'v') // vertice
		{
			indice++; // avancando no array
			char* proximo; // gamb
			do // este laco le todos os vertices
			{
				// colocando coordenadas x, y e z
				proximo = strtok(linha, " ");
				array_de_objetos[indice].vertices.push_back(new float[3]);
				array_de_objetos[indice].vertices.back()[0] = strtof((strtok(NULL, " ")), &proximo);
				array_de_objetos[indice].vertices.back()[1] = strtof((strtok(NULL, " ")), &proximo);
				array_de_objetos[indice].vertices.back()[2] = strtof((strtok(NULL, " ")), &proximo);
				arquivo.getline(linha, MAX_CHARS_LINHA);
			} while (linha[0] == 'v' && linha[1] != 'n');

		}
		else if (linha[0] == 'f') // face
		{
			
			array_de_objetos[indice].calcular_normais(); // neste ponto ja terminamos de armazenar (ou nao) as normais.
			// este metodo calcula as normais se e somente se for necessario :D

			if (strstr(linha, "/") != NULL) // com normal.
			{
				array_de_objetos[indice].normais_vinc_faces = true;
				if (strstr(linha, "//") != NULL) // com normal e sem textura
				{
					char* proximo; // gamb
					do // este laco le todas as faces
					{
						// colocando faces
						int num_faces = ocorrencias(linha, ' ');
						proximo = strtok(linha, " ");
						array_de_objetos[indice].faces.push_back(new int[(2*num_faces) + 1]);
						array_de_objetos[indice].faces.back()[0] = num_faces;
						for (int i = 1; i < (2 * num_faces) + 1; i += 2)
							sscanf(strtok(NULL, " "), "%d//%d", &(array_de_objetos[indice].faces.back()[i]), &(array_de_objetos[indice].faces.back()[i + 1]));
						arquivo.getline(linha, MAX_CHARS_LINHA);
					} while (linha[0] == 'f');
				}
				else // com normal e com indice da textura que deve ser ignorado.
				{
				}
			}
			else // sem normal.
			{
				array_de_objetos[indice].normais_vinc_faces = false;
				char* proximo; // gamb
				do // este laco le todas as faces
				{
					// colocando faces
					int num_faces = ocorrencias(linha, ' ');
					proximo = strtok(linha, " ");
					array_de_objetos[indice].faces.push_back(new int[num_faces+1]);
					array_de_objetos[indice].faces.back()[0] = num_faces;
					for (int i = 1; i <= num_faces; i++)
						array_de_objetos[indice].faces.back()[i] = atoi((strtok(NULL, " "))); // cuidado com atoi
					arquivo.getline(linha, MAX_CHARS_LINHA);
				} while (linha[0] == 'f');
			}
		}
		else if (linha[0] == '#')
			arquivo.getline(linha, MAX_CHARS_LINHA); // comentario
		else
			arquivo.getline(linha, MAX_CHARS_LINHA); // nao suportado; nao tratado
	}
	return (indice + 1);
}

void Objeto::calcular_normais()
{
	if (normais.size() == 0)
	{
	}
}

void Objeto::renderizar()
{
	if (normais_vinc_faces)
	{

	}
	else
	{

	}
}