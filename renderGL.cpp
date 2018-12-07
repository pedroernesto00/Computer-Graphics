//Para compilar: g++ renderGL.cpp -o renderGL -lGL -lGLU -lGLEW -lglut -lm


#include <iostream>

#include <GL/freeglut.h>
#include <GL/glext.h>

#include "./product/modelsGL.h"

using namespace std;

//float porta_faces_vertices[porta_num_faces * 3 * 3];

float rot = 0.0;

/*

void prepararModelo()
{
	for (int i = 0; i < porta_num_faces * 9; i+=9)
	{
		//Vertice 1

		porta_faces_vertices[i] = porta_vertices[porta_faces[i/3] * 3];
		porta_faces_vertices[i+1] = porta_vertices[porta_faces[i/3] * 3 + 1];
		porta_faces_vertices[i+2] = porta_vertices[porta_faces[i/3] * 3 + 2];

		//Vertice 2

		porta_faces_vertices[i+3] = porta_vertices[porta_faces[i/3+1] * 3];
		porta_faces_vertices[i+4] = porta_vertices[porta_faces[i/3+1] * 3 + 1];
		porta_faces_vertices[i+5] = porta_vertices[porta_faces[i/3+1] * 3 + 2];

		//Vertice 3

		porta_faces_vertices[i+6] = porta_vertices[porta_faces[i/3+2] * 3];
		porta_faces_vertices[i+7] = porta_vertices[porta_faces[i/3+2] * 3 + 1];
		porta_faces_vertices[i+8] = porta_vertices[porta_faces[i/3	+2] * 3 + 2]; 
	}


	for (int i = 0; i < porta_num_faces * 9; i++) cout << porta_faces_vertices[i] << endl;
}

*/


void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glLoadIdentity();

	glPointSize(5);


	
	glColor3f(0.0, 0.0, 1.0);
	glTranslatef(0.0, -50.0, 0.0);
	glTranslatef(0.0, 0.0, -10.0);
	glScalef(20.0, 20.0, 1.0);
	glRotatef(-rot, 0, 1, 0);

	glVertexPointer(3, GL_FLOAT, 0, porta_vertices);
	glDrawElements(GL_TRIANGLES, porta_num_faces * 3, GL_UNSIGNED_INT, porta_faces);

	glColor3f(0.0, 1.0, 0.0);
	//janela glTranslatef(0.0, 2.0, 5.0);
	//mesa glTranslatef(2.0, 0.0, -1);
	//mesa glScalef(1.0, 1.0, 0.3);
	glVertexPointer(3, GL_FLOAT, 0, cadeira_vertices);
	glDrawElements(GL_TRIANGLES, cadeira_num_faces * 3, GL_UNSIGNED_INT, cadeira_faces);


	glColor3f(1.0, 0.0, 1.0);
	glVertexPointer(3, GL_FLOAT, 0, monitor_vertices);
	glDrawElements(GL_TRIANGLES, monitor_num_faces * 3, GL_UNSIGNED_INT, monitor_faces);

	glColor3f(1.0, 1.0, 0.0);
	glVertexPointer(3, GL_FLOAT, 0,  livro1_vertices);
	glDrawElements(GL_TRIANGLES, livro1_num_faces * 3, GL_UNSIGNED_INT, livro1_faces);


	glColor3f(0.0, 1.0, 1.0);
	glVertexPointer(3, GL_FLOAT, 0,  livro2_vertices);
	glDrawElements(GL_TRIANGLES, livro2_num_faces * 3, GL_UNSIGNED_INT, livro2_faces);

	glColor3f(0.0, 1.0, 0.1);
	glVertexPointer(3, GL_FLOAT, 0,  livro3_vertices);
	glDrawElements(GL_TRIANGLES, livro3_num_faces * 3, GL_UNSIGNED_INT, livro3_faces);


	glColor3f(1.0, 0.0, 1.0);
	glVertexPointer(3, GL_FLOAT, 0,  gavetas_vertices);
	glDrawElements(GL_TRIANGLES, gavetas_num_faces * 3, GL_UNSIGNED_INT, gavetas_faces);

	glColor3f(1.0, 1.0, 0.0);
	glVertexPointer(3, GL_FLOAT, 0,  lixeira_vertices);
	glDrawElements(GL_TRIANGLES, lixeira_num_faces * 3, GL_UNSIGNED_INT, lixeira_faces);

	glColor3f(0.1, 0.3, 1.0);
	glVertexPointer(3, GL_FLOAT, 0,  copo_vertices);
	glDrawElements(GL_TRIANGLES, copo_num_faces * 3, GL_UNSIGNED_INT, copo_faces);


	glVertexPointer(3, GL_FLOAT, 0,  piso_vertices);
	glDrawElements(GL_TRIANGLES, piso_num_faces * 3, GL_UNSIGNED_INT, piso_faces);
	
	glScalef(1.0, 1.0, 1);
	glColor3f(1.0, 0.0, 0.0);
	glVertexPointer(3, GL_FLOAT, 0, mesa_vertices);
	glDrawElements(GL_TRIANGLES, mesa_num_faces * 3, GL_UNSIGNED_INT, mesa_faces);


	/*

	glBegin(GL_TRIANGLES);
		for(int i = 0; i < porta_num_faces * 3 ; i++) glArrayElement(i);
	glEnd();

	*/

	glFlush();
}

void setup(void)
{
	//prepararModelo();

	//glEnable(GL_CULL_FACE);

	glClearColor(0.0, 0.0, 0.0, 0.0);

	glEnableClientState(GL_VERTEX_ARRAY);

	//glVertexPointer(3, GL_FLOAT, 0, porta_faces_vertices);

	//glVertexPointer(3, GL_FLOAT, 0, porta_vertices);
}

void resize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-30.0, 30.0, -30.0, 30.0, 2.0, 200.0);

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
		case 'a':
			rot += 1;
			glutPostRedisplay();
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

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(1000, 1000);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("renderOPENGL");
	glutDisplayFunc(drawScene);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyInput);

	setup();

	glutMainLoop();

	return 0;
}