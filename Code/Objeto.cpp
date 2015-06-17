#include "Objeto.h"

Objeto::Objeto(){}; // construtor padrao

Objeto::~Objeto()
{
	// podemos fazer cast de unsigned para int jah que o tamanho do vetor nao sera absurdamente grande
	for (int i = 0; i < (int)vertices.size(); i++) delete[] vertices.at(i);
	for (int i = 0; i < (int)normais.size(); i++) delete[] normais.at(i);
	for (int i = 0; i < (int)faces.size(); i++) delete[] faces.at(i);
	for (int i = 0; i < (int)indNormais.size(); i++) delete[] indNormais.at(i);
}

int Objeto::ocorrencias(const char* palavra, const char caractere)
{
	int resposta = 0;
	int i = 0;
	char atual = palavra[i];
	while (atual != '\0')
	{
		if (atual == caractere && palavra[i+1] != '\0') resposta++;
		atual = palavra[++i];
	}
	return resposta;
}

/* (versao inicial)
conforme especificado, se destinara a ler estes arquivos .obj:
http://cin.ufpe.br/~marcelow/Marcelow/arquivos_obj.html
outros .obj podem nao ser suportados, e este algoritmo nao detecta erros no arquivo.
*/
int Objeto::carregar_obj(Objeto*& array_de_objetos, const char *caminho_arquivo)
{
	array_de_objetos = new Objeto[MAX_OBJS_ARQUIVO]();
	
	char linha[MAX_CHARS_LINHA];

	int indice = -1; // armazena a proxima posicao livre do array recebido como parametro.
	// um mesmo arquivo pode ter varios objetos.
	// se o arquivo tiver mais de um objeto, vamos adicionando os seguintes ao array.

	char * prefix = "Obj Files/";
	char * sufix = ".obj";
	char aux [30];

	char nextObj[MAX_CHARS_LINHA];
	std::ifstream arquivosObj(caminho_arquivo, std::ifstream::in);
	
	while (!arquivosObj.eof()){
		char *obj;
		arquivosObj.getline(nextObj, MAX_CHARS_LINHA);

		obj = strtok(nextObj, " ");
		strcpy(aux, prefix);
		strcat(aux, obj);
		strcat(aux, sufix);
		std::cout << indice << std::endl;
		array_de_objetos[indice+1].cores[0] = strtof((strtok(NULL, " ")), &obj);
		array_de_objetos[indice+1].cores[1] = strtof((strtok(NULL, " ")), &obj);
		array_de_objetos[indice+1].cores[2] = strtof((strtok(NULL, " ")), &obj);

		std::ifstream arquivo(aux, std::ifstream::in);
		// primeira chamada de leitura do arquivo do obj.
		arquivo.getline(linha, MAX_CHARS_LINHA);

		// enquanto o arquivo obj nao terminar
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

				//array_de_objetos[indice].calcular_normais(); // neste ponto ja terminamos de armazenar (ou nao) as normais.
				// este metodo calcula as normais se e somente se for necessario :D
				
				if (strstr(linha, "/") != NULL) // com normal.
				{
					//array_de_objetos[indice].normais_vinc_faces = true;
					if (strstr(linha, "//") != NULL) // com normal e sem textura
					{
						std::cout << "NORMAL SEM TEXTURA" << std::endl;
						char* proximo; // gamb
						do // este laco le todas as faces
						{
							// colocando faces
							int num_faces = ocorrencias(linha, ' ');
							proximo = strtok(linha, " ");
							array_de_objetos[indice].faces.push_back(new int[num_faces + 1]);
							array_de_objetos[indice].indNormais.push_back(new int[num_faces + 1]);
							array_de_objetos[indice].faces.back()[0] = num_faces;
							for (int i = 1, j = 1; i < (2 * num_faces) + 1; i += 2, j++)
								sscanf(strtok(NULL, " "), "%d//%d", &(array_de_objetos[indice].faces.back()[j]), &(array_de_objetos[indice].indNormais.back()[j]));
							arquivo.getline(linha, MAX_CHARS_LINHA);
						} while (linha[0] == 'f');
						std::cout << "EH TETRAAA" << std::endl;
					}
					else // com normal e com indice da textura que deve ser ignorado.
					{
						char* proximo; // gamb
						do // este laco le todas as faces
						{
							// colocando faces
							int num_faces = ocorrencias(linha, ' ');
							proximo = strtok(linha, " ");
							array_de_objetos[indice].faces.push_back(new int[num_faces + 1]);
							array_de_objetos[indice].indNormais.push_back(new int[num_faces + 1]);
							array_de_objetos[indice].faces.back()[0] = num_faces;
							for (int i = 1, j = 1; i < (2 * num_faces) + 1; i += 2, j++)
								sscanf(strtok(NULL, " "), "%d/%*d/%d", &(array_de_objetos[indice].faces.back()[j]), &(array_de_objetos[indice].indNormais.back()[j]));
							arquivo.getline(linha, MAX_CHARS_LINHA);
						} while (linha[0] == 'f');
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
						//std::cout << num_faces << std::endl;
						proximo = strtok(linha, " ");
						array_de_objetos[indice].faces.push_back(new int[num_faces + 1]);
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

	}
	
	
	return (indice + 1);
}

float* Objeto::calcular_normais_face(int *atual)
{
	float v1[3], v2[3];

	v1[0] = vertices.at(atual[1] - 1)[0] - vertices.at(atual[2] - 1)[0]; //x
	v1[1] = vertices.at(atual[1] - 1)[1] - vertices.at(atual[2] - 1)[1]; //y
	v1[2] = vertices.at(atual[1] - 1)[3] - vertices.at(atual[2] - 1)[3]; //z

	v2[0] = vertices.at(atual[3] - 1)[0] - vertices.at(atual[2] - 1)[0]; //x
	v2[1] = vertices.at(atual[3] - 1)[1] - vertices.at(atual[2] - 1)[1]; //y
	v2[2] = vertices.at(atual[3] - 1)[3] - vertices.at(atual[2] - 1)[3]; //z

	float nx = (v1[1] * v2[2]) - (v1[2] * v2[1]);
	float ny = (v1[2] * v2[0]) - (v1[0] * v2[2]);
	float nz = (v1[0] * v2[1]) - (v1[1] * v2[0]);

	float len = sqrt((nx*nx) + (ny*ny) + (nz*nz));

	nx /= len;
	ny /= len;
	nz /= len;

	float* normal = new float[3];
	normal[0] = nx;
	normal[1] = ny;
	normal[2] = nz;

	return normal;
}

void Objeto::calcular_normais_vert(){
	
	int* atual;
	float* normal;
	float x, y, z, len;

	for (int i = 0; i < vertices.size(); i++)
	{
		normais.push_back(new float[3]);
		vNormais.push_back(0);
	}

	for (int i = 0; i < (int)faces.size(); i++){
		atual = faces.at(i);
		//encontrando uma normal associada aos vertices da face atual
		normal = calcular_normais_face(atual);

		for (int j = 1; j < 4; j++){
			//somando essa normal com as outras que eu ja encontrei para aquele vértice
			normais.at(atual[j] - 1)[0] += normal[0];
			normais.at(atual[j] - 1)[1] += normal[1];
			normais.at(atual[j] - 1)[2] += normal[2];
			
			//as duas normais somadas eram normalizadas
			//mas o resultado nao
			//entao eu normalizo
			x = normais.at(atual[j] - 1)[0];
			y = normais.at(atual[j] - 1)[1];
			z = normais.at(atual[j] - 1)[2];

			len = sqrt((x*x) + (y*y) + (z*z));

			normais.at(atual[j] - 1)[0] /= len;
			normais.at(atual[j] - 1)[1] /= len;
			normais.at(atual[j] - 1)[2] /= len;
			
			//incrementando a quantidade de normais associadas ao vertice
			vNormais.at(atual[j] - 1)++;
		}

	}

	//tirando a media das normais das faces
	for (int i = 0; i < normais.size(); i++)
	{
		/*pra tirar a media das normais eu dividia elas pela quantidade de normais associadas ao vertice
		  mas, como eu sempre normalizava a soma, eu pegava um vetor de norma 1 e dividia por sei lá
		  quantas normais q cada vertice tem e isso fazia o vetor ficar beeem pequeno por isso o obj
		  ficava escuro.
		  evitando essa divisao o vetor se mantém normalizado e o resultado é muito melhor, mas ainda é
		  diferente do tubarão e tecnicamente errado, pois eu estou somando normais, e nao tirando a media delas :/
		*/
		/*
		normais.at(i)[0] /= vNormais.at(i);
		normais.at(i)[1] /= vNormais.at(i);
		normais.at(i)[2] /= vNormais.at(i);
		*/
		normais.at(i)[0] *= -1;
		normais.at(i)[1] *= -1;
		normais.at(i)[2] *= -1;
	}
}

void Objeto::renderizar()
{
	bool precisaNormais = false;
	int* atual;
	int* nAtual;

	//se o arquivo não vier com as normais
	if (normais.size() == 0){	
		//usar NORMAIS DOS VÉRTICES
		//comenta essa linha \/
		//precisaNormais = true;

		//se quiser usar NORMAIS DAS FACES
		//descomenta a anterior e 
		//comenta essa \/
		calcular_normais_vert();
	}
	std::cout << cores[0] << cores[1] << cores[2] << std::endl;

	for (int i = 0; i < (int)faces.size(); i++)
	{

		atual = faces.at(i);
		
		//std::cout << atual[1] << " " << atual[2] << " " << atual[3] << " " << std::endl;
		if (atual[0] == 3)	glBegin(GL_TRIANGLES);
		else if (atual[0] == 4) glBegin(GL_QUADS);
		else glBegin(GL_POLYGON);

		glColor3f(cores[0], cores[1],cores[2]);

		//agora o caso dos arquivos que nós mesmos calculamos as normais entra nesse if
		if (indNormais.size() == 0){//nao precisa calcular normais, não vem com indice
			
			if (precisaNormais){
				
				//usando apenas as normais das faces
				float *normal = calcular_normais_face(atual);
				glNormal3fv(normal);
				for (int j = 1; j <= atual[0]; j++)
				{
					glVertex3fv(vertices.at(atual[j] - 1));
				}
			}
			else{
				//usando as normais dos vertices
				
				for (int j = 1; j <= atual[0]; j++)
				{

					glNormal3fv(normais.at(atual[j] - 1));
					glVertex3fv(vertices.at(atual[j] - 1));
				}
			}
			
		}else{//nao precisa calcular normais, ja vem com indice
			
			nAtual = indNormais.at(i);
			for (int j = 1; j <= atual[0]; j++)
			{
				
				glNormal3fv(normais.at(nAtual[j] - 1));
				glVertex3fv(vertices.at(atual[j] - 1));
			}
		}
		glEnd();
	}
	
}


void Objeto::translateObj(int t, float s){
	float tx = 0.0;
	float ty = 0.0;
	float tz = 0.0;

	if (t == 0){
		tx = 0.2*s;
	}
	else if (t == 1){
		ty = 0.2*s;
	}
	else{
		tz = 0.2*s;
	}

	for (int i = 0; i < vertices.size(); i++)
	{		
		vertices.at(i)[0] += tx;
		vertices.at(i)[1] += ty;
		vertices.at(i)[2] += tz;		
	}

}

void Objeto::escale(float i){
	float sx, sy, sz;

	if (i > 0){
		sx = 1.01;
		sy = 1.01;
		sz = 1.01;
	}
	else{
		sx = 0.99;
		sy = 0.99;
		sz = 0.99;
	}

	for (int i = 0; i < vertices.size(); i++)
	{
		vertices.at(i)[0] *= sx;
		vertices.at(i)[1] *= sy;
		vertices.at(i)[2] *= sz;
	}
}