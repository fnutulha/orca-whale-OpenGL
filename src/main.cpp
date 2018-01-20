
#include <iostream>
#include "glut.h"
#include <math.h>
//#include "glfw.h"
//#include "StdAfx.h"

typedef struct _Vector

{
	double x, y, z;

} Vector;

GLuint mysphereID;

double i = 0, i1 = 0, j = 0, jtwo = 0, k1 = 0, k = 0, l = 0, l1 = 0;
double x_5 = 0, y_5 = 0, x_6 = 0, y_6 = 0, x_7 = 0, y_7 = 0, x_8 = 0, y_8 = 0, x_9 = 0, y_9 = 0, x_10 = 0, y_10 = 0, x_11 = 0, y_11 = 0, x_12 = 0, y_12 = 0, x_13 = 0, y_13 = 0, x_14 = 0, y_14 = 0, x_15 = 0, y_15 = 0, x_16 = 0, y_16 = 0, x_17 = 0, y_17 = 0;
int step = 0;
int time1 = 50;
int time2 = 50;
int beta = 0;
double amplitude = 10;
//float i = 0;
int alpha = 0;
GLuint loadandbufferimage(const char* filename);
const int W_SCREEN = 1366;
const int H_SCREEN = 768;
const double PI = 3.14159265;
GLUquadric *qobja;
double speed = 3.0;
double radian1, radian2, radian3, radian4, radian5, radian6, radian7, radian8, radian9, radian10, radian11, radian12, radian13, radian14, radian15, radian16, radian17;
GLuint _texturebufferid;
Vector pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12, pos13, pos14, pos15;
Vector vel;
Vector dis1, dis2, dis3, dis4, dis5, dis6, dis7, dis8, dis9, dis10, dis11, dis12, dis13, dis14, dis15, dis16;
double gamma = 0;
Vector dir;
Vector mousecoords;
Vector wormcoords;
int fx, fy;
bool mousestate = 0;

void draw_cyl_1(float j, float k);
void draw_cyl_2(float j, float k);
void draw_cyl_3(float j, float k);
void draw_cyl_4(float j, float k);
void draw_cyl_5(float j, float k);
void draw_cyl_6(float j, float k);
void draw_cyl_7(float j, float k);
void draw_cyl_8(float j, float k);
void draw_cyl_9(float j, float k);
void draw_cyl_10(float j, float k);
void draw_pyr();
int winw, winh;
int gapper = 0;

//GLuint loadandbufferimage(const char *filename);
//
//GLuint loadandbufferimage(const char *filename)
//{
//	GLFWimage imagedata;
//	glfwReadImage(filename, &imagedata, NULL);
//	GLuint texturebufferid;
//	glGenTextures(1, &texturebufferid);
//	glBindTexture(GL_TEXTURE_2D, texturebufferid);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imagedata.Width, imagedata.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imagedata.Data);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
//	glfwFreeImage(&imagedata);
//	return texturebufferid;
//}

GLuint Load_Tex(char *file)
{
	unsigned char *buffer;
	JPEG_CORE_PROPERTIES image = { 0 };

	if (ijlInit(&image) != IJL_OK)
	{
		printf("jpg %s is not loaded::can not init ijl \n", file);
		return 0;
	}

	image.JPGFile = file;

	if (ijlRead(&image, IJL_JFILE_READPARAMS) != IJL_OK)
	{
		printf("jpg %s is not loaded::corrupted jpg \n", file);
		return 0;
	}

	buffer = new unsigned char[image.JPGWidth*image.JPGHeight * 3];
	image.DIBBytes = buffer;
	image.DIBColor = IJL_RGB;
	image.DIBHeight = image.JPGHeight;
	image.DIBWidth = image.JPGWidth;
	image.DIBChannels = 3;


	if (ijlRead(&image, IJL_JFILE_READWHOLEIMAGE) == IJL_OK)
	{
		GLuint handle;
		glGenTextures(1, &handle);
		glBindTexture(GL_TEXTURE_2D, handle);

		glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_COMPRESSED_RGB_S3TC_DXT1_EXT,
			image.JPGHeight,
			image.JPGWidth,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			buffer);


		delete buffer;
		ijlFree(&image);

		printf("jpg %s is loaded:: X=%i Y=%i, OpenGL desc %i\n",
			file, image.JPGHeight, image.JPGWidth, handle);

		return handle;
	}

	delete buffer;
	ijlFree(&image);

	printf("jpg %s is not loaded::corrupted jpg \n", file);


	return 0;
}


void passive(int x1, int y1)
{
	mousecoords.x = x1;
	mousecoords.y = y1;

	wormcoords.x = ((double)mousecoords.x - winw / 2);
	wormcoords.y = 1 - ((double)mousecoords.y - winh / 2);
}

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);

	winw = width;
	winh = height;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		mousestate = (state == GLUT_DOWN);
		//		step = 0;
		glutPostRedisplay();
	}
	mousecoords.x = x;
	mousecoords.y = y;
	wormcoords.x = ((double)mousecoords.x - winw / 2);
	wormcoords.y = 1 - ((double)mousecoords.y - winh / 2);

}

void draw_cyl_1(float j, float k)
{
	//	GLuint handle = Load_Tex("IMGS\\blue.jpg");
	//	glGenTextures(1, &handle);
	//	glBindTexture(GL_TEXTURE_2D, handle);
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, 8 * sqrt(100.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_2(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(120.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_3(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude* sqrt(140.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_4(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(160.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_5(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(180.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_6(float j, float k) //fin begins here
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glTranslatef(-130, -30, 0);
	glRotatef(30.0f, 0.0f, 0.0f, 1.0f);
	glScalef(1.5, 0.5, 2);
	gluCylinder(qobja, 0, amplitude*sqrt(40.0), 10, 200, 200);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(j, k, 0);
	glTranslatef(130, -30, 0);
	glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
	glScalef(1.5, 0.5, 1);
	gluCylinder(qobja, 0, amplitude*sqrt(40.0), 10, 200, 200);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(j, k, 0);
	glTranslatef(0, 150, 0);
	//glRotatef(-30.0f, 0.0f, 0.0f, 1.0f);
	glScalef(0.2, 2, 1);
	gluCylinder(qobja, 0, amplitude*sqrt(40.0), 10, 200, 200);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(200.0), 10, 200, 200);
	/*	glPushMatrix();
	glTranslatef(j + (amplitude*sqrt(200.0))/10, k, 0);
	glScalef(1.0, 0.5, 1.0);
	gluCylinder(qobja, 0, amplitude*sqrt(200.0), 10, 200, 200);
	glPopMatrix();*/
	glPopMatrix();
}


void draw_cyl_7(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(200.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_8(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(180.0), 10, 200, 200);
	glPopMatrix();
}

//time for a tail decrement
void draw_cyl_9(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(160.0), 10, 200, 200);
	glPopMatrix();
}
void draw_cyl_10(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(140.0), 10, 200, 200);
	glPopMatrix();
}
void draw_cyl_11(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(120.0), 10, 200, 200);
	glPopMatrix();
}
void draw_cyl_12(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(100.0), 10, 200, 200);
	glPopMatrix();
}
void draw_cyl_13(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(80.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_14(float j, float k)
{
	/*glPushMatrix();
	glTranslatef(j, k, 0);
	glTranslatef(60, 0, 0);
	glRotatef(40.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(qobja, amplitude*sqrt(60.0), 0, 150, 200, 200);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(j, k, 0);
	glTranslatef(-60, 0, 0);
	glRotatef(-40.0f, 0.0f, 1.0f, 0.0f);
	gluCylinder(qobja, amplitude*sqrt(60.0), 0, 150, 200, 200);
	glPopMatrix();*/
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(60.0), 10, 200, 200);
	glPopMatrix();
}
void draw_cyl_15(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(40.0), 10, 200, 200);
	glPopMatrix();
}

void draw_cyl_16(float j, float k)
{
	glPushMatrix();
	glTranslatef(j, k, 0);
	glTranslatef(10, 0, 0);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	//glRotatef(20.0f, 0.0f, 0.0f, 1.0f);
	gluCylinder(qobja, 0, amplitude*sqrt(200.0), 100, 200, 200);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(j, k, 0);
	//	glColor3f(0, 0, 0);
	gluCylinder(qobja, 0, amplitude*sqrt(20.0), 100, 200, 200);
	glPopMatrix();
}
void display(void)
{
	step++;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glOrtho(-W_SCREEN / 2, W_SCREEN / 2, -H_SCREEN / 2, H_SCREEN / 2, -100, 100);
	qobja = gluNewQuadric();
	gluQuadricNormals(qobja, GLU_SMOOTH);

	dis1.x = wormcoords.x - i;
	dis1.y = wormcoords.y - i1;
	float m1 = (dis1.y / dis1.x);

	if (step > 0)
	{
		if (sqrt(dis1.x*dis1.x + dis1.y*dis1.y) < speed)
		{
			i = wormcoords.x;
			i1 = wormcoords.y;
		}

		else
		{
			radian1 = atan2(dis1.y, dis1.x);
			i += cos(radian1)*speed;
			i1 += sin(radian1)*speed;
		}
	}
	dis2.x = wormcoords.x - j;
	dis2.y = wormcoords.y - jtwo;
	float m2 = dis2.y / dis2.x;

	if (step > gamma + 10)
	{
		if (sqrt(dis2.x*dis2.x + dis2.y*dis2.y) < speed)
		{
			j = wormcoords.x;
			jtwo = wormcoords.y;
		}
		else
		{
			radian2 = atan2(dis2.y, dis2.x);
			j += cos(radian2)*speed;
			jtwo += sin(radian2)*speed;
		}
	}

	dis3.x = wormcoords.x - k;
	dis3.y = wormcoords.y - k1;
	float m3 = dis3.y / dis3.x;

	if (step > gamma + 20)
	{
		if (sqrt(dis3.x*dis3.x + dis3.y*dis3.y) < speed)
		{
			k = wormcoords.x;
			k1 = wormcoords.y;
		}
		else
		{
			radian3 = atan2(dis3.y, dis3.x);
			k += cos(radian3)*speed;
			k1 += sin(radian3)*speed;
		}
	}

	dis4.x = wormcoords.x - l;
	dis4.y = wormcoords.y - l1;

	if (step > gamma + 30)
	{
		if (sqrt(dis4.x*dis4.x + dis4.y*dis4.y) < speed)
		{
			l = wormcoords.x;
			l1 = wormcoords.y;
		}
		else
		{
			radian4 = atan2(dis4.y, dis4.x);
			l += cos(radian4)*speed;
			l1 += sin(radian4)*speed;
		}
	}

	dis5.x = wormcoords.x - x_5;
	dis5.y = wormcoords.y - y_5;
	float m5 = dis5.y / dis5.x;

	if (step > gamma + 40)
	{
		if (sqrt(dis5.x*dis5.x + dis5.y*dis5.y) < speed)
		{
			x_5 = wormcoords.x;
			y_5 = wormcoords.y;
		}
		else
		{
			radian5 = atan2(dis5.y, dis5.x);
			x_5 += cos(radian5)*speed;
			y_5 += sin(radian5)*speed;
		}
	}

	dis6.x = wormcoords.x - x_6;
	dis6.y = wormcoords.y - y_6;

	if (step > gamma + 50)
	{
		if (sqrt(dis6.x*dis6.x + dis6.y*dis6.y) < speed)
		{
			x_6 = wormcoords.x;
			y_6 = wormcoords.y;
		}
		else
		{
			radian6 = atan2(dis6.y, dis6.x);
			x_6 += cos(radian6)*speed;
			y_6 += sin(radian6)*speed;
		}
	}

	dis7.x = wormcoords.x - x_7;
	dis7.y = wormcoords.y - y_7;

	if (step > gamma + 60)
	{
		if (sqrt(dis7.x*dis7.x + dis7.y*dis7.y) < speed)
		{
			x_7 = wormcoords.x;
			y_7 = wormcoords.y;
		}
		else
		{
			radian7 = atan2(dis7.y, dis7.x);
			x_7 += cos(radian7)*speed;
			y_7 += sin(radian7)*speed;
		}
	}

	dis8.x = wormcoords.x - x_8;
	dis8.y = wormcoords.y - y_8;

	if (step > gamma + 70)
	{
		if (sqrt(dis8.x*dis8.x + dis8.y*dis8.y) < speed)
		{
			x_8 = wormcoords.x;
			y_8 = wormcoords.y;
		}
		else
		{
			radian8 = atan2(dis8.y, dis8.x);
			x_8 += cos(radian8)*speed;
			y_8 += sin(radian8)*speed;
		}
	}

	dis9.x = wormcoords.x - x_9;
	dis9.y = wormcoords.y - y_9;

	if (step > gamma + 80)
	{
		if (sqrt(dis9.x*dis9.x + dis9.y*dis9.y) < speed)
		{
			x_9 = wormcoords.x;
			y_9 = wormcoords.y;
		}
		else
		{
			radian9 = atan2(dis9.y, dis9.x);
			x_9 += cos(radian9)*speed;
			y_9 += sin(radian9)*speed;
		}
	}


	dis10.x = wormcoords.x - x_10;
	dis10.y = wormcoords.y - y_10;

	if (step > gamma + 90)
	{
		if (sqrt(dis10.x*dis10.x + dis10.y*dis10.y) < speed)
		{
			x_10 = wormcoords.x;
			y_10 = wormcoords.y;
		}
		else
		{
			radian10 = atan2(dis10.y, dis10.x);
			x_10 += cos(radian10)*speed;
			y_10 += sin(radian10)*speed;
		}
	}

	dis11.x = wormcoords.x - x_11;
	dis11.y = wormcoords.y - y_11;

	if (step > gamma + 100)
	{
		if (sqrt(dis11.x*dis11.x + dis11.y*dis11.y) < speed)
		{
			x_11 = wormcoords.x;
			y_11 = wormcoords.y;
		}
		else
		{
			radian11 = atan2(dis11.y, dis11.x);
			x_11 += cos(radian11)*speed;
			y_11 += sin(radian11)*speed;
		}
	}

	dis12.x = wormcoords.x - x_12;
	dis12.y = wormcoords.y - y_12;

	if (step > gamma + 110)
	{
		if (sqrt(dis12.x*dis12.x + dis12.y*dis12.y) < speed)
		{
			x_12 = wormcoords.x;
			y_12 = wormcoords.y;
		}
		else
		{
			radian12 = atan2(dis12.y, dis12.x);
			x_12 += cos(radian12)*speed;
			y_12 += sin(radian12)*speed;
		}
	}

	dis13.x = wormcoords.x - x_13;
	dis13.y = wormcoords.y - y_13;

	if (step > gamma + 120)
	{
		if (sqrt(dis13.x*dis13.x + dis13.y*dis13.y) < speed)
		{
			x_13 = wormcoords.x;
			y_13 = wormcoords.y;
		}
		else
		{
			radian13 = atan2(dis13.y, dis13.x);
			x_13 += cos(radian13)*speed;
			y_13 += sin(radian13)*speed;
		}
	}

	dis14.x = wormcoords.x - x_14;
	dis14.y = wormcoords.y - y_14;

	if (step > gamma + 130)
	{
		if (sqrt(dis14.x*dis14.x + dis14.y*dis14.y) < speed)
		{
			x_14 = wormcoords.x;
			y_14 = wormcoords.y;
		}
		else
		{
			radian14 = atan2(dis14.y, dis14.x);
			x_14 += cos(radian14)*speed;
			y_14 += sin(radian14)*speed;
		}

	}

	dis15.x = wormcoords.x - x_15;
	dis15.y = wormcoords.y - y_15;

	if (step > gamma + 140)
	{
		if (sqrt(dis15.x*dis15.x + dis15.y*dis15.y) < speed)
		{
			x_15 = wormcoords.x;
			y_15 = wormcoords.y;
		}
		else
		{
			radian15 = atan2(dis15.y, dis15.x);
			x_15 += cos(radian15)*speed;
			y_15 += sin(radian15)*speed;
		}

	}

	dis16.x = wormcoords.x - x_16;
	dis16.y = wormcoords.y - y_16;

	if (step > gamma + 150)
	{
		if (sqrt(dis16.x*dis16.x + dis16.y*dis16.y) < speed)
		{
			x_16 = wormcoords.x;
			y_16 = wormcoords.y;
		}
		else
		{
			radian16 = atan2(dis16.y, dis16.x);
			x_16 += cos(radian16)*speed;
			y_16 += sin(radian16)*speed;
		}

	}

	if ((i == j && j == k && k == l && l == x_5 && x_5 == x_6 && x_6 == x_7 && x_7 == x_8 && x_8 == x_9 && x_9 == x_10 && x_10 == x_11 && x_11 == x_12 && x_12 == x_13 && x_13 == x_14) && (i1 == jtwo && jtwo == k1 && k1 == l1 && l1 == y_5 && y_5 == y_6 && y_6 == y_7 && y_7 == y_8 && y_9 == y_10 && y_10 == y_11 && y_11 == y_12 && y_12 == y_13 && y_13 == y_14 && y_14 == y_15 && y_15 == y_16))
		step = 0;


	draw_cyl_16(x_16, y_16);
	draw_cyl_15(x_15, y_15);
	draw_cyl_14(x_14, y_14);
	draw_cyl_13(x_13, y_13);
	draw_cyl_12(x_12, y_12);
	draw_cyl_11(x_11, y_11);
	draw_cyl_10(x_10, y_10);
	draw_cyl_9(x_9, y_9);
	draw_cyl_8(x_8, y_8);
	draw_cyl_7(x_7, y_7);
	draw_cyl_6(x_6, y_6);
	draw_cyl_5(x_5, y_5);
	draw_cyl_4(l, l1);
	draw_cyl_3(k, k1);
	draw_cyl_2(j, jtwo);
	draw_cyl_1(i, i1);
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void init(void)
{
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(W_SCREEN, H_SCREEN);
	glutCreateWindow("ORCA WHALE SIMULATION (TO BE) ");
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutReshapeFunc(reshape);

	glutPassiveMotionFunc(passive);
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	init();
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);
	//	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glutMainLoop();
	return(0);
}