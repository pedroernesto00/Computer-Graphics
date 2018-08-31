
#include <GL/glew.h>
#include <GL/freeglut.h>

#pragma comment(lib, "glew32.lib") 

// Drawing routine.
void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	

	// Draw a polygon with specified vertices.

	// Quadrado
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex3f(-80.0, 40.0, 0.0); // Esquerdo inferior
	glVertex3f(-50.0, 40.0, 0.0); // Direito inferior
	glVertex3f(-50.0, 70.0, 0.0); // Direito superior
	glVertex3f(-80.0, 70.0, 0.0); // Esquerdo superior	
	glEnd();

	// Triangulo
	glColor3f(0.0, 0.8, 0.4);
	glBegin(GL_POLYGON);
	glVertex3f(-50.0, 10.0, 0.0); // Ponto esquerdo
	glVertex3f(-10.0, 10.0, 0.0); // Ponto direito
	glVertex3f(-10.0, 50.0, 0.0); // Ponsto superior
	glEnd();

	// Losango
	glColor3f(0.0, 0.589, 0.785);
	glBegin(GL_POLYGON);
	glVertex3f(-20.0, 20.0, 0.0);
	glVertex3f(80.0, 20.0, 0.0);
	glVertex3f(120.0, 120.0, 0.0);
	glVertex3f(20.0, 80.0, 0.0);
	glEnd();


	// Quadrado Cortado
	glColor3f(0.785, 0.0, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(-80.0, -70.0, 0.0); // Esquerdo inferior
	glVertex3f(-50.0, -70.0, 1.8); // Direito inferior
	glVertex3f(-50.0, -40.0, 0.0); // Direito superior
	glVertex3f(-80.0, -40.0, 0.0); // Esquerdo superior	
	glEnd();


	// Quadrado Maior
	glColor3f(0.8, 0.2, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(50.0, -70.0, 0.0); // Esquerdo inferior
	glVertex3f(80.0, -70.0, 0.0); // Direito inferior
	glVertex3f(80.0, -40.0, 0.0); // Direito superior
	glVertex3f(50.0, -40.0, 0.0); // Esquerdo superior	
	glEnd();

	// Quadrado Menor
	glColor3f(0.1, 0.8, 0.1);
	glBegin(GL_POLYGON);
	glVertex3f(60.0, -60.0, 0.0); // Esquerdo inferior
	glVertex3f(70.0, -60.0, 0.0); // Direito inferior
	glVertex3f(70.0, -50.0, 0.0); // Direito superior
	glVertex3f(60.0, -50.0, 0.0); // Esquerdo superior	
	glEnd();

	// Quadrado Colorido
	glBegin(GL_POLYGON);
	glColor3f(0.8, 0.1, 0.1);
	glVertex3f(-40.0, -90.0, 0.0); // Esquerdo inferior

	glColor3f(0.1, 0.8, 0.1);
	glVertex3f(40.0, -90.0, 0.0); // Direito inferior

	glColor3f(0.1, 0.1, 0.8);
	glVertex3f(40.0, -10.0, 0.0); // Direito superior

	glColor3f(0.8, 0.8, 0.1);
	glVertex3f(-40.0, -10.0, 0.0); // Esquerdo superior	

	glEnd();



	glFlush();
}

// Initialization routine.
void setup(void)
{
	glClearColor(30, 30, 30, 1);
}

// OpenGL window reshape routine.
void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-150.0, 150.0, -150.0, 150.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


// Main routine.
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("square.cpp");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	//	glutKeyboardFunc(keyInput);

	glewExperimental = GL_TRUE;
	glewInit();

	setup();

	glutMainLoop();
}