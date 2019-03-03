#include "stdio.h"
#include "stdlib.h"
#include "GL/glut.h"
#include "math.h"

int HEIGHT = 1000;
int WIDTH = 1000;
int mouseState;
float varX1 = 0;
float varY1 = 0;
float varX2 = 0;
float varY2 = 0;
float varX3 = 0;
float varY3 = 0;
float varX4 = 0;
float varY4 = 0;

//scale slider hard-coded values
float centerX1 = 666;
float centerY1 = 136;
float topEndY1 = 148;
float botEndY1 = 124;

//for rotate sliders
float centerX2 = 652;
float centerY2 = 334;
float topEndX2 = 664;
float botEndX2 = 640;

float centerX3 = 706;
float centerY3 = 334;
float topEndX3 = 718;
float botEndX3 = 694;

float centerX4 = 758;
float centerY4 = 334;
float topEndX4 = 771;
float botEndX4 = 745;

//for scale slider, going up/down x axis
float leftEndX = 535;
float rightEndX = 797;

//for rotate sliders, going up/down y axis
float topEndY = 464;
float botEndY = 204;

int UP = 1;
int DOWN = 0;

char buffer[15924]; //hard coded num
size_t size = 15924; //use against counter

void read() {
	FILE *ptr;
	int count = 0;

	//check to see if file is there, if so, read it
	ptr = fopen("block.raw", "r");
	if (ptr == NULL) {
		fprintf(stderr, "\nError opening file\n");
	}

	//until array is full, read each char byte by byte
	while (count < size) {
		fread(buffer, size, 1, ptr);
		count++;
	}

	//close file
	fclose(ptr);
}

void init()
{
	glClearColor(1.0, 1.0, 1.0, 0.0);
}

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(WIDTH / 6, HEIGHT/6, WIDTH / 2, HEIGHT / 2); //object view
	glLoadIdentity();
	gluLookAt(100.0, 50.0, 0.0, 10.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	//scale
	if (varX1 != 0.0) {
		glScalef(varX1, varX1, varX1);
	}
	//rotate
	if (varY2 != 0.0) {
		glRotatef(varX2 * 180, 1.0, 0.0, 0.0);
	}
	if (varY3 != 0.0) {
		glRotatef(varX3 * 180, 0.0, 1.0, 0.0);
	}
	if (varY4 != 0.0) {
		glRotatef(varX4 * 180, 0.0, 0.0, 1.0);
	}
	drawObj();

	
	glMatrixMode(GL_MODELVIEW);
	glViewport(WIDTH / 2, HEIGHT / 3, WIDTH / 3, HEIGHT / 1.5); //sliders
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	drawBarScale();
	drawSliderScale();
	drawBar(-2);
	drawBar(2);
	drawBar(6);
	drawSlider1(-2);
	drawSlider2(2);
	drawSlider3(6);

	
	glPushMatrix();


	glFlush();
	glutPostRedisplay();
}

drawObj() {
	int count = 0;
	int threshhold = 0; //for block

	glPointSize(5);
	glEnable(GL_POINT_SMOOTH); //make circles instead of squares
	glBegin(GL_POINTS);
	glColor3f(0.5, 0.0, 0.4);
	//go through x, y, z dimensions and plot points if the content from array is over threshhold
	for (int z = 0; z < 54; z++) {
		for (int y = 0; y < 9; y++) {
			for (int x = 0; x < 34; x++) {
				if (buffer[count] != 0) {
					glVertex3f(x - (34/2), y - (9/2), z - (54/2)); //centers object
				}
				count++; //keeps track of where you are in array
			}
		}
	}
	glEnd();
	
}

//for the scaling slider
drawBarScale() {
	glBegin(GL_QUADS);
	glColor3f(0.9, 0.5, 0.0);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(10, 7, 1);
	glVertex3f(10, 8, 1);
	glVertex3f(-10, 8, 1);
	glVertex3f(-10, 7, 1);
	glEnd();
}

drawSliderScale() {
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.0, 0.1);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0.5 + varX1, 7, 1);
	glVertex3f(0.5 + varX1, 8, 1);
	glVertex3f(-0.5 + varX1, 8, 1);
	glVertex3f(-0.5 + varX1, 7, 1);
	glEnd();
}

//for the rotate sliders
drawBar(int x) {
	glBegin(GL_QUADS);
	glColor3f(0.9, 0.5, 0.0);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0 + x, 5, 1);
	glVertex3f(2 + x, 5, 1);
	glVertex3f(2 + x, -5, 1);
	glVertex3f(0 + x, -5, 1);
	glEnd();
}

//individual slider piece drawn out
drawSlider1(int x) {
	float tempy = 0.3 + varY2;
	float tempy2 = -0.3 + varY2;
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.0, 0.1);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0 + x, 0.3 + varY2, 1);
	glVertex3f(2 + x, 0.3 + varY2, 1);
	glVertex3f(2 + x, -0.3 + varY2, 1);
	glVertex3f(0 + x, -0.3 + varY2, 1);
	glEnd();

}
drawSlider2(int x) {
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.0, 0.1);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0 + x, 0.3 + varY3, 1);
	glVertex3f(2 + x, 0.3 + varY3, 1);
	glVertex3f(2 + x, -0.3 + varY3, 1);
	glVertex3f(0 + x, -0.3 + varY3, 1);
	glEnd();
}
drawSlider3(int x) {
	glBegin(GL_QUADS);
	glColor3f(0.1, 0.0, 0.1);
	glNormal3f(0.0, 0.0, 1.0);
	glVertex3f(0 + x, 0.3 + varY4, 1);
	glVertex3f(2 + x, 0.3 + varY4, 1);
	glVertex3f(2 + x, -0.3 + varY4, 1);
	glVertex3f(0 + x, -0.3 + varY4, 1);
	glEnd();
}


static void reshape() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 400.0);
	glMatrixMode(GL_MODELVIEW);
}

void mousecb(int button, int state, int x, int y) {
	if (state == GLUT_DOWN && GLUT_LEFT_BUTTON == button)
	{
		//check if mouse clicked within parameters of slider (hard coded values, DON'T CHANGE WINDOW SIZE PLEASE TT-TT)
		if (x >= leftEndX && x <= rightEndX && y >= botEndY1 && y <= topEndY1) { //first slider
			mouseState = DOWN;
			varX1 = (((float)x - centerX1) / 131) * 9.5;
			varY1 = (((float)y - centerY1) / 12) * 9.5;
		}
		else if (x >= botEndX2 && x <= topEndX2 && y >= botEndY && y <= topEndY) { //second slider
			mouseState = DOWN;
			varX2 = ((centerX2 - (float)x) / 12) * 4.7;
			varY2 = ((centerY2 - (float)y) / 130) * 4.7;
		}
		else if (x >= botEndX3 && x <= topEndX3 && y >= botEndY && y <= topEndY) { //third slider
			mouseState = DOWN;
			varX3 = ((centerX3 - (float)x) / 12) * 4.7;
			varY3 = ((centerY3 - (float)y) / 130) * 4.7;
		}
		else if (x >= botEndX4 && x <= topEndX4 && y >= botEndY && y <= topEndY) { //fourth slider
			mouseState = DOWN;
			varX4 = ((centerX4 - (float)x) / 13) * 4.7;
			varY4 = ((centerY4 - (float)y) / 130) * 4.7;
		}
	}
}

//laggy but works
void motioncb(int x, int y) {
	if (x >= leftEndX && x <= rightEndX && y >= botEndY1 && y <= topEndY1) { //first slider
		mouseState = DOWN;
		varX1 = (((float)x - centerX1) / 131) * 9.5;
		varY1 = (((float)y - centerY1) / 12) * 9.5;
	}
	else if (x >= botEndX2 && x <= topEndX2 && y >= botEndY && y <= topEndY) { //second slider
		mouseState = DOWN;
		varX2 = ((centerX2 - (float)x) / 12) * 4.7;
		varY2 = ((centerY2 - (float)y) / 130) * 4.7;
	}
	else if (x >= botEndX3 && x <= topEndX3 && y >= botEndY && y <= topEndY) { //third slider
		mouseState = DOWN;
		varX3 = ((centerX3 - (float)x) / 12) * 4.7;
		varY3 = ((centerY3 - (float)y) / 130) * 4.7;
	}
	else if (x >= botEndX4 && x <= topEndX4 && y >= botEndY && y <= topEndY) { //fourth slider
		mouseState = DOWN;
		varX4 = ((centerX4 - (float)x) / 13) * 4.7;
		varY4 = ((centerY4 - (float)y) / 130) * 4.7;
	}
}

int main(int argc, char **argv)
{
	//read in file
	read();

	//make window and display (from powerpoint slides)
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowPosition(50, 100);
	glutInitWindowSize(WIDTH, HEIGHT);
	glutCreateWindow("title bar");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mousecb);
	glutMotionFunc(motioncb);
	glutMainLoop();

	return 0;
}