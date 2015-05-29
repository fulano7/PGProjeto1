#include "carrega_obj.h"

/* (versao inicial) 
TODO: normais
conforme especificado, se destinara a ler estes arquivos .obj:
http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
outros .obj podem nao ser suportados, e este algoritmo nao detecta erros no arquivo.
*/
int carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo)
{
	array_de_objetos = new Objeto[MAX_OBJS_ARQUIVO]();
	std::ifstream arquivo (caminho_arquivo, std::ifstream::in);
	char linha[MAX_CHARS_LINHA];
	bool precisa_normais = true;// variavel que diz se precisa calcular as normais
	int indice = 0; // armazena a proxima posicao livre do array recebido como parametro.
	// um mesmo arquivo pode ter varios objetos.
	// se o arquivo tiver mais de um objeto, vamos adicionando os seguintes ao array.
	while (arquivo.getline(linha, MAX_CHARS_LINHA))
	{
		#ifdef DEBUG
		std::cout << linha << std::endl;
		#endif
		if (linha[0] == 'v' && linha[1] == 'n')
		{
			// normal
		}
		else if (linha[0] == 'v')
		{
			precisa_normais = true;
			char* proximo = strtok(linha, " ");
			do
			{
				array_de_objetos[indice].vertices.push_back(new float[3]);
				array_de_objetos[indice].vertices.back()[0] = strtof((strtok(NULL, " ")), NULL);
				array_de_objetos[indice].vertices.back()[1] = strtof((strtok(NULL, " ")), NULL);
				array_de_objetos[indice].vertices.back()[2] = strtof((strtok(NULL, " ")), NULL);
				arquivo.getline(linha, MAX_CHARS_LINHA);
			}while (linha[0] == 'v');
			delete[] proximo;
			indice++;
			// vertice
		}
		else if (linha[0] == 'f')
		{
			// face (tratar com e sem normal!)
		}
		else if (linha[0] == '#'); // comentario
		else
		{} // nao suportado; nao tratado
	}
	return 0; // para poder compilar por enquanto
}
