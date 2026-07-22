#include "stdio.h"
#include "glm\glm.hpp"
#include "glut.h"

using namespace glm;

ivec2 windowSize = { 800, 600 };	//ウィンドウの大きさを管理する変数

bool keys[256];  //キーボードの状態を管理する配列  ASCIIコードの数256コだけ用意する　2^8 = 256 = 1バイト = 8ビット

void display() {
	glClear(GL_COLOR_BUFFER_BIT); //GLbitfield mask		//前の絵を消す　じゃないと回転してる部分が白で埋め尽くされる

	glMatrixMode(GL_PROJECTION);//GLenum mode	射影行列（投影変換行列）を操作する ３次元を２次元に変換するための行列
	glLoadIdentity(); //現在の行列を単位行列に初期化　これで前のフレームの射影変換行列の影響を受けないようにする
	gluOrtho2D(		//GLdouble left, GLdouble right, GLdouble bottom, GLdouble top	//左、右、下、上の座標を指定する OrthoとはOrthgraphicの略で、平行投影法のこと
		0, windowSize.x,	//左、右の座標
		windowSize.y, 0	//下、上の座標
	);
	glMatrixMode(GL_MODELVIEW);		//GLenum mode	モデルビュー行列（モデル変換行列）を操作する　物体の位置や向きを変えるための行列
	glLoadIdentity(); //現在の行列を単位行列に初期化　これで前のフレームのモデルビュー変換行列の影響を受けないようにする

	glTranslatef(windowSize.x/2, windowSize.y/2, 0);	//GLfloat x, y, z		//teapotの座標を移動させる

	static float angle;	//回転角度
	if(keys['d']) angle += 1;	//回転角度を増やす
	if(keys['a']) angle -= 1;	//回転角度を減らす
	glRotatef(	//z軸を中心に回転させる    glutWireTeapot(1);に対しての行列
		angle,		//GLfloat angle	１度
		0, 0, 1	//GLfloat x, y, z
	);
	glScalef(256, 256, 1); //GLfloat x, y, z		//大きさを変える
	glutWireTeapot(1); //GLdouble size
	glutSwapBuffers(); //ダブルバッファリングモードのときに使うやつ
	//glFlush(); //これでため込まれたOpenGLの描画命令を実行する
}

void idle() {
	glutPostRedisplay();	//glutPostRedisplay()を呼び出すことで、再描画を要求する
}

void reshape(int width, int height) {		
	//printf("reshape: width: %d, height: %d\n", width, height);
	glViewport(		//ウィンドウの大きさが変わるときに、ビューポートの大きさも変える　つまり絵がウィンドウの大きさに合わせて変わるようにする
		0, 0,			//GLint x, y,
		width, height	//GLsizei width, height
	);
	windowSize = ivec2(width, height);	//ウィンドウの大きさを管理する変数 ivec2のコンストラクタにwidthとheightを渡している
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 0x1b) {	//ESCキーが押されたときに終了する
		exit(0);
	}
	printf("keyboard: \%c\ (%#x)\n", key, key);
	keys[key] = true; //キーが押されたときに、keys配列の該当する要素をtrueにする
}

void keyboardUp(unsigned char key, int x, int y) {
	printf("keyboardUp: \%c\ (%#x)\n", key, key);
	keys[key] = false; //キーが離されたときに、keys配列の該当する要素をfalseにする
}

int main(int argc, char* argv[]){
    glutInit(
        &argc, //int *argcp
        argv); //char **argv
	glutInitDisplayMode(GL_DOUBLE); //unsigned int mode  ダブルバッファリングモードを使うときに書くやつGL_DOUBLE	垂直同期が切られ、FPSが60くらいになる
	glutInitWindowPosition(200, 720); //int x, int y
	glutInitWindowSize(windowSize.x, windowSize.y); //int width, int height
	glutCreateWindow("title"); //const char *title
	glutDisplayFunc(display); //void (GLUTCALLBACK *func)(void)
	glutIdleFunc(idle); //void (GLUTCALLBACK *func)(void)	//なんもしてない時に呼ばれる
	glutReshapeFunc(reshape); //void (GLUTCALLBACK *func)(int width, int height)  //ウィンドウのサイズが変わったときに呼ばれる
	glutKeyboardFunc(keyboard); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)  //キーボードが押されたときに呼ばれる
	glutIgnoreKeyRepeat(GL_TRUE);	//int ignore	//キーを押しっぱなしにしたときに、連続で呼ばれるのを無視する
	glutKeyboardUpFunc(keyboardUp); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)  //キーボードが離されたときに呼ばれる
	glutMainLoop();
    return 0;
}