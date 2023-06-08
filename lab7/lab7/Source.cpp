#include <gl\glut.h>
#include <cmath>
#include <math.h>
#include <C:\Users\Владимир\Downloads\\GLAUX.H>
#pragma comment(lib, "C:/Users/Владимир/Downloads/GLAUX.LIB")
#pragma comment(lib, "legacy_stdio_definitions.lib")

void init();
void draw();
int count = 0;
float* X;
float* Y;
//Главная функция
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Лаба 6");
	init();
	glutDisplayFunc(draw);
	glutMainLoop();
}
//Функция инициализации
void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
		glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-100.0, 100.0, -100.0, 100.0);
}
//Функция рисования
void draw()
{
	GLfloat A = 100, B = 50, X = 0, Y = 0;
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(10, 10, 600, 400);
	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_LINES);
	glVertex2f(-100.0, 0.0); glVertex2f(100.0, 0.0);
	glVertex2f(0.0, 100.0); glVertex2f(0.0, -100.0);
	glEnd();
	// 3. y = 2px (2)
	int M_PI = 5;
	GLfloat X1 = -30, X2 = 30, Y1, Y2, dX, dY;
	Y1 = 2 * M_PI * X1; Y2 = 2 * M_PI * X2;
	glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_LINE_STRIP);
	dX = X2 - X1; dY = Y2 - Y1;
	glVertex2f(X1, Y1);
	while (X1 < X2) {
		X1 = X1 + 1;
		Y1 = Y1 + dY / dX;
		glVertex2f(X1, Y1);
	}
	glEnd();
	
	glFlush();
}