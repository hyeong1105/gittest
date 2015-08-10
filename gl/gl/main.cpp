#include "sample.h"
#include <gl\freeglut.h>

DataLoad test_M;

void display()
{
	test_M.renderScence();
}

void main(int argc, char **argv)
{
	test_M.loadData();
	test_M.DataSmoothed();
	test_M.init();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowPosition(600, 600);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Sample");
	glutDisplayFunc(display);
	glutIdleFunc(display);
	glutMainLoop();
}