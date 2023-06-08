#define _CRT_SECURE_NO_WARNINGS
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

/*��������� ��� �������� ��������� ����� �����������*/
struct Zagolovok
{
	GLint shirina; /*������*/
	GLint vysota; /*������*/
	GLenum formatCveta; /*������ ������������� �����*/
	GLenum formatKomponenty; /*������ ������ ���������� �����*/
	int kol_voKomponent; /*���������� ��������� �����*/
};
/*��������� ��� �������� �����������*/
struct Izobrajenie
{
	unsigned char* pikseli;
	Zagolovok zagolovok;
};
/*������� ������ ����������� �� ����� .kai*/
Izobrajenie* ChtenieIzobrajeniyaIzFaila(const char* szFileName)
{
	FILE* pFile; // ��������� �����
	Izobrajenie* iz = (Izobrajenie*)malloc(sizeof(Izobrajenie)); //�������� ��������� ����������� �����������
		// �������� �����
		pFile = fopen(szFileName, "rb");
	if (pFile == NULL) return NULL;
	// ��������� ���������
	fread(&(iz->zagolovok), sizeof(Zagolovok), 1, pFile);
	//�������� ������� ��� �����
	iz->pikseli = (unsigned char*)malloc(iz->zagolovok.shirina * iz->zagolovok.vysota * iz -> zagolovok.kol_voKomponent);
	// ���������� �����
	fread(iz->pikseli, iz->zagolovok.shirina * iz->zagolovok.vysota * iz -> zagolovok.kol_voKomponent, 1, pFile);
	// ������ � ������ �����������
	fclose(pFile);
	// ���������� ��������� �� ������ �����������
	return iz;
}
/*������� ������ ����������� � ���� .kai*/
GLint SohranenieIzobrajeniyaVfail(const char* szFileName)
{
	FILE* pFile; // ��������� �����
	//�������� ��������� ��� �������� �����������
	Izobrajenie* iz = (Izobrajenie*)malloc(sizeof(Izobrajenie));
	GLint iViewport[4]; //������ ��� �������� �������� ����� ���������
	// ��������� �������� ����� ���������
	glGetIntegerv(GL_VIEWPORT, iViewport);
	// ���������� ����� �� ������ �����
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ROW_LENGTH, 0);
	glPixelStorei(GL_PACK_SKIP_ROWS, 0);
	glPixelStorei(GL_PACK_SKIP_PIXELS, 0);
	// ������������ �� �������� �����
	glReadBuffer(GL_FRONT);
	//��������� ���������� �����������
	iz->zagolovok.shirina = iViewport[2];
	iz->zagolovok.vysota = iViewport[3];
	iz->zagolovok.formatCveta = GL_BGR_EXT;
	iz->zagolovok.formatKomponenty = GL_UNSIGNED_SHORT;
	iz->zagolovok.kol_voKomponent = 3;
	//��������� ������ ��� �������� �����
	iz->pikseli = (unsigned char*)malloc(iz->zagolovok.shirina * iz->zagolovok.vysota * iz -> zagolovok.kol_voKomponent);
	//������ �����
	glReadPixels(0, 0, iz->zagolovok.shirina, iz->zagolovok.vysota, iz->zagolovok.formatCveta, iz -> zagolovok.formatKomponenty, iz->pikseli);
	// �������� �����
	pFile = fopen(szFileName, "wb");
	// ������ ���������
	fwrite(&(iz->zagolovok), sizeof(Zagolovok), 1, pFile);
	// ������ ������ �� �����������
	fwrite(iz->pikseli, iz->zagolovok.shirina * iz->zagolovok.vysota * iz -> zagolovok.kol_voKomponent, 1, pFile);
	//�������� �����
	fclose(pFile);
	// �����
	return 1;
}
Izobrajenie* izobr; //������� �����������
Izobrajenie* izobr_bmp; //����������� �� ����� .bmp
Izobrajenie* izobr_kai; //����������� �� ����� .kai
Izobrajenie* izobr_ch_b; //�����-����� �����������
AUX_RGBImageRec* pImage = NULL; //����������� AUX_RGB
//���������� ��� �������� ������ ���������
static GLint rejim = 1;
// ������� ������� ��������� ����� � ����� �� ����� ������� �� ����
void ObrabotkaMenu(int punktMenu)
{
	// ������ ������ ������ ������������ �� ������,
	// ��������������� ������� ����
	rejim = punktMenu;
	// ������������ ��������������� ����������� glutPostRedisplay(); }
	glutPostRedisplay();
}
int k;
int iz = 0;
void Pererisovka(void)
{
	GLint iViewport[4];
	GLbyte *pModifiedBytes = NULL;
	GLfloat invertMap[256];
	GLint i;
	// ������� ���� ������� ������ �������
	glClear(GL_COLOR_BUFFER_BIT);
	// ������� ��������� ��������� ������ ������������� ������ ������� ���� ����
	glRasterPos2i(0.5, 0);
	// � ����������� �� ������� ������ ������������ ����������� ����������� �������� � ������������
		switch (rejim)
		{
		case 0: /*������� ������*/
			glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
			break;
		case 1: /*�������� ����������� �� ����� *.bmp*/
			pImage = auxDIBImageLoadA("image2.bmp");
			izobr_bmp = (Izobrajenie*)malloc(sizeof(Izobrajenie));
			izobr_bmp->zagolovok.shirina = pImage->sizeX;
			izobr_bmp->zagolovok.vysota = pImage->sizeY;
			izobr_bmp->pikseli = pImage->data;
			izobr_bmp->zagolovok.formatCveta = GL_BGR_EXT;
			izobr_bmp->zagolovok.formatKomponenty = GL_UNSIGNED_SHORT;
			izobr_bmp->zagolovok.kol_voKomponent = 3;
			izobr = izobr_bmp;
			break;
		case 2: /*�������� ������*/
			invertMap[0] = 1.0f;
			for (i = 1; i < 256; i++)
				invertMap[i] = 1.0f - (1.0f / 255.0f * (GLfloat)i);
			glPixelMapfv(GL_PIXEL_MAP_R_TO_R, 255, invertMap);
			glPixelMapfv(GL_PIXEL_MAP_G_TO_G, 255, invertMap);
			glPixelTransferi(GL_MAP_COLOR, GL_TRUE);
			break;
		
		default:
			break;
		}
	if (rejim != 0)
		// �������� �������
	{
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glDrawPixels(izobr->zagolovok.shirina, izobr->zagolovok.vysota, izobr -> zagolovok.formatCveta, izobr->zagolovok.formatKomponenty, izobr->pikseli);
	}
	//����������� ������
	glutSwapBuffers();
}
void IzmenenieRazmera(int w, int h)
{
	//������������� ������� �� ����, ����� ���� ������� ���������
	if (h == 0)
		h = 1;
	glViewport(0, 0, w, h);
	//������� ��������� ����������� ����� ������������
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
//����� ����� �������� ���������
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GL_DOUBLE);
	glutInitWindowSize(512, 512);
	glutCreateWindow("�������� ��� ���������");
	glutReshapeFunc(IzmenenieRazmera);
	glutDisplayFunc(Pererisovka);
	//��������� ���� � ����������� ����� ������
	glutCreateMenu(ObrabotkaMenu);
	glutAddMenuEntry("�������� �����", 0);
	glutAddMenuEntry("��������� ����������� .bmp", 1);;
	glutAddMenuEntry("�������� ������(��� ������)", 2);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	gluOrtho2D(0, 512, 0, 512);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	rejim = 0;
	glutMainLoop();
	// ����������� �������� ������ �����������
	free(izobr);
	free(izobr_ch_b);
	free(izobr_kai);
	free(izobr_bmp);
	free(pImage);
	return 0;
}