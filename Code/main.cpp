/*
-----------------------------------------------------------------------------
OpenGL Tutorial
VOXAR Labs
Computer Science Center - CIn
Federal University of Pernambuco - UFPE
http://www.cin.ufpe.br/~voxarlabs

-----------------------------------------------------------------------------
*/

#include <cstdlib>
#include "common.h"
#include "Objeto.h"
#include "camera.h"

/*
http://www.inf.pucrs.br/~manssour/OpenGL/Tutorial.html
esse link!!!!
*/

Camera *c = new Camera();
bool tecla_pressionada = false;

// Função callback chamada para fazer o desenho
void Desenha()
{
	//glMatrixMode(GL_MODELVIEW);
	//definir que todas as tranformações vão ser em cena (no desenho)
	
	glClearColor(0.0, 0.7, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();

	// Limpa a janela de visualização com a cor de fundo especificada
	//glClear(GL_COLOR_BUFFER_BIT);
	c->nossoLookat(1.0, 1.0, -10,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0);
	glLoadMatrixf(c->extrinsic);
	
	/*gluLookAt(
		1.0, 1.0, -10,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0);*/
	// Especifica que a cor corrente é vermelha
	//         R     G     B
	//glColor3f(1.0f, 0.0f, 0.0f);
	//cor que vai usar para pintar

	// AQUI VAO OS DESENHOS

	// TESTES
	Objeto* array_inicial;
	int quant = Objeto::carregar_obj(array_inicial, "Obj Files/spheretri.obj");
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	for (int i = 0; i < quant; i++) array_inicial[i].renderizar();
	glPopMatrix();
	for (int i = 0; i < 16; i++) std::cout << c->extrinsic[i] << " " << std::endl;
	// FIM DOS TESTES

	// TERMINA DESENHOS
	glutSwapBuffers();
	// Executa os comandos OpenGL
	//glFlush();
	//não sei exatamente o que faz, umas das coisas que não funciona sem.
}

// Inicializa parâmetros de rendering
void Inicializa()
{
	// Define a cor de fundo da janela de visualização como preta
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);
	//para ver os parametros da função (e de qualquer outra) usar ctrl+shift+spacebar
	//dentro dos parênteses
}

void TeclaSolta(unsigned char tecla, int x, int y)
{
	tecla_pressionada = false;
}

void TeclaPressionada(unsigned char tecla, int x, int y)
{
	//tecla_pressionada = true;
	switch (tecla)
	{
		// interacao com objetos
		// objeto1, objeto2, ... objeton, luz1, luz2, .... luzn (lista circular)
		case ',':
		case '<': // objeto anterior ou ultima fonte de luz
			break;
		case '.': 
		case '>': // proximo objeto ou primeira fonte de luz
			break;
		case '1': // translada no eixo x e sentido -
			break;
		case '2': // translada no eixo x e sentido +
			break;
		case '3': // translada no eixo y e sentido -
			break; 
		case '4': // translada no eixo y e sentido +
			break;
		case '5': // translada no eixo z e sentido -
			break;
		case '6': // translada no eixo z e sentido +
			break;
		case '7': // gira em relacao ao eixo x
			break;
		case '8': // gira em relacao ao eixo y
			break;
		case '9': // gira em relacao ao eixo z
			break;
		case '-':
		case '_': // decrementa o tamanho do objeto em 1%
			break;
		case '=': 
		case '+': // incrementa o tamanho do objeto em 1%
			break;

		// interacao com camera
		case 'w':
		case 'W': // move camera para frente (eixo z em coord de camera)
			//while (tecla_pressionada)
			//{
			c->nossoTranslate(1.f,1.f,-10.f);
				c->nossoTranslate(0.f,0.f,.1f);
				c->nossoTranslate(-1.f,-1.f,10.f);
				glLoadMatrixf(c->extrinsic);
				glutPostRedisplay();
			//}
			break;
		case 's':
		case 'S': // move camera para tras (eixo z em coord de camera)
			break;
		case 'd':
		case 'D': // move camera para esquerda (eixo x em coord de camera)
			break;
		case 'a':
		case 'A': // move camera para direita (eixo x em coord de camera)
			break;
	}
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Evita a divisao por zero
	if (h == 0) h = 1;

	float ratio = ((float)w)/ ((float)h);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	//definir que todas as tranformações vão ser em camera (usuario)
	glLoadIdentity();

	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW);
	// Especifica as dimensões da Viewport
	glViewport(0, 0, w, h);
	//define a área dentro janela, em coordenadas de tela,
	//que OpenGL pode usar para fazer o desenho. O volume de
	//visualização é, então, mapeado para a nova viewport
	// Estabelece a janela de seleção (left, right, bottom, top)
	//if (w <= h)
		//gluOrtho2D(0.0f, 250.0f, 0.0f, 250.0f*h / w);
	//else
		//gluOrtho2D(0.0f, 250.0f*w / h, 0.0f, 250.0f);
	//é usada para determinar que a projeção ortográfica (2D) 
	//será utilizada para exibir na tela a imagem
}

/*acendendo a luz
https://www.cse.msu.edu/~cse872/tutorial3.html
GL_AMBIENT
GLfloat white[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat cyan[] = {0.f, .8f, .8f, 1.f};
glMaterialfv(GL_FRONT, GL_DIFFUSE, cyan);
glMaterialfv(GL_FRONT, GL_SPECULAR, white);
glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
*/

// Programa Principal 
int main()
{
	// TESTES
	//Objeto* array_inicial;
	//int quant = Objeto::carregar_obj(array_inicial, "Obj Files/CAT.OBJ");
	// FIM DOS TESTES

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//setar modo de exibição, nesse caso um unico buffer e modelo de cor RGB
	////recomendo usar buffer duplo (GLUT_DOUBLE).
	glutInitWindowSize(640, 480);
	//tamanho da janela
	glutInitWindowPosition(10, 10);
	//onde a janela vai aparecer na tela do PC
	glutCreateWindow("janelinha");
	//criar um janela
	glutDisplayFunc(Desenha);
	//callback da função que dezenha na tela
	glutReshapeFunc(AlteraTamanhoJanela);
	//callback que controla o tamanho da janela (maximizada e minimizada com e 
	// sem essa função e vc vai entender)
	// callback da funcao que interpreta uma tecla pressionada
	glutKeyboardFunc(TeclaPressionada);
	// callback da funcao que interpreta uma tecla que acaba de ser solta
	//glutKeyboardUpFunc(TeclaSolta);
	Inicializa();
	//inicializar alguns parametros do glut (nessa caso a cor do fundo da tela).
	//cor que vai limpar o buffer
	glutMainLoop();
	//começa a execução da maquina de estados do glut/opengl que controla as funções
	//de callback (controlador de mouse, teclado, callback de controle de tela, etc).
	delete c;
}
