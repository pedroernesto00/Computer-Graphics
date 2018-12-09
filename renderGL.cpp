//Para compilar: g++ renderGL.cpp -o renderGL -lGL -lGLU -lGLEW -lglut -lm

/*
	TO-DO

	1) Definir parâmetros dos materiais de cada objeto


*/




#include <iostream>

#include <GL/freeglut.h>
#include <GL/glext.h>
#include <cmath>

#include "./product/modelsGL.h"

using namespace std;



//float porta_faces_vertices[porta_num_faces * 3 * 3];

float rot = 0.0f;
float rot2 = 0.0f;


float transZ = 0.0f;
float transX = 0.0f;

float angleAlpha = 0.0f;
float angleBeta = 0.0f;
float pi = 3.14159265359;

/* -------------------------- PARÂMETROS DOS MATERIAIS ----------------------------------- */


	float matAmbAndDif1[] = {1.0, 0.5, 1.0, 1.0};
   	float matAmbAndDif2[] = {0.5, 0.31, 1.0, 1.0};
   	float matAmbAndDif3[] = {0.0, 0.0, 0.9, 1.0};
   	float matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float matShine[] = {1.0};


   	float matAmbAndDifOuro[] = {0.75164f, 0.60648f, 0.22648f, 1.0f};
   	float matSpecOuro[] = {0.628281f, 0.555802f, 0.366065f, 1.0f};
   	float matShineOuro[] = {51.2};

   	float janela_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float janela_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float janela_matShine[] = {1.0};

   	float porta_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float porta_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float porta_matShine[] = {1.0};

   	float cadeira_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float cadeira_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float cadeira_matShine[] = {1.0};

   	float gavetas_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float gavetas_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float gavetas_matShine[] = {1.0};

   	float piso_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float piso_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float piso_matShine[] = {1.0};

   	float lixeira_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float lixeira_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float lixeira_matShine[] = {1.0};

   	float monitor_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float monitor_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float monitor_matShine[] = {1.0};

   	float livro1_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float livro1_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float livro1_matShine[] = {1.0};

   	float livro2_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float livro2_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float livro2_matShine[] = {1.0};

   	float livro3_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float livro3_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float livro3_matShine[] = {1.0};


   	float copo_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float copo_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float copo_matShine[] = {1.0};


   	float mesa_matAmbAndDif[] = {1.0, 0.5, 0.31, 1.0};
   	float mesa_matSpec[] = {0.1, 0.1, 0.1, 1.0};
   	float mesa_matShine[] = {1.0};


/* ------------------------------------------------------------------------------------------ */   	


/*

	Funções para lidar com eventos do scroll do mouse e para criar o menu.
	O menu é ativado com um clique do botão direito do mouse.



*/


void mouse(int button, int state, int x, int y)
{
	if((button == 3) || (button == 4) )
	{
		if (state == GLUT_UP) return;

		(button == 3) ? transZ++ : transZ--;
	}

	if((button == 5) || (button == 6) )
	{
		if (state == GLUT_UP) return;

		(button == 5) ? transX++ : transX--;
	}

	glutPostRedisplay();
}

void top_menu(int id)
{
	if (id == 1) exit(0);
}

void color_menu(int id)
{
	if (id == 1) exit(0);
}

void janela_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		janela_matAmbAndDif[0] = 0.75164f;
   		janela_matAmbAndDif[1] = 0.60648f;
   		janela_matAmbAndDif[2] = 0.22648f;
   		janela_matAmbAndDif[3] = 1.0f;
   	
   		janela_matSpec[0] = 0.628281f;
   		janela_matSpec[1] = 0.555802f;
   		janela_matSpec[2] = 0.366065f;
   		janela_matSpec[3] = 1.0f;

   		janela_matShine[0] = 51.2;

   		glutPostRedisplay();		
	}
}

void porta_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		porta_matAmbAndDif[0] = 0.75164f;
   		porta_matAmbAndDif[1] = 0.60648f;
   		porta_matAmbAndDif[2] = 0.22648f;
   		porta_matAmbAndDif[3] = 1.0f;
   	
   		porta_matSpec[0] = 0.628281f;
   		porta_matSpec[1] = 0.555802f;
   		porta_matSpec[2] = 0.366065f;
   		porta_matSpec[3] = 1.0f;

   		porta_matShine[0] = 51.2;

   		glutPostRedisplay();		
	}
}

void cadeira_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		cadeira_matAmbAndDif[0] = 0.75164f;
   		cadeira_matAmbAndDif[1] = 0.60648f;
   		cadeira_matAmbAndDif[2] = 0.22648f;
   		cadeira_matAmbAndDif[3] = 1.0f;
   	
   		cadeira_matSpec[0] = 0.628281f;
   		cadeira_matSpec[1] = 0.555802f;
   		cadeira_matSpec[2] = 0.366065f;
   		cadeira_matSpec[3] = 1.0f;

   		cadeira_matShine[0] = 51.2;

   		glutPostRedisplay();
	}
}

void lixeira_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		lixeira_matAmbAndDif[0] = 0.75164f;
   		lixeira_matAmbAndDif[1] = 0.60648f;
   		lixeira_matAmbAndDif[2] = 0.22648f;
   		lixeira_matAmbAndDif[3] = 1.0f;
   	
   		lixeira_matSpec[0] = 0.628281f;
   		lixeira_matSpec[1] = 0.555802f;
   		lixeira_matSpec[2] = 0.366065f;
   		lixeira_matSpec[3] = 1.0f;

   		lixeira_matShine[0] = 51.2;

   		glutPostRedisplay();
	}
}

void gavetas_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		gavetas_matAmbAndDif[0] = 0.75164f;
   		gavetas_matAmbAndDif[1] = 0.60648f;
   		gavetas_matAmbAndDif[2] = 0.22648f;
   		gavetas_matAmbAndDif[3] = 1.0f;
   	
   		gavetas_matSpec[0] = 0.628281f;
   		gavetas_matSpec[1] = 0.555802f;
   		gavetas_matSpec[2] = 0.366065f;
   		gavetas_matSpec[3] = 1.0f;

   		gavetas_matShine[0] = 51.2;	

   		glutPostRedisplay();
	}
}

void piso_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		piso_matAmbAndDif[0] = 0.75164f;
   		piso_matAmbAndDif[1] = 0.60648f;
   		piso_matAmbAndDif[2] = 0.22648f;
   		piso_matAmbAndDif[3] = 1.0f;
   	
   		piso_matSpec[0] = 0.628281f;
   		piso_matSpec[1] = 0.555802f;
   		piso_matSpec[2] = 0.366065f;
   		piso_matSpec[3] = 1.0f;

   		piso_matShine[0] = 51.2;

   		glutPostRedisplay();

	}
}

void monitor_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		 monitor_matAmbAndDif[0] = 0.75164f;
   		monitor_matAmbAndDif[1] = 0.60648f;
   		monitor_matAmbAndDif[2] = 0.22648f;
   		monitor_matAmbAndDif[3] = 1.0f;
   	
   		monitor_matSpec[0] = 0.628281f;
   		monitor_matSpec[1] = 0.555802f;
   		monitor_matSpec[2] = 0.366065f;
   		monitor_matSpec[3] = 1.0f;

   		monitor_matShine[0] = 51.2;

   		glutPostRedisplay();
	}
}

void livro1_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		livro1_matAmbAndDif[0] = 0.75164f;
   		livro1_matAmbAndDif[1] = 0.60648f;
   		livro1_matAmbAndDif[2] = 0.22648f;
   		livro1_matAmbAndDif[3] = 1.0f;
   	
   		livro1_matSpec[0] = 0.628281f;
   		livro1_matSpec[1] = 0.555802f;
   		livro1_matSpec[2] = 0.366065f;
   		livro1_matSpec[3] = 1.0f;

   		livro1_matShine[0] = 51.2;

   		glutPostRedisplay();
	}
}

void livro2_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		 livro2_matAmbAndDif[0] = 0.75164f;
   		livro2_matAmbAndDif[1] = 0.60648f;
   		livro2_matAmbAndDif[2] = 0.22648f;
   		livro2_matAmbAndDif[3] = 1.0f;
   	
   		livro2_matSpec[0] = 0.628281f;
   		livro2_matSpec[1] = 0.555802f;
   		livro2_matSpec[2] = 0.366065f;
   		livro2_matSpec[3] = 1.0f;

   		livro2_matShine[0] = 51.2;		

   		glutPostRedisplay();
	}
}

void livro3_menu(int id)
{
	if (id == 1) exit(0);
	if (id == 2)
	{
		 livro3_matAmbAndDif[0] = 0.75164f;
   		livro3_matAmbAndDif[1] = 0.60648f;
   		livro3_matAmbAndDif[2] = 0.22648f;
   		livro3_matAmbAndDif[3] = 1.0f;
   	
   		livro3_matSpec[0] = 0.628281f;
   		livro3_matSpec[1] = 0.555802f;
   		livro3_matSpec[2] = 0.366065f;
   		livro3_matSpec[3] = 1.0f;

   		livro3_matShine[0] = 51.2;		

   		glutPostRedisplay();
	}
}

void makeMenu(void)
{
	int sub_menuJanela = glutCreateMenu(janela_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuPorta = glutCreateMenu(porta_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuCadeira = glutCreateMenu(cadeira_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuLixeira = glutCreateMenu(lixeira_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuGavetas = glutCreateMenu(gavetas_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuPiso = glutCreateMenu(piso_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuMonitor = glutCreateMenu(monitor_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuLivro1 = glutCreateMenu(livro1_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuLivro2 = glutCreateMenu(livro2_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menuLivro3 = glutCreateMenu(livro3_menu);
	glutAddMenuEntry("Sair", 1);
	glutAddMenuEntry("Ouro", 2);

	int sub_menu;
	sub_menu = glutCreateMenu(color_menu);
	glutAddSubMenu("Janela", sub_menuJanela);
	glutAddSubMenu("Porta", sub_menuPorta);
	glutAddSubMenu("Cadeira", sub_menuCadeira);
	glutAddSubMenu("Lixeira", sub_menuLixeira);
	glutAddSubMenu("Gavetas", sub_menuGavetas);
	glutAddSubMenu("Piso", sub_menuPiso);
	glutAddSubMenu("Monitor", sub_menuMonitor);
	glutAddSubMenu("Livro 1", sub_menuLivro1);
	glutAddSubMenu("Livro 2", sub_menuLivro2);
	glutAddSubMenu("Livro 3", sub_menuLivro3);
	glutAddMenuEntry("Sair", 1);


	glutCreateMenu(top_menu);
	glutAddSubMenu("Objeto", sub_menu);
	glutAddMenuEntry("Sair", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}


/* -------------------------------------------------- */


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	
	
	
   	

	/* ------------------------------------ TRANSFORMAÇÕES -------------------------------------- */
	glTranslatef(0.0, -50.0, 0.0); //  0.0 -10.0 0.0: EM CASO DE PROJEÇÃO PARALELA
	glTranslatef(0.0 + transX, 0.0, -10.0 + transZ);
	glScalef(20.0, 20.0, 1.0);
	//glRotatef(-rot, 0, 1, 0);	
	/* ------------------------------------------------------------------------------------------- */
	

	/* ------------------------------------ DEFINIÇÃO DO OBSERVADOR ------------------------------------ */

	//gluLookAt(0.33 * cos(angle), 0.0, 0.33 * sin(angle), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	gluLookAt( 0.33 * cos(angleBeta) * cos(angleAlpha), 0.33 * sin(angleBeta), 0.33 * cos(angleBeta) * sin(angleAlpha), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	//gluLookAt( 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); //Em caso de projeção paralela. (Isométrica)
	

	/* ----------------------------------------------------------------------------------------------- */
	


 	/* --------------------------------------    OBJETOS:  ------------------------------------------ */

	
	glPushMatrix();
	glTranslatef(0.0, -1.0, 0.0);

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);

   	glVertexPointer(3, GL_FLOAT, 0, paredes_vertices);
	glNormalPointer(GL_FLOAT, 0, paredes_normais);
	glDrawElements(GL_TRIANGLES, paredes_num_faces * 3, GL_UNSIGNED_INT, paredes_faces);	

	glPopMatrix();


	/* 
	------------------    DESENHO DA JANELA: FRAME E VIDRO ----------------
	*/

	glPushMatrix();
	glTranslatef(-1, 2, 3.5);
	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif1);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);


	/*
					JANELA INTEIRA
	glVertexPointer(3, GL_FLOAT, 0, janela_vertices);
	glNormalPointer(GL_FLOAT, 0, janela_normais);
	glDrawElements(GL_TRIANGLES, janela_num_faces * 3, GL_UNSIGNED_INT, janela_faces);
	
	*/

	/* 
	   ------------ FRAME DA JANELA ------------------
	*/
	glVertexPointer(3, GL_FLOAT, 0, frame_vertices);
	glNormalPointer(GL_FLOAT, 0, frame_normais);
	glDrawElements(GL_TRIANGLES, frame_num_faces * 3, GL_UNSIGNED_INT, frame_faces);

	
	/*
	  -------------- VIDRO DA JANELA -------------------
	*/

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif2);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
   	float emissao[] = {0.1f, 0.1f, 0.4f, 1.0f};
   	glMaterialfv(GL_FRONT, GL_EMISSION, emissao);



   	glVertexPointer(3, GL_FLOAT, 0, vidro_vertices);
	glNormalPointer(GL_FLOAT, 0, vidro_normais);
	glDrawElements(GL_TRIANGLES, vidro_num_faces * 3, GL_UNSIGNED_INT, vidro_faces);

	float emissao2[] = {0.0f, 0.0f, 0.0f, 1.0f};
   	glMaterialfv(GL_FRONT, GL_EMISSION, emissao2);
	
	glPopMatrix();

	/* -------------------------------------------------------------------- */
	
	
	
	/*
		 --------------------- DESENHO DA PORTA --------------------

	*/

	/*
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, matAmbAndDifOuro);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpecOuro);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShineOuro);
	*/

   	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, porta_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, porta_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, porta_matShine);

	glPushMatrix();
	glTranslatef(2.5, 0.0, -5);
	glRotatef(-90, 0, 1, 0);
	glVertexPointer(3, GL_FLOAT, 0, porta_vertices);
	glNormalPointer(GL_FLOAT, 0, porta_normais);
	glDrawElements(GL_TRIANGLES, porta_num_faces * 3, GL_UNSIGNED_INT, porta_faces);
	glPopMatrix();


	/* -------------------------------------------------------------------- */

	

	/*
		----------------------- DESENHO DA CADEIRA -------------------------
	*/
	

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, cadeira_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, cadeira_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, cadeira_matShine);
	
	glVertexPointer(3, GL_FLOAT, 0, cadeira_vertices);
	glNormalPointer(GL_FLOAT, 0, cadeira_normais);
	glDrawElements(GL_TRIANGLES, cadeira_num_faces * 3, GL_UNSIGNED_INT, cadeira_faces);

	/* ---------------------------------------------------------------------- */


	/*
		----------------------- DESENHO DO MONITOR ---------------------------

	*/
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, monitor_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, monitor_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, monitor_matShine);
   		

	glVertexPointer(3, GL_FLOAT, 0, monitor_vertices);
	glNormalPointer(GL_FLOAT, 0, monitor_normais);
	glDrawElements(GL_TRIANGLES, monitor_num_faces * 3, GL_UNSIGNED_INT, monitor_faces);

	/* ------------------------------------------------------------------------ */

	
	/*
		------------------------ DESENHO DO LIVRO1 ---------------------------
	*/



	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, livro1_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, livro1_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, livro1_matShine);

	
	glNormalPointer(GL_FLOAT, 0, livro1_normais);
	glVertexPointer(3, GL_FLOAT, 0,  livro1_vertices);
	glDrawElements(GL_TRIANGLES, livro1_num_faces * 3, GL_UNSIGNED_INT, livro1_faces);

	/* ---------------------------------------------------------------------- */



	/*
		--------------------------- DESENHO DO LIVRO2 ---------------------------
	*/

	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, livro2_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, livro2_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, livro2_matShine);
   	

   	glNormalPointer(GL_FLOAT, 0, livro2_normais);
	glVertexPointer(3, GL_FLOAT, 0,  livro2_vertices);
	glDrawElements(GL_TRIANGLES, livro2_num_faces * 3, GL_UNSIGNED_INT, livro2_faces);

	/* ------------------------------------------------------------------------- */

	
	
	/*

		--------------------------- DESENHO DO LIVRO 3 ----------------------------

	*/


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, livro3_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, livro3_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, livro3_matShine);
	
	glNormalPointer(GL_FLOAT, 0, livro3_normais);
	glVertexPointer(3, GL_FLOAT, 0,  livro3_vertices);
	glDrawElements(GL_TRIANGLES, livro3_num_faces * 3, GL_UNSIGNED_INT, livro3_faces);

	/* ---------------------------------------------------------------------------- */


	/*
		------------------------------ DESENHO DA GAVETA -----------------------------
	*/


	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, gavetas_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, gavetas_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, gavetas_matShine);
	
	glNormalPointer(GL_FLOAT, 0, gavetas_normais);
	glVertexPointer(3, GL_FLOAT, 0,  gavetas_vertices);
	glDrawElements(GL_TRIANGLES, gavetas_num_faces * 3, GL_UNSIGNED_INT, gavetas_faces);

	/* --------------------------------------------------------------------------------*/


	/*
		----------------------------------- DESENHO DA LIXEIRA ------------------------
	*/
	
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, lixeira_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, lixeira_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, lixeira_matShine);
	
	glNormalPointer(GL_FLOAT, 0, lixeira_normais);
	glVertexPointer(3, GL_FLOAT, 0,  lixeira_vertices);
	glDrawElements(GL_TRIANGLES, lixeira_num_faces * 3, GL_UNSIGNED_INT, lixeira_faces);

	/* -------------------------------------------------------------------------------------- */

	
	/*
		------------------------------------- DESENHO DO COPO -------------------------------
	*/

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, copo_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, copo_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, copo_matShine);

	glNormalPointer(GL_FLOAT, 0, copo_normais);
	glVertexPointer(3, GL_FLOAT, 0,  copo_vertices);
	glDrawElements(GL_TRIANGLES, copo_num_faces * 3, GL_UNSIGNED_INT, copo_faces);

	/* --------------------------------------------------------------------------- */


	/*
		----------------------------------- DESENHO DO PISO ---------------------------------
	*/

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, piso_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, piso_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, piso_matShine);
	
	glNormalPointer(GL_FLOAT, 0, piso_normais);
	glVertexPointer(3, GL_FLOAT, 0,  piso_vertices);
	glDrawElements(GL_TRIANGLES, piso_num_faces * 3, GL_UNSIGNED_INT, piso_faces);

	/* ------------------------------------------------------------------------------ */
	
	/*
		---------------------------------------- DESENHO DA MESA --------------------------
	*/

	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mesa_matAmbAndDif);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mesa_matSpec);
   	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mesa_matShine);

	
	glNormalPointer(GL_FLOAT, 0, mesa_normais);
	glVertexPointer(3, GL_FLOAT, 0, mesa_vertices);
	glDrawElements(GL_TRIANGLES, mesa_num_faces * 3, GL_UNSIGNED_INT, mesa_faces);

	/* -------------------------------------------------------------------------------- */


	glFlush();
}

void setup(void)
{
	//prepararModelo();
	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnable(GL_NORMALIZE);



	
 
   	/* ------------------ Parâmetros da fonte luminosa 1 ----------------------- */
	

	float lightAmb[] = {0.0, 0.0, 0.0, 1.0};
   	float lightDifAndSpec[] = {0.3, 0.3, 0.3, 1.0};
   	glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
   	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDifAndSpec);
   	glLightfv(GL_LIGHT0, GL_SPECULAR, lightDifAndSpec);

   	float lightPos[] = {0.0, 100.0, 400.0 , 1.0};

   	//float lightPos[] = {-50.0, 20.0, -50.0 , 1.0};

   	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);
   	
   	/* -------------------------------------------------------------------------- */
   	

   	/* ------------------ Parâmetros luz ambiente ------------------------------- */
   	float globAmb[] = {0.4, 0.4, 0.4, 1.0};   
   	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb); // Global ambient light.

   	/* ----------------------------------------------------------------------- */
   	

   	/* ------------------ Características gerais da iluminação ----------------- */

   	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE); // Enable two-sided lighting.
   	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

   	/* ------------------------------------------------------------------------- */

	makeMenu();

}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glFrustum(-30.0, 30.0, -30.0, 30.0, 2.0, 200.0);
	//glOrtho(-30.0, 30.0, -30.0, 30.0, -2.0, 200.0); //em caso de projeção paralela : isométrica
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void keyInput(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(0);
			break;
		case 'q':
			rot += 50; //95
			glutPostRedisplay();
			break;
		case 'e':
			rot -= 50;
			glutPostRedisplay();
			break;
		case 'w':
			transZ += 1.0;
			glutPostRedisplay();
			break;
		case 's':
			transZ -= 1.0;
			glutPostRedisplay();
			break;
		case 'd':
			transX -= 1.0;
			glutPostRedisplay();
			break;
		case 'a':
			transX += 1.0;
			glutPostRedisplay();
			break;
		case 'z':
			angleAlpha += pi/6;
			glutPostRedisplay();
			break;	
		case 'x':
			angleAlpha -= pi/6;
			glutPostRedisplay();
			break;
		case 'Z':
			angleBeta += pi/6;
			glutPostRedisplay();
			break;
		case 'X':
			angleBeta -= pi/6;
			glutPostRedisplay();
			break;
		default:
			break;
	}
}

void printInteraction(void)
{
	cout << "Interaction: " << endl;
	cout << "Press ESC to exit" << endl;
	
}

int main(int argc, char **argv)
{
	printInteraction();
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("cenarioOPENGL");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);
	glutMouseFunc(mouse);

	setup();

	glutMainLoop();

	return 0;
}