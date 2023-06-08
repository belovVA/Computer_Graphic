#include <gl\glut.h>
#include <math.h>
#include <windows.h>
GLfloat angle = 0;
GLfloat resize = 0.5;
GLfloat posz = 0;
GLfloat dx = 0;
void init(void)
{
	glClearColor(1.0, 0.5, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 1, 1, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void myDisplay()
{
	glPushMatrix(); //��������� VM = 1
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	gluLookAt(3, 1, 1, 0, 0, 0, 0, 1, 0); // VM=Fwe ������� �����������
	GLfloat myLightPosition[] = { 100.0, 55.0, 6.0, 1.0 }; // �������� ����� � CKw
	glLightfv(GL_LIGHT0, GL_POSITION, myLightPosition); /*������� ��������� ����� ����� ������������� � CKe*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glPushMatrix(); //��������� VM=Fwe
	//glRotatef(angle, -1, 0, 0); // VM=Fwe*R
	glRotatef(angle, 0, 0, 1); // VM=Fwe*R*R
	//glRotatef(angle, 0, 0, -1); // VM=Fwe*R*R*R
	//glutWireCube(0.95);
	glScalef(resize, resize, resize); //������� ��������
	glutSolidOctahedron(); //�������
	glPopMatrix(); // ��������������� VM=Fwe
	glDisable(GL_LIGHTING); //��������� ���������
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); glVertex3f(0, 0, 0); glVertex3f(1, 0, 0);
	glColor3f(0, 1, 0); glVertex3f(0, 0, 0); glVertex3f(0, 1, 0);
	glColor3f(0, 0, 1); glVertex3f(0, 0, 0); glVertex3f(0, 0, 1);
	glEnd();
	//glBegin(GL_LINES);//����� �����
	//glColor3f(1, 1, 1); glVertex3f(100, 55, 6); glVertex3f(0.0, 0.0, 0.0);
	//glEnd();
	glPopMatrix();

	glutSwapBuffers();
	Sleep(30); //�������� ��������

}
void myResMB(int button, int state, int x, int y) // ��������� ������� ������ �������� ������ �����
{
	if (state == GLUT_UP)
	{
		if (button == GLUT_LEFT_BUTTON)
		{
			resize *= 1.5;
		}
		if (button == GLUT_RIGHT_BUTTON)
		{
			resize *= 0.5;
		}
	}
}
void myResKB(unsigned char key, int x, int y) // ��������� �������� �� �������� � � Y
{
	switch (key)
	{
	case 'x':
		// ����������� ��������� � ��. (���Z, �) ������ ������� �� �.�.
		glMatrixMode(GL_MODELVIEW);
		glTranslatef(0, 0, -3);
		glRotatef(2, 0, 0, 1);
		glTranslatef(0, 0, 3);
		glutPostRedisplay();
		break;
	case 'y':
		// ����������� ��������� � ��. (���Z, �) ������ �.�.
		while (true) {
			glMatrixMode(GL_MODELVIEW);
			glTranslatef(0, 0, 0);
			glRotatef(-2, 0, 0, 1);
			glTranslatef(0, 0, 3);
			glutPostRedisplay();

		}
		break;

	default:
		break;
	}
}

void myReshape(int width, int height)
{
	if (width / height < 1) glViewport(0, 0, width, width);
	else glViewport(0, 0, height, height);
}
void myIdle()
{
	angle += dx;
	if (angle > 360.0) angle = 0;
	glutPostRedisplay();
}
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("my window");
	glutDisplayFunc(myDisplay);
	glutMouseFunc(myResMB); //������� ����
	glutKeyboardFunc(myResKB); //����������
	glutReshapeFunc(myReshape);
	glutIdleFunc(myIdle);
	init();
	glutMainLoop();
}
