#include "glut.h"

void display() {
	glutWireTeapot(1); //GLdouble size
	glFlush(); //これでため込まれたOpenGLの描画命令を実行する
}

int main(int argc, char* argv[]){
    glutInit(
        &argc, //int *argcp
        argv); //char **argv
	glutInitWindowPosition(200, 720); //int x, int y
	glutInitWindowSize(640, 480); //int width, int height
	glutCreateWindow("title"); //const char *title
	glutDisplayFunc(display); //void (GLUTCALLBACK *func)(void)
	glutMainLoop();
    return 0;
}