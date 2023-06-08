#include <GL/glut.h>
#include <math.h>
#include <iostream>
void init();
void draw();
float mass[21] = { 255,0,0,255,69,0,255,255,0,0,255,0,0,255,255,0,0,255,128,0,128 };
void main(int argc, char** argv) //Главная функция
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1200, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Myprog");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();

}
void init() //Функция инициализации
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
}
void draw()
{
	GLfloat l = -1, r = 1, b = -1, t = 1;
	GLint x = 0, y = 0, w = 200, h = 200;
	int q = 0, qw = 1, e = 2;
	glClear(GL_COLOR_BUFFER_BIT);
	gluOrtho2D(l, r, b, t);
	for (x = 0; x <= 1200; x += w)
		for (y = 0; y <= 800; y += h)
		{

			glViewport(x, y, w, h);
			glColor3f(0.0, 0.0, 0.0);
			glBegin(GL_LINE_LOOP);
			glVertex2f(-5.0, -5.0); glVertex2f(-5.0, 5.0);
			glVertex2f(5.0, 5.0); glVertex2f(5.0, -5.0);
			glEnd();
			glColor3f(mass[q], mass[qw], mass[e]);
			glBegin(GL_POLYGON);
			glVertex2f(-2.0, -2.0); glVertex2f(-2.0, 0.0); glVertex2f(2.0, 2.0); glVertex2f(2.0, 0.0); glVertex2f(2.0, -2.0);
			glEnd();
			q += 3; qw += 3; e += 3;
			if (e > 21) { q = 0; qw = 1; e = 2; }

		}
	glFlush();
}
