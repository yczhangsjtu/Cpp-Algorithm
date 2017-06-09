/*
 * This program is designed to assist playing games involved with 2.5d grid
 * mazes.
 */
#include <GL/freeglut.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cassert>
#include <png.h>


char ifname[256] = "";
char ofname[256] = "map";
char gfname[256] = "map.png";

const int MAP_WIDTH = 100;
const int MAP_HEIGHT = 100;

int ww,hh;

GLfloat sclLeft = 0;
GLfloat sclRight = MAP_WIDTH;
GLfloat sclBottom = 0;
GLfloat sclTop = MAP_HEIGHT;

bool readonly = false;

char map[MAP_HEIGHT][MAP_WIDTH+1];
int sx = MAP_WIDTH/2, sy = MAP_WIDTH/2;
int px = MAP_WIDTH/2, py = MAP_WIDTH/2, pd = 0;

void drawSquare(int X1,int Y1,int X2,int Y2,int R,int G,int B)
{
	glColor3f(R/255.0,G/255.0,B/255.0);
	glBegin(GL_QUADS);
		glVertex2f(X1,Y1);
		glVertex2f(X1,Y2);
		glVertex2f(X2,Y2);
		glVertex2f(X2,Y1);
	glEnd();
}

void drawGrid(int x, int y, int R, int G, int B)
{
	drawSquare(x,y,x+1,y+1,R,G,B);
}

void drawWall(int x, int y)
{
	drawGrid(x,y,22,22,55);
}

void drawGround(int x, int y)
{
	drawGrid(x,y,100,100,255);
}

void drawMark(int x, int y)
{
	glColor3f(1.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(x+1,y+1);
		glVertex2f(x+1,y);
		glVertex2f(x,y+1);
	glEnd();
}

void drawPeople(int x, int y)
{
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
		glVertex2f(x,y);
		glVertex2f(x+0.5,y+0.5);
		glVertex2f(x+1,y);
		glVertex2f(x+0.5,y+0.5);
		glVertex2f(x,y+0.5);
		glVertex2f(x+1,y+0.5);
		glVertex2f(x+0.5,y+0.5);
		glVertex2f(x+0.5,y+1);
	glEnd();
}

void drawDownStair(int x, int y)
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
		glVertex2f(x,y+1);
		glVertex2f(x+1,y+1);
		glVertex2f(x+1,y+0.66);
		glVertex2f(x,y+0.66);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(x+0.3,y+0.66);
		glVertex2f(x+0.6,y+0.66);
		glVertex2f(x+0.6,y);
		glVertex2f(x+0.3,y);
	glEnd();
}

void drawUpStair(int x, int y)
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_QUADS);
		glVertex2f(x+0.3,y+1);
		glVertex2f(x+0.6,y+1);
		glVertex2f(x+0.6,y+0.33);
		glVertex2f(x+0.3,y+0.33);
	glEnd();
	glBegin(GL_QUADS);
		glVertex2f(x,y+0.33);
		glVertex2f(x+1,y+0.33);
		glVertex2f(x+1,y);
		glVertex2f(x,y);
	glEnd();
}

void drawDoor(int x, int y)
{
	drawGrid(x,y,128,0,0);
}

void drawGrid(int x, int y, char c)
{
	if(c == '#') drawWall(x,y);
	else if(c == '.') drawGround(x,y);
	else if(c == 'x') {drawWall(x,y);drawMark(x,y);}
	else if(c == '|') {drawGround(x,y);drawPeople(x,y);}
	else if(c == 'd') {drawGround(x,y);drawDownStair(x,y);}
	else if(c == 'u') {drawGround(x,y);drawUpStair(x,y);}
	else if(c == 'm') {drawDoor(x,y);}
}

void drawPointer(int x, int y, int d)
{
	double x0,y0,x1,y1,x2,y2;
	switch(d)
	{
	case 0: x0 = x, y0 = y, x1 = x+1, y1 = y, x2 = x+0.5, y2 = y+1; break;
	case 1: x0 = x+1, y0 = y+1, x1 = x+1, y1 = y, x2 = x, y2 = y+0.5; break;
	case 2: x0 = x, y0 = y+1, x1 = x+1, y1 = y+1, x2 = x+0.5, y2 = y; break;
	case 3: x0 = x, y0 = y+1, x1 = x, y1 = y, x2 = x+1, y2 = y+0.5; break;
	}
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_LINE_LOOP);
		glVertex2f(x0,y0);
		glVertex2f(x1,y1);
		glVertex2f(x2,y2);
	glEnd();
}

void drawStart()
{
	drawGrid(sx,sy,255,0,0);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	for(int x = 0; x < MAP_WIDTH; x++)
		for(int y = 0; y < MAP_HEIGHT; y++)
			drawGrid(x,y,map[y][x]);

	drawStart();
	drawPointer(px,py,pd);
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
	ww = w;
	hh = h;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (w <= h)
		gluOrtho2D(sclLeft, sclRight, sclBottom * (GLfloat) h / (GLfloat) w,
			sclTop * (GLfloat) h / (GLfloat) w);
	else
		gluOrtho2D(sclLeft * (GLfloat) w / (GLfloat) h,
			sclRight * (GLfloat) w / (GLfloat) h, sclBottom, sclTop);

	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);
}

void turnleft()
{
	pd = (pd+1)%4;
}

void turnright()
{
	pd = (pd+3)%4;
}

void moveback();
void moveforward()
{
	px+=(pd%2)*((pd/2)*2-1);py+=(1-pd%2)*(1-(pd/2)*2);
	if(px < 0) px = 0;
	if(py < 0) py = 0;
	if(px >= MAP_WIDTH) px = MAP_WIDTH-1;
	if(py >= MAP_HEIGHT) py = MAP_HEIGHT-1;
	if(readonly)
	{
		if(map[py][px]!='.' && map[py][px]!='m') moveback();
		if(map[py][px]=='m') moveforward();
	}
}

void moveback()
{
	px+=(pd%2)*(1-(pd/2)*2);py+=(1-pd%2)*((pd/2)*2-1);
	if(px < 0) px = 0;
	if(py < 0) py = 0;
	if(px >= MAP_WIDTH) px = MAP_WIDTH-1;
	if(py >= MAP_HEIGHT) py = MAP_HEIGHT-1;
	if(readonly)
	{
		if(map[py][px]!='.' && map[py][px]!='m') moveforward();
		if(map[py][px]=='m') moveback();
	}
}

void printmap(FILE *fp)
{
	for(int y = MAP_HEIGHT-1; y >= 0; y--)
		fprintf(fp,"%s\n",map[y]);
}

void savefile()
{
	FILE *fp = fopen(ofname,"w");
	if(!fp) fprintf(stderr,"Failed to write to %s!\n",ofname);
	printmap(fp);
	fclose(fp);
}

void saveimage()
{
	GLbyte *data = new GLbyte[3*ww*hh];
	glReadPixels(0, 0, ww, hh, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);
	png_bytep* row_pointers = new png_bytep[hh];
	for(int y = hh-1; y >= 0; y--)
	{
		row_pointers[y] = new png_byte[3*ww];
		for(int x = 0; x < ww; x++)
		{
			row_pointers[y][3*x+2] = data[3*(hh-1-y)*ww+3*x];
			row_pointers[y][3*x+1] = data[3*(hh-1-y)*ww+3*x+1];
			row_pointers[y][3*x] = data[3*(hh-1-y)*ww+3*x+2];
		}
	}
	FILE *fp = fopen(gfname,"wb");
	if(!fp) {delete []data;fprintf(stderr,"Failed to open %s!\n",gfname);return;}
	png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if(!png_ptr) {delete []data;fprintf(stderr,"Failed to create png struct!\n");return;}
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if(!info_ptr) {delete []data;fprintf(stderr,"Failed to create png info struct!\n");return;}
	if (setjmp(png_jmpbuf(png_ptr))) {delete []data;fprintf(stderr,"Failed to init io!\n");return;}
	png_init_io(png_ptr, fp);
	if (setjmp(png_jmpbuf(png_ptr))) {delete []data;fprintf(stderr,"Failed writing header!\n");return;}
	png_set_IHDR(png_ptr, info_ptr, ww, hh,
				 8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
				 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
	png_write_info(png_ptr, info_ptr);
	if (setjmp(png_jmpbuf(png_ptr))) {delete []data;fprintf(stderr,"Failed writing bytes!\n");return;}
	png_write_image(png_ptr, row_pointers);
	if (setjmp(png_jmpbuf(png_ptr))) {delete []data;fprintf(stderr,"Failed during end of write!\n");return;}
	png_write_end(png_ptr, NULL);
	for(int y = 0; y < hh; y++)
		delete []row_pointers[y];
	delete []row_pointers;
	delete []data;
}

void keyboard(unsigned char keyCode, int x, int y)
{
	if(!readonly)
	{
		if(keyCode == 'p') saveimage();
		else if(keyCode == 'x') {moveforward();map[py][px]='x';moveback();}
		else if(keyCode == 'r') {moveforward();map[py][px]='|';moveback();}
		else if(keyCode == 't') {moveforward();map[py][px]='d';moveback();}
		else if(keyCode == 'u') {moveforward();map[py][px]='u';moveback();}
		else if(keyCode == 'b') {turnleft();moveforward();map[py][px]='.';moveback();moveback();map[py][px]='.';moveforward();turnright();}
		else if(keyCode == 'j') {turnleft();moveforward();map[py][px]='.';moveback();turnright();}
		else if(keyCode == 'l') {turnright();moveforward();map[py][px]='.';moveback();turnleft();}
		else if(keyCode == 'm') {moveforward();map[py][px]='m';moveforward();}
		else if(keyCode == 'e') {sx=px;sy=py;}
		else if(keyCode == 'f') savefile();
	}
	if(keyCode == 'a') turnleft();
	else if(keyCode == 'q') exit(0);
	else if(keyCode == 'd') turnright();
	else if(keyCode == 'w') moveforward();
	else if(keyCode == 's') moveback();
	glutPostRedisplay();
}

void keyboardUp(unsigned char keyCode, int x, int y)
{
}

void special(int keyCode, int x, int y)
{
	if(keyCode == GLUT_KEY_LEFT) turnleft();
	else if(keyCode == GLUT_KEY_RIGHT) turnright();
	else if(keyCode == GLUT_KEY_UP) {map[py][px]='.';moveforward();map[py][px]='.';}
	else if(keyCode == GLUT_KEY_DOWN) {map[py][px]='.';moveback();map[py][px]='.';}
	glutPostRedisplay();
}

void specialUp(int keyCode, int x, int y)
{
}

void mouse(int btn, int state, int x, int y)
{
}

void menu(int id)
{
	switch(id)
	{
	case 0:
		exit(0);
	}
}

void myinit()
{
	glClearColor(1.0, 1.0, 1.0, 1.0);
}

void idle()
{
}

void processCmdArgs(int argc, char *argv[])
{
	int ch;
	while((ch=getopt(argc,argv,"i:o:g:r"))!=-1)
	{
		switch(ch)
		{
		case 'i': strncpy(ifname,optarg,255); break;
		case 'o': strncpy(ofname,optarg,255); break;
		case 'g': strncpy(gfname,optarg,255); break;
		case 'r': readonly=true; break;
		}
	}
}

void readfile()
{
	FILE *f = fopen(ifname,"r");
	if(!f)
	{
		for(int y = 0; y < MAP_HEIGHT; y++)
		{
			for(int x = 0; x < MAP_WIDTH; x++)
				map[y][x] = '#';
			map[y][MAP_WIDTH] = '\0';
		}
	}
	else
	{
		for(int y = MAP_HEIGHT-1; y >= 0; y--)
		{
			int r = fscanf(f,"%s",map[y]);
		}
		fclose(f);
	}
}

int main(int argc, char *argv[])
{
	processCmdArgs(argc,argv);
	readfile();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Map Drawer");
	myinit();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(special);
	glutSpecialUpFunc(specialUp);
	glutMouseFunc(mouse);
	glutCreateMenu(menu);
	glutAddMenuEntry("Quit", 0);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutIdleFunc(idle);
	glutMainLoop();
}
