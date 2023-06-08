#include <iostream>
#include <gl\glut.h>
#include <atlbase.h>
#include <atlconv.h>
#include <string>
#include <cmath>
#include <math.h>
#include <Windows.h>
#include <stdlib.h>
#include <C:\Users\��������\Downloads\\GLAUX.H>
#pragma comment(lib, "C:/Users/��������/Downloads/GLAUX.LIB")
#pragma comment(lib, "legacy_stdio_definitions.lib")
GLfloat angle = 0, plusangle = 0;
GLfloat angle2 = 0, plusangle2 = 0;
int ch1 = 0, ch2 = 0;
GLuint list = 0, list2 = 0;
void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	AUX_RGBImageRec* image = auxDIBImageLoadA("image1.bmp"); //��� �������� � ����������� ������ �����������
	AUX_RGBImageRec* image2 = auxDIBImageLoadA("image2.bmp");
	AUX_RGBImageRec* image3 = auxDIBImageLoadA("image3.bmp");

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	list = glGenLists(1); //������������� ������ ��� ����� �����������������
	//��������.
		glNewList(list, GL_COMPILE); //����������� ����������� ������
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0, GL_RGB,
		GL_UNSIGNED_BYTE, image->data);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	// ����� f0 (���������)
	glBegin(GL_POLYGON);
	glNormal3f(0, -1, 0);
	glVertex3f(0, 0, 0); glVertex3f(1.5, 0, 0);
	glVertex3f(1.5, 0, 1); glVertex3f(0, 0, 1);
	glEnd();

	// ����� f1 (������ ������)
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, -1);
	glVertex3f(0, 0, 0); glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 0, 0);
	
	glEnd();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image3->sizeX, image3->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image3->data);
	// ����� f2 (�������� ������)
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1); glVertex3f(1.5, 1.5, 1);
	glVertex3f(1.5, 0, 1);

	glEnd();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image2->sizeX, image2->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image2->data);

	// ����� f4 (����� ������)
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0); glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 1.5, 1); glVertex3f(0, 0, 1);
	
	glEnd();
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0,
		GL_RGB, GL_UNSIGNED_BYTE, image->data);
	// ����� f1 (������ ������)
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(1.5, 0, 0); glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 1.5, 1); glVertex3f(1.5, 0, 1);
	glEnd();

	list2 = glGenLists(1); //������������� ������ ��� ����� �����������������
	//��������.
		glNewList(list2, GL_COMPILE);
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(2, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 2, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 2);
	glEnd();

	glEndList();
}
void myDisplay()
{
	glPushMatrix(); //��������� VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ � �������� ������
	//����� ������������� ������� ������ �������
		glEnable(GL_DEPTH_TEST); //��������� ������ �������� ��������� (��������
	//�������)
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0); // VM=Fwe // ������� �����������
	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 }; // �������� ����� � CKw
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*������� ��-������� �����
	����� ������������� � CKe*/
	glPushMatrix(); //��������� VM=Fwe
	glRotatef(angle2, 0, 1, 0); // ������� �������� �����
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glBegin(GL_LINES); // ������ ����������� � ��������� ����� � CKe
	glColor3f(1, 1, 1); glVertex3f(myLightPosition[0], myLightPosition[1],
		myLightPosition[2]); glVertex3f(0.0, 0.0, 0.0);
	glEnd();
	glPopMatrix(); // ��������������� VM=Fwe
	glEnable(GL_LIGHTING); // ��������� ������� ������������
	glEnable(GL_LIGHT0); // �������� ���� ���������� ��������
	glPushMatrix(); //��������� VM=Fwe
	glRotatef(angle, 0, 1, 0); // VM=Fwe*R
	GLfloat myDiffuse[] = { 0.75164, 0.60648, 0.22648, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // �������� ����� � CKw
	GLfloat myShininess[] = { 51.2 };
	glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
	GLfloat myAmbient[] = { 0.24725, 0.1995, 0.0745, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
	GLfloat mySpecular[] = { 0.628281, 0.555802, 0.366065, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);
	glCallList(list); //��������� ���������, � ������� ���������
	glPopMatrix(); // ��������������� VM=Fwe
	glDisable(GL_LIGHTING); //��������� ���������
	glCallList(list2); //��������� ���������, � ������� ���������
	glPopMatrix();
	glutSwapBuffers();
}
void myReshape(int width, int height)
{
	if (width / height < 1) {
		glViewport(0, 0, width, width);
	}
	else {
		glViewport(0, 0, height, height);
	}
}
void myIdle()
{
	angle += plusangle; if (angle > 360.0) angle = 0;
	angle2 += plusangle2; if (angle2 > 360.0) angle2 = 0;
	glutPostRedisplay();

}
void keys(unsigned char key, int x, int y)
{
	if (key == '0') {
		if (ch1 % 2 == 0) plusangle = 0.1;
		else plusangle = 0;
		ch1++;
	}
	else if (key == 'l') {
		if (ch2 % 2 == 0) plusangle2 = 0.5;
		else plusangle2 = 0;
		ch2++;
	}

	if (key == 'f') {
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
	}
	else if (key == 'b') {
		glCullFace(GL_FRONT);
		glEnable(GL_CULL_FACE);
	}
}
void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //������

		//�������� ���� �������� �������� ��������
	}
	else if (button == GLUT_RIGHT_BUTTON) {
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); //������

		//������� ���� �������� �������� ��������
	}
}
int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "");
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //������������ �����
	//������� � ������� main(), ������������� ������������� ������ �������
		glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("���� 5");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(mouseButton);
	glutKeyboardFunc(keys);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
