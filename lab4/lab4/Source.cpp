#include <gl/glut.h>
#include <cmath>
#include <math.h>
#include <stdlib.h>
#include <windows.h>

GLfloat angle = 0, plusangle = 0;
GLfloat angle2 = 0, plusangle2 = 0;
int ch1 = 0, ch2 = 0;

void init(void)
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myDisplay()
{
	glPushMatrix(); //��������� VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //������ � �������� ������ �����
	//������������� ������� ������ �������
	glEnable(GL_DEPTH_TEST); //��������� ������ �������� ��������� (�������� �������)
	gluLookAt(3, 3, 7, 0, 0, 0, 0, 1, 0); // VM=Fwe // ������� �����������

	GLfloat myLightPosition[] = { 1.0, 2.0, 2.0, 1.0 }; // �������� ����� � CKw

	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*������� ��-������� ����� �����
	������������� � CKe*/
	glEnable(GL_LIGHTING); // ��������� ������� ������������
	glEnable(GL_LIGHT0); // �������� ���� ���������� ��������
	GLfloat myDiffuse[] = { 0.714, 0.4284, 0.18144, 1 };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, myDiffuse); // �������� ����� � CKw
	GLfloat myShininess[] = { 25.6 };
	glMaterialfv(GL_FRONT, GL_SHININESS, myShininess);
	GLfloat myAmbient[] = { 0.2125, 0.1275, 0.054, 1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, myAmbient);
	GLfloat mySpecular[] = { 0.393548, 0.271906, 0.166721, 1 };
	glMaterialfv(GL_FRONT, GL_SPECULAR, mySpecular);

	glPushMatrix(); //��������� VM=Fwe
	glRotatef(angle2, 0, 1, 0); // ������� �������� �����
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition);
	glPopMatrix(); // ��������������� VM=Fwe

	glPushMatrix(); //��������� VM=Fwe
	glRotatef(angle, 0, 1, 0); // VM=Fwe*R

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

	// ����� f2 (�������� ������)
	glBegin(GL_POLYGON);
	glNormal3f(0, 0, 1);
	glVertex3f(0, 0, 1); glVertex3f(1.5, 1.5, 1);
	glVertex3f(1.5, 0, 1); 
	glEnd();


	// ����� f4 (����� ������)
	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glVertex3f(0, 0, 0); glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 1.5, 1); glVertex3f(0, 0, 1);
	glEnd();

	// ����� f1 (������ ������)
	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glVertex3f(1.5, 0, 0); glVertex3f(1.5, 1.5, 0);
	glVertex3f(1.5, 1.5, 1); glVertex3f(1.5, 0, 1);
	glEnd();

	glPopMatrix(); // ��������������� VM=Fwe

	glDisable(GL_LIGHTING); //��������� ���������

	glBegin(GL_LINES); //������ ������������ ��� ������� ����� � CKe
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(3, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 3, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 3);
	glEnd();

	//������ ����������� � ��������� ����� � CKe
	//glBegin(GL_LINES); glColor3f(0,0,0); glVertex3f(1, 2, 2); glVertex3f(0.0, 0.0, 0.0); glEnd();

	glPopMatrix();
	glutSwapBuffers();
	// usleep(50000);
}

void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
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
		if (ch2 % 2 == 0) plusangle2 = 0.1;
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

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH); //������������ �����
	//������� � ������� main(), ������������� ������������� ������ �������
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("���� 4, ������� 2 (��������������)");
	glutDisplayFunc(myDisplay);
	glutKeyboardFunc(keys);
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);

	init();
	glutMainLoop();
}