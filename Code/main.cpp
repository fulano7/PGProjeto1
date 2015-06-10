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
Objeto* array_inicial;
int quant;
Camera *c = new Camera();
bool tecla_pressionada = false;
float eyex = 1.0f, eyey = 1.0f, eyez = -10.0f;

// Função callback chamada para fazer o desenho
void Desenha()
{
	glMatrixMode(GL_MODELVIEW);
	//definir que todas as tranformações vão ser em cena (no desenho)
	
	glClearColor(0.0, 0.7, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glLoadMatrixf(c->extrinsic);

	// AQUI VAO OS DESENHOS

	// TESTES
	
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	for (int i = 0; i < quant; i++) array_inicial[i].renderizar();
	glPopMatrix();
	for (int i = 0; i < 16; i++) std::cout << c->extrinsic[i] << " " << std::endl;
	// FIM DOS TESTES

	// TERMINA DESENHOS
	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa()
{
	glEnable(GL_DEPTH_TEST);
	c->nossoLookat(eyex,eyey,eyez,
		0.0, 0.0, 1.0,
		0.0, 1.0, 0.0);
	//para ver os parametros da função (e de qualquer outra) usar ctrl+shift+spacebar
	//dentro dos parênteses
}

void TeclaPressionada(unsigned char tecla, int x, int y)
{
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
			c->nossoRotate(0.05, 1.f, 0.f, 0.f);
			glLoadMatrixf(c ->extrinsic);
			glutPostRedisplay();
			break;
		case '8': // gira em relacao ao eixo y
			c->nossoRotate(0.05, 0.f, 1.f, 0.f);
			glLoadMatrixf(c->extrinsic);
			glutPostRedisplay();
			break;
		case '9': // gira em relacao ao eixo z
			c->nossoRotate(0.05, 0.f, 0.f, 1.f);
			glLoadMatrixf(c->extrinsic);
			glutPostRedisplay();
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
			// da no mesmo sem transladar para origem?
			// ordem importa?
			//c->nossoTranslate(eyex,eyey,eyez);
			// indo pra frente
			c->nossoTranslate(0.f,0.f,-.1f);
			//c->nossoTranslate(-eyex,-eyey,-eyez);
			glLoadMatrixf(c->extrinsic);
			glutPostRedisplay();
			break;
		case 's':
		case 'S': // move camera para tras (eixo z em coord de camera)
			c->nossoTranslate(0.f, 0.f, +.1f);
			//c->nossoTranslate(-eyex,-eyey,-eyez);
			glLoadMatrixf(c->extrinsic);
			glutPostRedisplay();
			break;
		case 'd':
		case 'D': // move camera para direita (eixo x em coord de camera)
			c->nossoTranslate(+.1f, 0.f, 0.f);
			//c->nossoTranslate(-eyex,-eyey,-eyez);
			glLoadMatrixf(c->extrinsic);
			glutPostRedisplay();
			break;
		case 'a':
		case 'A': // move camera para esquerda (eixo x em coord de camera)
			c->nossoTranslate(-.1f, 0.f, 0.f);
			//c->nossoTranslate(-eyex,-eyey,-eyez);
			glLoadMatrixf(c->extrinsic);
			glutPostRedisplay();
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

	quant = Objeto::carregar_obj(array_inicial, "Obj Files/shark.obj");

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
	Inicializa();
	//inicializar alguns parametros do glut (nessa caso a cor do fundo da tela).
	//cor que vai limpar o buffer
	glutMainLoop();
	//começa a execução da maquina de estados do glut/opengl que controla as funções
	//de callback (controlador de mouse, teclado, callback de controle de tela, etc).
	delete c;
}
