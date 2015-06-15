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
#include "Camera.h"

/*
http://www.inf.pucrs.br/~manssour/OpenGL/Tutorial.html
esse link!!!!
*/
Objeto* array_inicial;
int quant;
Camera *c = new Camera();
bool botao_esquerdo_pressionado = false;
bool botao_recem_pressionado = false;
float posicaoX = 0.f, posicaoY = 0.f, posicaoZ = 0.f;
float rotacaoX = 0.f, rotacaoY = 0.f;
float x_atual = 0.f, y_atual = 0.f;

void MouseArrastado(int x, int y)
{
	if (botao_esquerdo_pressionado)
	{
		int deltaX, deltaY;
		if (botao_recem_pressionado)
		{
			deltaX = deltaY = 0;
			botao_recem_pressionado = false;
		}
		else
		{
			deltaX = x - x_atual;
			deltaY = y - y_atual;
		}
		x_atual = x;
		y_atual = y;
		// o sentido da rotacao eh a gosto do fregues.
		// no momento esta se movendo estilo "maozinha de mover" de um arquivo pdf ou imagem jpg.
		// para inverter, inverta a operacao.
		rotacaoX -= (float)deltaY;
		rotacaoY -= (float)deltaX;
		glutPostRedisplay();
	}
}

void BotaoDoMouseClicado(int botao, int estado, int x, int y)
{
	if (botao == GLUT_LEFT_BUTTON && estado == GLUT_DOWN)
	{
		botao_esquerdo_pressionado = true;
		botao_recem_pressionado = true;
	}
	else if (botao == GLUT_LEFT_BUTTON && estado == GLUT_UP) botao_esquerdo_pressionado = false;
}

// Função callback chamada para fazer o desenho
void Desenha()
{
	glMatrixMode(GL_MODELVIEW);
	//definir que todas as tranformações vão ser em cena (no desenho)
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	c->nossoLoadIdentity();

	// nossa camera
	c->nossoRotate(rotacaoX, 1.0, 0.0, 0.0);
	c->nossoRotate(rotacaoY, 0.0, 1.0, 0.0);
	c->nossoTranslate(-posicaoX, -posicaoY, -posicaoZ);
	
	glLoadMatrixf(c->extrinsic);

	// AQUI VAO OS DESENHOS

	// TESTES
	
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	for (int i = 0; i < quant; i++) array_inicial[i].renderizar();
	glPopMatrix();
	//for (int i = 0; i < 16; i++) std::cout << c->extrinsic[i] << " " << std::endl;
	// FIM DOS TESTES

	// TERMINA DESENHOS
	glutSwapBuffers();
}

// Inicializa parâmetros de rendering
void Inicializa()
{
	glEnable(GL_DEPTH_TEST);
	//para ver os parametros da função (e de qualquer outra) usar ctrl+shift+spacebar
	//dentro dos parênteses
	//-----inicioIluminação
	//Características do objeto
	GLfloat especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLint especMaterial = 1;

	//Característica padrão
	GLfloat luzAmbiente[4] = { 0.5, 0.5, 0.5, 1.0 };

	//Habilitando Gouraud
	glShadeModel(GL_SMOOTH);

	//Habilitando características padrões 
	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	//Características da luz 0
	GLfloat luzDifusa[4] = { 1.0, 1.0, 1.0, 1.0 };	   
	GLfloat luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 }; 
	GLfloat posicaoLuz[4] = { 0.0, 50.0, 50.0, 1.0 };

	//Ativando parâmetros da luz 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);


	//Características da luz 1
	GLfloat luzDifusa1[4] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat luzEspecular1[4] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat posicaoLuz1[4] = { 0.0, 25.0, 25.0, 1.0 };

	//Ativando parâmetros da luz 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

	//Habilita tipo de coloração
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	//Habilita a luz 0
	glEnable(GL_LIGHT0);
	//Habilita a luz 1
	glEnable(GL_LIGHT1);
	//Habilita o depth-buffering
	//-----fimIluminação
	
	//----------Modo específico: iluminação com sombras e névoa
	//Adicionando as 6 fontes de luz que faltam
	//para desativar alguma fonte de luz comente os: glEnable(GL_LIGHT*);
	//Características da luz 2
	GLfloat luzDifusa2[4] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat luzEspecular2[4] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat posicaoLuz2[4] = { 0.0, 10.0, 10.0, 1.0 };

	//Ativando parâmetros da luz 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luzDifusa2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luzEspecular2);
	glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz2);
	glEnable(GL_LIGHT2);

	//Características da luz 3
	GLfloat luzDifusa3[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat luzEspecular3[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat posicaoLuz3[4] = { 0.0, 20.0, 20.0, 1.0 };

	//Ativando parâmetros da luz 3
	glLightfv(GL_LIGHT3, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, luzDifusa3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, luzEspecular3);
	glLightfv(GL_LIGHT3, GL_POSITION, posicaoLuz3);
	glEnable(GL_LIGHT3);

	//Características da luz 4
	GLfloat luzDifusa4[4] = { 0.0, 0.0, 0.75, 1.0 };
	GLfloat luzEspecular4[4] = { 0.0, 0.0, 0.75, 1.0 };
	GLfloat posicaoLuz4[4] = { 0.0, 30.0, 30.0, 1.0 };

	//Ativando parâmetros da luz 4
	glLightfv(GL_LIGHT4, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, luzDifusa4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, luzEspecular4);
	glLightfv(GL_LIGHT4, GL_POSITION, posicaoLuz4);
	glEnable(GL_LIGHT4);

	//Características da luz 5
	GLfloat luzDifusa5[4] = { 0.0, 0.75, 0.0, 1.0 };
	GLfloat luzEspecular5[4] = { 0.0, 0.75, 0.0, 1.0 };
	GLfloat posicaoLuz5[4] = { 0.0, 40.0, 40.0, 1.0 };

	//Ativando parâmetros da luz 5
	glLightfv(GL_LIGHT5, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, luzDifusa5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, luzEspecular5);
	glLightfv(GL_LIGHT5, GL_POSITION, posicaoLuz5);
	glEnable(GL_LIGHT5);

	//Características da luz 6
	GLfloat luzDifusa6[4] = { 0.75, 0.0, 0.0, 1.0 };
	GLfloat luzEspecular6[4] = { 0.75, 0.0, 0.0, 1.0 };
	GLfloat posicaoLuz6[4] = { 0.0, 60.0, 60.0, 1.0 };

	//Ativando parâmetros da luz 6
	glLightfv(GL_LIGHT6, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, luzDifusa6);
	glLightfv(GL_LIGHT6, GL_SPECULAR, luzEspecular6);
	glLightfv(GL_LIGHT6, GL_POSITION, posicaoLuz6);
	glEnable(GL_LIGHT6);

	//Características da luz 7
	GLfloat luzDifusa7[4] = { 0.0, 0.0, 0.25, 1.0 };
	GLfloat luzEspecular7[4] = { 0.0, 0.0, 0.25, 1.0 };
	GLfloat posicaoLuz7[4] = { 0.0, 70.0, 70.0, 1.0 };

	//Ativando parâmetros da luz 7
	glLightfv(GL_LIGHT7, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, luzDifusa7);
	glLightfv(GL_LIGHT7, GL_SPECULAR, luzEspecular7);
	glLightfv(GL_LIGHT7, GL_POSITION, posicaoLuz7);
	glEnable(GL_LIGHT7);
	//----------fim modo específico: iluminação com sombras e névoa
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
		case '1': // translada objeto no seu proprio eixo x e sentido -
			break;
		case '2': // translada objeto no seu proprio eixo x e sentido +
			break;
		case '3': // translada objeto no seu proprio eixo y e sentido -
			break; 
		case '4': // translada objeto no seu proprio eixo y e sentido +
			break;
		case '5': // translada objeto no seu proprio eixo z e sentido -
			break;
		case '6': // translada objeto no seu proprio eixo z e sentido +
			break;
		case '7': // gira o objeto em relacao ao seu eixo x
			glutPostRedisplay();
			break;
		case '8': // gira o objeto em relacao ao seu eixo y
			glutPostRedisplay();
			break;
		case '9': // gira o objeto em relacao ao seu eixo z
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
			posicaoX += float(sin(Camera::grau_para_rad(rotacaoY)));
			posicaoZ -= float(cos(Camera::grau_para_rad(rotacaoY)));
			posicaoY -= float(sin(Camera::grau_para_rad(rotacaoX)));
			glutPostRedisplay();
			break;
		case 's':
		case 'S': // move camera para tras (eixo z em coord de camera)
			posicaoX -= float(sin(Camera::grau_para_rad(rotacaoY)));
			posicaoZ += float(cos(Camera::grau_para_rad(rotacaoY)));
			posicaoY += float(sin(Camera::grau_para_rad(rotacaoX)));
			glutPostRedisplay();
			break;
		case 'd':
		case 'D': // move camera para direita (eixo x em coord de camera)
			posicaoX += float(cos(Camera::grau_para_rad(rotacaoY)));
			posicaoZ += float(sin(Camera::grau_para_rad(rotacaoY)));
			glutPostRedisplay();
			break;
		case 'a':
		case 'A': // move camera para esquerda (eixo x em coord de camera)
			posicaoX -= float(cos(Camera::grau_para_rad(rotacaoY)));
			posicaoZ -= float(sin(Camera::grau_para_rad(rotacaoY)));
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

// Programa Principal 
int main()
{

	quant = Objeto::carregar_obj(array_inicial, "Obj Files/OBJS.obj");

	std::cout << quant << std::endl;
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

	// callback da funcao que interpreta o mouse sendo arrastado enquanto algum botao dele eh pressionado
	glutMotionFunc(MouseArrastado);
	// callback da funcao que interpreta o evento de um botao do mouse sendo pressionado ou solto
	glutMouseFunc(BotaoDoMouseClicado);
	// callback da funcao que interpreta uma tecla pressionada
	glutKeyboardFunc(TeclaPressionada);
	Inicializa();
	//inicializar alguns parametros do glut (nessa caso a cor do fundo da tela).
	//cor que vai limpar o buffer
	glutMainLoop();
	//começa a execução da maquina de estados do glut/opengl que controla as funções
	//de callback (controlador de mouse, teclado, callback de controle de tela, etc).
	delete c;
	if (quant > 0) delete[] array_inicial;
}
