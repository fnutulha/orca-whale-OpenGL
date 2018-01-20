#include <Windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include "glut.h"
#include <math.h>
GLUquadric *qobja;
#define W_SCREEN 1366
#define H_SCREEN 768
#define TERR_D 75
#define TERR_W 750
#define pi 3.14
int mou_x = 0, mou_y = 0;
float alpha = 0;
float fahad = 0;

//GLfloat ctrlpoints[4][4][3] = {
//   { {-1.5, -1.5, 4.0},
//     {-0.5, -1.5, 2.0},
//     {0.5, -1.5, -1.0},
//     {1.5, -1.5, 2.0}},
//   { {-1.5, -0.5, 1.0},
//     {-0.5, -0.5, 3.0},
//     {0.5, -0.5, 0.0},
//     {1.5, -0.5, -1.0}},
//   { {-1.5, 0.5, 4.0},
//     {-0.5, 0.5, 0.0},
//     {0.5, 0.5, 3.0},
//     {1.5, 0.5, 4.0}},
//   { {-1.5, 1.5, -2.0},
//     {-0.5, 1.5, -2.0},
//     {0.5, 1.5, 0.0},
//     {1.5, 1.5, -1.0}}
//};

GLfloat ctrlpoints[4][4][3] = {
   { {-1.5, -1.5, 4.0},
     {-1.5, -1.5, 4.0},
     {-1.5, -1.5, 4.0},
     {-1.5, -1.5, 4.0}},
   { {-1.5, -0.5, 1.0},
     {-0.5, -0.5, 3.0},
     {0.5, -0.5, 0.0},
     {1.5, -0.5, -1.0}},
   { {-1.5, 0.5, 4.0},
     {-0.5, 0.5, 0.0},
     {0.5, 0.5, 3.0},
     {1.5, 0.5, 4.0}},
   { {-1.5, 1.5, -2.0},
     {-0.5, 1.5, -2.0},
     {0.5, 1.5, 0.0},
     {1.5, 1.5, -1.0}}
};

float cam_xrot = 180, cam_yrot = 180, cam_zrot = 0;
GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_ambient[] = { 0.7, 0.7, 0.7, 1.0 };
GLfloat mat_ambient_color[] = { 0.8, 0.8, 0.2, 1.0 };
GLfloat mat_diffuse[] = { 0.1, 0.5, 0.8, 1.0 };
GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat no_shininess[] = { 0.0 };
GLfloat low_shininess[] = { 5.0 };
GLfloat high_shininess[] = { 100.0 };
GLfloat mat_emission[] = { 0.3, 0.2, 0.2, 0.0 };

// Function Prototypes ////////////////////////////////////
void drawTerrain();
void drawAxes();
//drawing function decs
void draw_frust(float inner, float outer, float height, float m_z);
void cleanup();
void camera();
void pyramid();
void draw_closed_cyl(float a, float b, float c);


/*  Initialize z-buffer, projection matrix, light source,
*  and lighting model.  Do not specify a material property here.
*/
void initLight(void)
{
	GLfloat ambient[] = {0.2, 0.2, 0.2, 1.0};
   GLfloat position[] = {0.0, 0.0, 2.0, 1.0};
   GLfloat mat_diffuse[] = {0.6, 0.6, 0.6, 1.0};
   GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
   GLfloat mat_shininess[] = {50.0};

   glEnable(GL_LIGHTING);
   glEnable(GL_LIGHT0);

   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   glLightfv(GL_LIGHT0, GL_POSITION, position);

   glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
   glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
   glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}


void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glEnable(GL_DEPTH_TEST);
   glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoints[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_AUTO_NORMAL);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
	initLight();
}



///////////////////////////////////////////////////////////
void display(void)
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	camera();
	drawAxes();
	qobja = gluNewQuadric();
	gluQuadricNormals(qobja, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0,0,87);
   glRotatef(180, 0.0, 0.0, 1.0);
   //glRotatef(135,1,1,0);
   glScalef(2,2,2);
   glEvalMesh2(GL_FILL, 0, 20, 0, 20);
   glPopMatrix();
	glPushMatrix();
	float count = 5;
	float a = 5;
	for (float i = 0; i <= 16; i = i + 1)
	{
		draw_frust(a*sqrt(i), a*sqrt((i + 1)), 2, count * 2);
		count++;
		alpha = i + 1;
	}
	
	//a few smooth runs
	for (int j = 0; j < 3; j++)
	{
		draw_frust(a*sqrt(alpha), a*sqrt(alpha), 2, count * 2);
		count++;
	}
	

	float co = count;
	for (float i = 17; i >= 3; i = i - 1)
	{
		draw_frust(a*sqrt(i), a*sqrt(i - 1), 2, co * 2);
		co++;
		fahad = a*sqrt(i - 1);
	}


	draw_frust(7.07, 5, 2, co * 2);
	co++;
	draw_frust(5, 3, 2, co * 2);
	co++;
	draw_frust(3, 1, 2, co * 2);
	//co++;
	//draw_frust(1, 0, 2, co * 2);

		/*glPushMatrix();
		glTranslatef(MOUSE.x,MOUSE.y, 0);
		glTranslatef(0,0,85);
		glRotatef(180,0,0,1);
		glScalef(8, 2, 10);
		pyramid();
		glPopMatrix();*/
		glPushMatrix();

							//fin left 
							glPushMatrix();
							glTranslatef(-25.5, 10, 25);
							glRotatef(100, 1, 0, 0);
							glRotatef(135, 0, 1, 0);
							glRotatef(45, 0, 0, 1);
							glScalef(1,6,1);
							draw_closed_cyl(0, 0 , 0);
							glPopMatrix();


							//fin right 
							glPushMatrix();
							glTranslatef(25.5, 10, 25);
							glRotatef(100, 1, 0, 0);
							glRotatef(-135, 0, 1, 0);
							glRotatef(-45, 0, 0, 1);
							glScalef(1, 6, 1);
							draw_closed_cyl(0, 0, 0);
							glPopMatrix();
								
		glPopMatrix();
	glutSwapBuffers();
}


void draw_frust(float inner, float outer, float height, float m_z)
{
	qobja = gluNewQuadric();
	gluQuadricNormals(qobja, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(0, 0, m_z);

	gluDisk(qobja, 0.0, inner, 200, 20);
	gluCylinder(qobja, inner, outer, height, 200, 200);
	glPopMatrix();
}
void draw_closed_cyl(float a, float b, float c)
{
	qobja = gluNewQuadric();
	gluQuadricNormals(qobja, GLU_SMOOTH);
	glPushMatrix();
	glTranslatef(a, b + 2, c);
	glRotatef(120, 0, 0, 1);
	gluCylinder(qobja, 3.0, 3.0, 2.0, 20, 20);
	gluDisk(qobja, 0, 3.0, 20, 20);
	glTranslatef(0, 0, 2.0);
	gluDisk(qobja, 0, 3.0, 20, 20);
	glPopMatrix();
}



void pyramid()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, -1.0f, -1.0f);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, -1.0f, -1.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f);

	glEnd();

}

void drawTerrain(){
	GLfloat color[] = { 0.2, 0.8, 0.2 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, color);
	glColor3f(0.2, 0.8, 0.2); // this line is not needed when lighting in enabled
	glPushMatrix();
	glTranslatef(-TERR_W / 2, 0.0, -TERR_D / 2);
	glBegin(GL_POLYGON);
	glVertex3f(0, 0, 0);
	glVertex3f(TERR_W, 0, 0);
	glVertex3f(TERR_W, 0, TERR_D);
	glVertex3f(0, 0, TERR_D);
	glVertex3f(0, 0, 0);
	glEnd();
	glPopMatrix();
}
void drawAxes(){
	glColor3d(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(3, 0, 0);
	glEnd();

	glColor3d(0, 1, 0);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 3, 0);
	glEnd();

	glColor3d(0, 0, 1);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 3);
	glEnd();
}

///////////////////////////////////////////////////////////
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(1.5*60.0, (GLfloat)w / (GLfloat)h, 1, 1.5*120.0);
	glMatrixMode(GL_MODELVIEW);
	camera();
}

///////////////////////////////////////////////////////////
void camera(){
	glLoadIdentity();
	glTranslatef(0, 0, -100);
	glRotatef(cam_xrot, 1, 0, 0);
	glRotatef(cam_yrot, 0, 1, 0);
	glRotatef(cam_zrot, 0, 0, 1);
}

///////////////////////////////////////////////////////////
void keyboard(unsigned char key, int x, int y)
{
	// Camera controls - Rotation along principle axis
	switch (key) {

	/*case 'g':
		rotneedle = rotneedle + 0.5;
		if (rotneedle > 360) { rotneedle = rotneedle - 360; }
		break;
	case 'G':
		rotneedle = rotneedle - 0.5;
		if (rotneedle < 360) { rotneedle = rotneedle + 360; }
		break;
	case 'n':
		movec++;
		if (movec>0) movec = 0;
		break;*/
	/*case 'N':
		movec--;
		if (movec<-5) movec = -5;
		break;
	case 'B':
		phi = phi + 1;
		if (phi > 360) { phi = phi - 360; }
		break;*/
	/*case 'b':
		phi = phi - 1;
		if (phi < 360) phi = phi + 360;
		break;
	case 't':
		beta = beta + 1;
		if (beta > 360) { beta = beta - 360; }
		break;
	case 'T':
		beta = beta - 1;
		if (beta < 360) beta = beta + 360;
		break;*/
	/*case 'f':
		alpha = alpha + 5;
		movex = movex + 0.1;
		if (alpha > 360) { alpha = alpha - 360; }
		break;
	case 'F':
		alpha = alpha - 5;
		movex = movex - 0.1;
		if (alpha < 360) alpha = alpha + 360;
		break;
	case 'p':
		base = base + 5;
		break;
	case 'P':
		base = base - 5;
		break;*/
	case 'q':
		cam_xrot += 10;
		if (cam_xrot >360) cam_xrot -= 360;
		break;
	case 'z':
		cam_xrot -= 10;
		if (cam_xrot < -360) cam_xrot += 360;
		break;
	case 'a':
		cam_yrot += 10;
		if (cam_yrot >360) cam_yrot -= 360;
		break;
	case 'd':
		cam_yrot -= 10;
		if (cam_yrot < -360) cam_yrot += 360;
		break;
	case 'w':
		cam_zrot += 10;
		if (cam_zrot >360) cam_zrot -= 360;
		break;
	case 'x':
		cam_zrot -= 10;
		if (cam_zrot < -360) cam_zrot += 360;
		break;
	case 27:
		cleanup();
		exit(0);
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

///////////////////////////////////////////////////////////
void cleanup() // call once when you exit program
{

}

void jerry(int mouse, int state, int xo, int yo)
{

	/*MOUSE.x = xo - W_SCREEN / 2;
	MOUSE.y = yo + H_SCREEN / 2;*/

	/*switch (mouse)
	{
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			mou_x = xo;
			mou_y = yo;
			glutPostRedisplay();
		}
		break;

	}*/
}

void move()
{

	/*DIS.x = MOUSE.x - POS.x;
	DIS.y = MOUSE.y - POS.y;
*/
	/*if ((DIS.x*DIS.x - DIS.y*DIS.y) < 10)
	{
		POS.x = MOUSE.x;
		POS.y = MOUSE.y;
	}
	else
	{
		float radian = atan2(DIS.y, DIS.x);
		POS.x += cos(radian) * 0.1;
		POS.y += cos(radian) * 0.1;
		float rot = radian * 180 / pi;
	}*/

}
void update(int value)
{
	move();
	glutPostRedisplay();
	glutTimerFunc(10, update, 0);

}
///////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(W_SCREEN, H_SCREEN);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(argv[0]);
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(jerry);
	glutTimerFunc(25, update, 0);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}




