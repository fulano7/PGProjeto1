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
#include "Luz.h"

/*
http://www.inf.pucrs.br/~manssour/OpenGL/Tutorial.html
esse link!!!!
*/
Objeto* array_inicial;
int quantObj;
Camera *c = new Camera();
bool botao_esquerdo_pressionado = false;
bool botao_recem_pressionado = false;
float posicaoX = 0.f, posicaoY = 4.f, posicaoZ = 13.f;
float posicaoX_2 = 10.f, posicaoY_2 = 15.f, posicaoZ_2 = 70.f; // posição da camera do observador diretor
float rotacaoX = 0.f, rotacaoY = 0.f;
float x_atual = 0.f, y_atual = 0.f;
int selecionado = 1;
int quantLuzes = 8;
GLsizei aux_w, aux_h = 0;  // usado para o caso de visão diretor, usado para separar os viewports
bool directorView = true;
vector <Luz> lights;
bool n_pressionado = false;
float densidade = 0.025f;

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
		rotacaoY += (float)deltaX;
		glutPostRedisplay();
	}
}

void desenhaCubo(){
	
	//Lado vermelho - Frente
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(posicaoX + 1, posicaoY + 1, posicaoZ - 1); 
	glVertex3f(posicaoX - 1, posicaoY + 1, posicaoZ - 1);      
	glVertex3f(posicaoX - 1, posicaoY - 1, posicaoZ - 1);
	glVertex3f(posicaoX + 1, posicaoY - 1, posicaoZ - 1);
	glEnd();

	// Lado branco - TRASEIRA
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(posicaoX + 1, posicaoY + 1, posicaoZ + 1);
	glVertex3f(posicaoX - 1, posicaoY + 1, posicaoZ + 1);
	glVertex3f(posicaoX - 1, posicaoY - 1, posicaoZ + 1);
	glVertex3f(posicaoX + 1, posicaoY - 1, posicaoZ + 1);
	glEnd();

	// Lado roxo - DIREITA
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(posicaoX + 1, posicaoY + 1, posicaoZ - 1);
	glVertex3f(posicaoX + 1, posicaoY + 1, posicaoZ + 1);
	glVertex3f(posicaoX + 1, posicaoY - 1, posicaoZ + 1);
	glVertex3f(posicaoX + 1, posicaoY - 1, posicaoZ - 1);
	glEnd();

	// Lado verde - ESQUERDA
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(posicaoX - 1, posicaoY + 1, posicaoZ - 1);
	glVertex3f(posicaoX - 1, posicaoY + 1, posicaoZ + 1);
	glVertex3f(posicaoX - 1, posicaoY - 1, posicaoZ + 1);
	glVertex3f(posicaoX - 1, posicaoY - 1, posicaoZ - 1);
	glEnd();


	// Lado azul - TOPO
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(posicaoX + 1, posicaoY + 1, posicaoZ - 1);
	glVertex3f(posicaoX + 1, posicaoY + 1, posicaoZ + 1);
	glVertex3f(posicaoX - 1, posicaoY + 1, posicaoZ - 1);
	glVertex3f(posicaoX - 1, posicaoY + 1, posicaoZ - 1);
	glEnd();

	// Lado vermelho - BASE
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);
	glVertex3f(posicaoX + 1, posicaoY - 1, posicaoZ - 1);
	glVertex3f(posicaoX + 1, posicaoY - 1, posicaoZ + 1);
	glVertex3f(posicaoX - 1, posicaoY - 1, posicaoZ - 1);
	glVertex3f(posicaoX - 1, posicaoY - 1, posicaoZ - 1);
	glEnd();

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
	if (!directorView)
	{

	glMatrixMode(GL_MODELVIEW);
	
	//definir que todas as tranformações vão ser em cena (no desenho)
	
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	c->nossoLoadIdentity();

	// nossa camera
	c->nossoRotate(rotacaoX, 1.0, 0.0, 0.0);
	c->nossoTranslate(-posicaoX, -posicaoY, -posicaoZ);
	c->nossoRotate(rotacaoY, 0.0, 1.0, 0.0);
	
	glLoadMatrixf(c->extrinsic);

	// AQUI VAO OS DESENHOS
	
	// TESTES
	
	glColor3f(1.0, 1.0, 1.0);
	glPushMatrix();
	glTranslatef(0.0, 0.0, 0.75);
	

	for (int i = 0; i < quantObj; i++) { 
		std::cout << i << std::endl;
		array_inicial[i].renderizar(); 
	}
	
	glPopMatrix();
	for (int i = 0; i < quantLuzes; i++)
	{
		glPushMatrix();
		glTranslated(lights.at(i).Tx, lights.at(i).Ty, lights.at(i).Tz);
		double scale = lights.at(i).Scale;
		//std::cout << "scale: " << scale << std::endl;
		glScaled(scale, scale, scale);
		glLightfv(GL_LIGHT0+i, GL_POSITION, lights.at(i).posicao);
		glPopMatrix();
	}
	//for (int i = 0; i < 16; i++) std::cout << c->extrinsic[i] << " " << std::endl;
	// FIM DOS TESTES

	// TERMINA DESENHOS
		
	}
	else  // dividir viewport em duas partes
	{
		glViewport(0, 0, aux_w, aux_h); // primeiro viewport
		glMatrixMode(GL_MODELVIEW);
		//definir que todas as tranformações vão ser em cena (no desenho)

		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glLoadIdentity();
		c->nossoLoadIdentity();

		// nossa camera
		c->nossoRotate(rotacaoX, 1.0, 0.0, 0.0);
		c->nossoTranslate(-posicaoX, -posicaoY, -posicaoZ);
		c->nossoRotate(rotacaoY, 0.0, 1.0, 0.0);

		glLoadMatrixf(c->extrinsic);

		// AQUI VAO OS DESENHOS

		// TESTES

		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.75);

		for (int i = 0; i < quantObj; i++) array_inicial[i].renderizar();
		glPopMatrix();
		//for (int i = 0; i < 16; i++) std::cout << c->extrinsic[i] << " " << std::endl;
		// FIM DOS TESTES

		// TERMINA DESENHOS
		
		

		// parte do observador da camera

		Camera *c_2 = new Camera();   // camera que deve ficar fixa, mostrando apenas os objetos sendo modificados
		glViewport(aux_w, 0, aux_w, aux_h); // segundo viewport
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		c_2->nossoLoadIdentity();

		// nossa camera
		c->nossoRotate(rotacaoX, 1.0, 0.0, 0.0);
		c_2->nossoTranslate(-posicaoX_2, -posicaoY_2, -posicaoZ_2);
		c->nossoRotate(rotacaoY, 0.0, 1.0, 0.0);

		glLoadMatrixf(c_2->extrinsic);

		glColor3f(1.0, 1.0, 1.0);
		glPushMatrix();
		glTranslatef(0.0, 0.0, 0.75);


		for (int i = 0; i < quantObj; i++) array_inicial[i].renderizar();
		glPopMatrix();
		//for (int i = 0; i < 16; i++) std::cout << c_2->extrinsic[i] << " " << std::endl;
		glPushMatrix();
		glRotatef(-rotacaoY, 0.0, 1.0, 0.0);
		desenhaCubo();
		glRotatef(-rotacaoX, 1.0, 0.0, 0.0);
		glPopMatrix();
	}

	glutSwapBuffers();
}


void Nevoa(){

	GLfloat fColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogfv(GL_FOG_COLOR, fColor);
	glFogf(GL_FOG_DENSITY, densidade);
	glFogf(GL_FOG_START, 1.0f);
	glFogf(GL_FOG_END, 5.0f);
	glEnable(GL_FOG);
}


// Inicializa parâmetros de rendering
void Inicializa()
{
	glEnable(GL_DEPTH_TEST);
	//para ver os parametros da função (e de qualquer outra) usar ctrl+shift+spacebar
	//dentro dos parênteses
	//-----inicioIluminação
	//Características do objeto
	float especularidade[4] = { 1.0, 1.0, 1.0, 1.0 };
	int especMaterial = 45;

	//Característica padrão
	float luzAmbiente[4] = { 0.5, 0.5, 0.5, 1.0 };

	//Habilitando Gouraud
	glShadeModel(GL_SMOOTH);

	//Habilitando características padrões 
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, especularidade);
	glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, especMaterial);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	//Características da luz 0
	float luzDifusa[4] = { 1.0, 1.0, 1.0, 1.0 };	   
	float luzEspecular[4] = { 1.0, 1.0, 1.0, 1.0 }; 
	float* posicaoLuz = new float[4];
	posicaoLuz[0] = -20.0f;
	posicaoLuz[1] = 50.0f;
	posicaoLuz[2] = 50.0f;
	posicaoLuz[3] = 1.0f;
	Luz l = Luz(posicaoLuz);
	lights.push_back(l);
	//Ativando parâmetros da luz 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz);


	//Características da luz 1
	GLfloat luzDifusa1[4] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat luzEspecular1[4] = { 0.0, 0.0, 1.0, 1.0 };
	GLfloat* posicaoLuz1 = new GLfloat[4];
	posicaoLuz1[0] = 0.0f;
	posicaoLuz1[1] = 25.0f;
	posicaoLuz1[2] = 25.0f;
	posicaoLuz1[3] = 1.0f;
	Luz l1 = Luz(posicaoLuz1);
	lights.push_back(l1);
	//Ativando parâmetros da luz 1
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);

	//Habilita tipo de coloração
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminação
	glEnable(GL_LIGHTING);
	

	//Habilita o depth-buffering
	//-----fimIluminação
	
	//----------Modo específico: iluminação com sombras e névoa
	//Adicionando as 6 fontes de luz que faltam
	//para desativar alguma fonte de luz comente os: glEnable(GL_LIGHT*);
	//Características da luz 2
	GLfloat luzDifusa2[4] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat luzEspecular2[4] = { 0.0, 1.0, 0.0, 1.0 };
	GLfloat* posicaoLuz2 = new GLfloat[4];
	posicaoLuz2[0] = 0.0;
	posicaoLuz2[1] = 10.0;
	posicaoLuz2[2] = 10.0;
	posicaoLuz2[3] = 1.0;
	Luz l2 = Luz(posicaoLuz2);
	lights.push_back(l2);
	//Ativando parâmetros da luz 2
	glLightfv(GL_LIGHT2, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, luzDifusa2);
	glLightfv(GL_LIGHT2, GL_SPECULAR, luzEspecular2);
	glLightfv(GL_LIGHT2, GL_POSITION, posicaoLuz2);
	

	//Características da luz 3
	GLfloat luzDifusa3[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat luzEspecular3[4] = { 1.0, 0.0, 0.0, 1.0 };
	GLfloat* posicaoLuz3 = new GLfloat[4];
	posicaoLuz3[0] = 0.0;
	posicaoLuz3[1] = 20.0;
	posicaoLuz3[2] = 20.0;
	posicaoLuz3[3] = 1.0;
	Luz l3 = Luz(posicaoLuz3);
	lights.push_back(l3);
	//Ativando parâmetros da luz 3
	glLightfv(GL_LIGHT3, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, luzDifusa3);
	glLightfv(GL_LIGHT3, GL_SPECULAR, luzEspecular3);
	glLightfv(GL_LIGHT3, GL_POSITION, posicaoLuz3);

	//Características da luz 4
	GLfloat luzDifusa4[4] = { 0.0, 0.0, 0.75, 1.0 };
	GLfloat luzEspecular4[4] = { 0.0, 0.0, 0.75, 1.0 };
	GLfloat* posicaoLuz4 = new GLfloat[4];
	posicaoLuz4[0] = 0.0;
	posicaoLuz4[1] = 30.0;
	posicaoLuz4[2] = 30.0;
	posicaoLuz4[3] = 1.0;
	Luz l4 = Luz(posicaoLuz4);
	lights.push_back(l4);

	//Ativando parâmetros da luz 4
	glLightfv(GL_LIGHT4, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, luzDifusa4);
	glLightfv(GL_LIGHT4, GL_SPECULAR, luzEspecular4);
	glLightfv(GL_LIGHT4, GL_POSITION, posicaoLuz4);
	

	//Características da luz 5
	GLfloat luzDifusa5[4] = { 0.0, 0.75, 0.0, 1.0 };
	GLfloat luzEspecular5[4] = { 0.0, 0.75, 0.0, 1.0 };
	GLfloat* posicaoLuz5 = new GLfloat[4];
	posicaoLuz5[0] = 0.0;
	posicaoLuz5[1] = 40.0;
	posicaoLuz5[2] = 40.0;
	posicaoLuz5[3] = 1.0;
	Luz l5 = Luz(posicaoLuz5);
	lights.push_back(l5);

	//Ativando parâmetros da luz 5
	glLightfv(GL_LIGHT5, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, luzDifusa5);
	glLightfv(GL_LIGHT5, GL_SPECULAR, luzEspecular5);
	glLightfv(GL_LIGHT5, GL_POSITION, posicaoLuz5);

	//Características da luz 6
	GLfloat luzDifusa6[4] = { 0.75, 0.0, 0.0, 1.0 };
	GLfloat luzEspecular6[4] = { 0.75, 0.0, 0.0, 1.0 };
	GLfloat* posicaoLuz6 = new GLfloat[4];
	posicaoLuz6[0] = 0.0;
	posicaoLuz6[1] = 60.0;
	posicaoLuz6[2] = 60.0;
	posicaoLuz6[3] = 1.0;
	Luz l6 = Luz(posicaoLuz6);
	lights.push_back(l6);

	//Ativando parâmetros da luz 6
	glLightfv(GL_LIGHT6, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT6, GL_DIFFUSE, luzDifusa6);
	glLightfv(GL_LIGHT6, GL_SPECULAR, luzEspecular6);
	glLightfv(GL_LIGHT6, GL_POSITION, posicaoLuz6);
	

	//Características da luz 7
	GLfloat luzDifusa7[4] = { 0.0, 0.0, 0.25, 1.0 };
	GLfloat luzEspecular7[4] = { 0.0, 0.0, 0.25, 1.0 };
	GLfloat* posicaoLuz7 = new GLfloat[4];
	posicaoLuz7[0] = 0.0;
	posicaoLuz7[1] = 70.0;
	posicaoLuz7[2] = 70.0;
	posicaoLuz7[3] = 1.0;
	Luz l7 = Luz(posicaoLuz7);
	lights.push_back(l7);

	//Ativando parâmetros da luz 7
	glLightfv(GL_LIGHT7, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT7, GL_DIFFUSE, luzDifusa7);
	glLightfv(GL_LIGHT7, GL_SPECULAR, luzEspecular7);
	glLightfv(GL_LIGHT7, GL_POSITION, posicaoLuz7);

	for (int i = 0; i < (int)quantLuzes; i++) glEnable(GL_LIGHT0+i);

	Nevoa();

	//----------fim modo específico: iluminação com sombras e névoa
}

void TeclaPressionada(unsigned char tecla, int x, int y)
{
	float rotacaoY = 0.f; // como a rotacao eh no eixo y do mundo e nao da camera,
	                      // nao consideramos sua influencia nas translacoes nos eixos x e z da camera.
	switch (tecla)
	{
		// interacao com objetos
		// objeto1, objeto2, ... objeton, luz1, luz2, .... luzn (lista circular)
		case ',':
		case '<': // objeto anterior ou ultima fonte de luz
			if (selecionado == 1){
				selecionado = quantObj + lights.size() - 1;

			}
			else{
				selecionado -= 1;
			}
			break;
		case '.': 
		case '>': // proximo objeto ou primeira fonte de luz
			if (selecionado == quantObj + lights.size() - 1){
				selecionado = 1;
			}
			else{
				selecionado += 1;
			}
			break;
		case '1': // translada objeto no seu proprio eixo x e sentido -
			if (selecionado < quantObj){
				array_inicial[selecionado].translateObj(0, -1.0);
			}
			else{
				lights.at(selecionado - quantObj).Tx -= 0.2;
			}
			
			glutPostRedisplay();
			break;
		case '2': // translada objeto no seu proprio eixo x e sentido +
			if (selecionado < quantObj){
				array_inicial[selecionado].translateObj(0, 1.0);
			}
			else{
				lights.at(selecionado - quantObj).Tx += 0.2;
			}
			
			glutPostRedisplay();
			break;
		case '3': // translada objeto no seu proprio eixo y e sentido -
			if (selecionado < quantObj){
				array_inicial[selecionado].translateObj(1, -1.0);
			}
			else{
				lights.at(selecionado - quantObj).Ty -= 0.2;
			}
			
			glutPostRedisplay();
			break; 
		case '4': // translada objeto no seu proprio eixo y e sentido +
			if (selecionado < quantObj){
				array_inicial[selecionado].translateObj(1, 1.0);
			}
			else{
				lights.at(selecionado - quantObj).Ty += 0.2;
			}
			
			glutPostRedisplay();
			break;
		case '5': // translada objeto no seu proprio eixo z e sentido -
			if (selecionado < quantObj){
				array_inicial[selecionado].translateObj(2, -1.0);
			}
			else{
				lights.at(selecionado - quantObj).Tz -= 0.2;
			}
			
			glutPostRedisplay();
			break;
		case '6': // translada objeto no seu proprio eixo z e sentido +
			if (selecionado < quantObj){
				array_inicial[selecionado].translateObj(2, 1.0);
			}
			else
			{
				lights.at(selecionado - quantObj).Tz += 0.2;
			}
			
			glutPostRedisplay();
			break;
		case '7': // gira o objeto em relacao ao seu eixo x
			if (selecionado < quantObj){
				array_inicial[selecionado].rotateObj(0);
			}
			glutPostRedisplay();
			break;
		case '8': // gira o objeto em relacao ao seu eixo y
			if (selecionado < quantObj){
				array_inicial[selecionado].rotateObj(1);
			}
			glutPostRedisplay();
			break;
		case '9': // gira o objeto em relacao ao seu eixo z
			if (selecionado < quantObj){
				array_inicial[selecionado].rotateObj(2);
			}
			glutPostRedisplay();
			break;
		case '-':
		case '_': // decrementa o tamanho do objeto em 1%
			if (selecionado < quantObj)
			{
			array_inicial[selecionado].escale(-1.0);
			}
			else
			{
				lights.at(selecionado - quantObj).Scale -= 0.01;
			}
			glutPostRedisplay();
			break;
		case '=': 
		case '+': // incrementa o tamanho do objeto em 1%
			if (selecionado < quantObj)
			{
			array_inicial[selecionado].escale(1.0);
			}
			else
			{
				lights.at(selecionado - quantObj).Scale += 0.01;
			}
			glutPostRedisplay();
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
		case 'o':
		case 'O': // funçao de diretor observador
			if (!directorView)
			{
				directorView = true;
			}
			else
			{
				directorView = false;
			}
			break;
		//aumenta nevoa
		case 'j':
		case 'J':
			if (n_pressionado)
			{
				densidade += 0.005f;
				Nevoa();
				glutPostRedisplay();
	}
			break;
		//diminui nevoa
		case 'k':
		case 'K':
			if (n_pressionado)
			{
				densidade -= 0.005f;
				Nevoa();
				glutPostRedisplay();
			}
			break;
		case 'n':
		case 'N':
			n_pressionado = true;
			break;
	}
}

void TeclaSolta(unsigned char tecla, int x, int y)
{
	switch (tecla)
	{
	case 'n':
	case 'N':
		n_pressionado = false;
		break;
	}
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{

	
	// Evita a divisao por zero
	if (h == 0) h = 1;

	float ratio = ((float)w)/ ((float)h);

	glViewport(0, 0, w, h);
	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_PROJECTION);
	//definir que todas as tranformações vão ser em camera (usuario)
	glLoadIdentity();

	gluPerspective(45.0, ratio, 0.1, 100.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW);
	// Especifica as dimensões da Viewport
	
	if (directorView)
	{
		aux_w = w / 2;
		aux_h = h;
	}
	
	

}

// Programa Principal 
int main()
{

	quantObj = Objeto::carregar_obj(array_inicial, "Obj Files/OBJS.obj");

	std::cout << quantObj << std::endl;
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
	// callback da funcao que interpreta uma tecla solta
	glutKeyboardUpFunc(TeclaSolta);
	Inicializa();
	
	//inicializar alguns parametros do glut (nessa caso a cor do fundo da tela).
	//cor que vai limpar o buffer
	glutMainLoop();
	//começa a execução da maquina de estados do glut/opengl que controla as funções
	//de callback (controlador de mouse, teclado, callback de controle de tela, etc).
	if (quantObj > 0) delete[] array_inicial;
}
