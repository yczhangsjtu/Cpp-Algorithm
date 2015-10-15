#include <GL/freeglut.h>
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <set>

GLfloat sclLeft = -2.0;
GLfloat sclRight = 2.0;
GLfloat sclBottom = -2.0;
GLfloat sclTop = 2.0;

using namespace std;

class Segment;
class Point;
class PSeg;
vector<Segment> segments;
set<PSeg> status;
typedef set<PSeg>::iterator Iter;
set<Point> points;
double ey;

class Point
{
public:
	Point(double x,double y)
	{
		_x = x;
		_y = y;
		_valid = true;
	}
	Point(const Point& p)
	{
		_x = p._x;
		_y = p._y;
		_valid = p._valid;
	}
	Point(bool v)
	{
		_x = 0.0;
		_y = 0.0;
		_valid = v;
	}
	bool isvalid() const {return _valid;}

	bool operator< (const Point& p) const
	{
		if(_y < p._y) return true;
		if(_y == p._y) return _x < p._x;
		return false;
	}
	
	double x() const { return _x; }
	double y() const { return _y; }

private:
	double _x;
	double _y;
	bool _valid;
};

class Segment
{
public:
	Segment(double x1, double y1, double x2, double y2)
	:_p1(x1,y1),_p2(x2,y2)
	{
		if(_p1 < _p2)
		{
		}
		else
		{
			Point tmp = _p1;
			_p1 = _p2;
			_p2 = tmp;
		}
	}

	bool operator<(const Segment& s) const
	{
		double x1 = _p1.x();
		double y1 = _p1.y();
		double x2 = _p2.x();
		double y2 = _p2.y();
		double X1 = s.x1();
		double Y1 = s.y1();
		double X2 = s.x2();
		double Y2 = s.y2();
		double mx = x1;
		double mX = X1;
		if(y1 == y2)
		{
			if(ey != y1) return false;
		}
		else
		{
			double l = (ey-y1)/(y2-y1);
			mx = x1 + l*(x2-x1);
		}
		if(Y1 == Y2)
		{
			if(ey != Y1) return false;
		}
		else
		{
			double l = (ey-Y1)/(Y2-Y1);
			mX = X1 + l*(X2-X1);
		}
		if(mx < mX) return true;
		if(mx > mX) return false;
		if(y1 == y2 || Y1 == Y2) return false;
		mx += (x2-x1)/(y2-y1);
		mX += (X2-X1)/(Y2-Y1);
		if(mx <= mX) return true;
		if(mx > mX) return false;
	}

	Point intersection(const Segment& s) const
	{
		double x1 = _p1.x();
		double y1 = _p1.y();
		double x2 = _p2.x();
		double y2 = _p2.y();
		double X1 = s.x1();
		double Y1 = s.y1();
		double X2 = s.x2();
		double Y2 = s.y2();
		double d = (x2-x1)*(Y2-Y1)-(y2-y1)*(X2-X1);
		if(d == 0) return Point(false);
		double l1 = ((X1-x1)*(Y2-Y1)-(Y1-y1)*(X2-X1))/d;
		double l2 = ((X1-x1)*(y2-y1)-(Y1-y1)*(x2-x1))/d;
		if(l1 < 0 || l1 > 1 || l2 < 0 || l2 > 1) return Point(false);
		return Point(x1+l1*(x2-x1),y1+l1*(y2-y1));
	}

	void setStat(Iter iter) {_stat = iter;}
	Iter stat() const {return _stat;}
	Iter next() const 
	{
		Iter iter = _stat;
		if(iter != status.end())
		{
			iter++;
			return iter;
		}
		return status.end();
	}
	Iter prev() const
	{
		Iter iter = _stat;
		if(iter != status.begin())
		{
			iter --;
			return iter;
		}
		return status.end();
	}

	double x1() const {return _p1.x();}
	double y1() const {return _p1.y();}
	double x2() const {return _p2.x();}
	double y2() const {return _p2.y();}
private:
	Point _p1;
	Point _p2;
	Iter _stat;
};

class PSeg
{
public:
	PSeg(Segment* s)
	{
		_s = s;
	}
	Segment* s() const { return _s; }
	bool operator< (const PSeg& p) const
	{
		return *_s < *p._s;
	}
	bool operator== (const PSeg& p) const
	{
		return _s == p._s;
	}
private:
	Segment* _s;
};

class EventPoint
{
public:
	EventPoint(double x, double y)
	:_p(x,y)
	{ }
	Point p() const {return _p;}
	double x() const {return _p.x();}
	double y() const {return _p.y();}
	void addLowers(PSeg s) {_lowers.push_back(s);}
	void addUppers(PSeg s) {_uppers.push_back(s);}
	void addMiddle(PSeg s) {_middle.push_back(s);}
	int lowerNum() const {return _lowers.size();}
	int upperNum() const {return _uppers.size();}
	int middleNum() const {return _middle.size();}
	PSeg lower(int i) const {assert(i>=0 && i<_lowers.size());return _lowers.at(i);}
	PSeg upper(int i) const {assert(i>=0 && i<_uppers.size());return _uppers.at(i);}
	PSeg middle(int i) const {assert(i>=0 && i<_middle.size());return _middle.at(i);}

	bool operator< (const EventPoint& p) const
	{
		return _p < p._p;
	}
private:
	Point _p;
	vector<PSeg> _lowers;
	vector<PSeg> _uppers;
	vector<PSeg> _middle;
};

double Random(double a, double b)
{
	return rand()/(float)RAND_MAX * (b-a)+a;
}

Segment randSeg()
{
	double l = Random(0.3,0.5);
	double x = Random(sclLeft+l,sclRight-l);
	double y = Random(sclBottom+l,sclTop-l);
	double t = Random(0.0,2*M_PI);
	double x1 = x + l*cos(t);
	double y1 = y + l*sin(t);
	double x2 = x - l*cos(t);
	double y2 = y - l*sin(t);
	return Segment(x1,y1,x2,y2);
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glColor3f(0.0,0.0,0.0);
	glPointSize(5.0);
	glBegin(GL_LINES);
	for(int i = 0 ; i < segments.size(); i++)
	{
		glVertex2f(segments.at(i).x1(),segments.at(i).y1());
		glVertex2f(segments.at(i).x2(),segments.at(i).y2());
	}
	glEnd();
	glColor3f(0.0,1.0,0.0);
	glBegin(GL_LINES);
	for(Iter iter = status.begin(); iter != status.end(); iter++)
	{
		glVertex2f(iter->s()->x1(),iter->s()->y1());
		glVertex2f(iter->s()->x2(),iter->s()->y2());
	}
	glEnd();
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POINTS);
	for(int i = 0 ; i < segments.size(); i++)
	{
		glVertex2f(segments.at(i).x1(),segments.at(i).y1());
		glVertex2f(segments.at(i).x2(),segments.at(i).y2());
	}
	glEnd();
	glColor3f(1.0,0.0,0.0);
	glBegin(GL_POINTS);
	for(set<Point>::iterator iter = points.begin(); iter!=points.end(); iter++)
	{
		glVertex2f(iter->x(),iter->y());
	}
	glEnd();
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_LINES);
	glVertex2f(sclLeft,ey);
	glVertex2f(sclRight,ey);
	glEnd();
	
	glutSwapBuffers();
}

void reshape(int w, int h)
{
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

set<EventPoint> Q;

void findNewEvent(PSeg s1, PSeg s2)
{
	Point p = s1.s()->intersection(*s2.s());
	if(p.isvalid() && p.y() > ey)
	{
		EventPoint ep(p.x(),p.y());
		ep.addMiddle(s1);
		ep.addMiddle(s2);
		Q.insert(ep);
	}
}

void handleEventPoint(EventPoint p)
{
	if(p.middleNum() > 0) points.insert(p.p());
	ey = p.y();
	set<PSeg> lefts, rights;
	for(int i = 0; i < p.lowerNum(); i++)
	{
		Iter iter = p.lower(i).s()->prev();
		if(iter!=status.end()) lefts.insert(*iter);
		iter = p.lower(i).s()->next();
		if(iter!=status.end()) rights.insert(*iter);
		status.erase(p.lower(i).s()->stat());
		p.lower(i).s()->setStat(status.end());
		lefts.erase(p.lower(i));
		rights.erase(p.lower(i));
	}
	for(int i = 0; i < p.middleNum(); i++)
	{
		status.erase(p.middle(i).s()->stat());
		p.middle(i).s()->setStat(status.end());
	}
	for(int i = 0; i < p.upperNum(); i++)
	{
		p.upper(i).s()->setStat(status.insert(p.upper(i)).first);
	}
	for(int i = 0; i < p.middleNum(); i++)
	{
		p.middle(i).s()->setStat(status.insert(p.middle(i)).first);
	}
	if(p.upperNum()+p.middleNum()==0)
	{
		if(!lefts.empty() && !rights.empty())
		{
			findNewEvent(*lefts.begin(),*rights.begin());
		}
	}
	else
	{
		set<PSeg> s;
		for(int i = 0; i < p.upperNum(); i++)
			s.insert(p.upper(i));
		for(int i = 0; i < p.middleNum(); i++)
			s.insert(p.middle(i));
		Iter iter = s.begin();
		Iter l = iter->s()->prev();
		if(l != status.end()) findNewEvent(*iter,*l);
		iter = --s.end();
		Iter r = iter->s()->next();
		if(r != status.end()) findNewEvent(*iter,*r);
	}
}

void keyboard(unsigned char keyCode, int x, int y)
{
	if(keyCode == ' ')
	{
		if(Q.empty()) return;
		set<EventPoint>::iterator iter = Q.begin();
		handleEventPoint(*iter);
		Q.erase(iter);
	}
	glutPostRedisplay();
}

void keyboardUp(unsigned char keyCode, int x, int y)
{
}

void special(int keyCode, int x, int y)
{
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
		std::exit(0);
	}
}

void myinit()
{
	int N = 30;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	Q.clear();
	segments.clear();
	status.clear();
	points.clear();
	for(int i = 0; i < N; i++)
		segments.push_back(randSeg());
	#if 0
	for(int i = 0; i < segments.size(); i++)
		for(int j = i+1; j < segments.size(); j++)
		{
			Point p = segments.at(i).intersection(segments.at(j));
			if(p.isvalid()) points.insert(p);
		}
	#endif
	for(int i = 0; i < segments.size(); i++)
	{
		EventPoint start(segments.at(i).x1(),segments.at(i).y1());
		start.addUppers(PSeg(&segments.at(i)));
		EventPoint end(segments.at(i).x2(),segments.at(i).y2());
		end.addLowers(PSeg(&segments.at(i)));
		Q.insert(start);
		Q.insert(end);
	}
}

void idle()
{
}

int main(int argc, char *argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(1366, 750);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Window");
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
