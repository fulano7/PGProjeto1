#include "carrega_obj.h"

/* (versao inicial) 
TODO: normais
conforme especificado, se destinara a ler estes arquivos .obj:
http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
outros .obj podem nao ser suportados.
*/
void carregar_obj(char *caminho_arquivo)
{
	std::ifstream arquivo (caminho_arquivo, std::ifstream::in);
	char linha[MAX_CHARS_LINHA];
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
			// vertice
		}
		else if (linha[0] == 'f')
		{
			// face (tratar com e sem normal!)
		}
		else if (linha[0] == '#'){} // comentario
		else
		{
			// nao suportado (?)
		}
	}
}
