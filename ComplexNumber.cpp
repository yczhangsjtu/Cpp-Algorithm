#include <iostream>
#include <iomanip>

using namespace std;

class MyComplex
{
private:
	double x,y;
public:
	MyComplex():x(0),y(0){}
	MyComplex(double a,double b):x(a),y(b){}
	void setx(double xx) {x=xx;}
	void sety(double yy) {y=yy;}
	double getx() {return x;}
	double gety() {return y;}
	MyComplex operator+(MyComplex rh) const
	{
		return MyComplex(x+rh.getx(),y+rh.gety());
	}
	MyComplex operator-(MyComplex rh) const
	{
		return MyComplex(x-rh.getx(),y-rh.gety());
	}
	MyComplex operator*(MyComplex rh) const
	{
		double rx=rh.getx(),ry=rh.gety();
		return MyComplex(x*rx-y*ry,x*ry+y*rx);
	}
	MyComplex operator/(MyComplex rh) const
	{
		double rx=rh.getx(),ry=rh.gety();
		double d = rx*rx+ry*ry;
		return MyComplex((x*rx+y*ry)/d,(-x*ry+y*rx)/d);
	}
	MyComplex operator+=(MyComplex rh)
	{
		x+=rh.getx();
		y+=rh.gety();
		return *this;
	}
	MyComplex operator-=(MyComplex rh)
	{
		x-=rh.getx();
		y-=rh.gety();
		return *this;
	}
	MyComplex operator*=(MyComplex rh)
	{
		double rx=rh.getx(),ry=rh.gety();
		double nx=x*rx-y*ry,ny=x*ry+y*rx;
		x=nx;y=ny;
		return *this;
	}
	MyComplex operator/=(MyComplex rh)
	{
		double rx=rh.getx(),ry=rh.gety();
		double d = rx*rx+ry*ry;
		double nx = (x*rx+y*ry)/d,ny = (-x*ry+y*rx)/d;
		x=nx;y=ny;
		return *this;
	}
};

istream& operator>>(istream& is, MyComplex &z)
{
	double a,b;
	is >> a >> b;
	z.setx(a);
	z.sety(b);
	return is;
}

ostream& operator<<(ostream& os, MyComplex z)
{
	os << fixed << setprecision(2) << z.getx() << ' ' << z.gety();
	return os;
}

int main()
{
	MyComplex z1;
	MyComplex z2;

	cin >> z1 >> z2;

	cout << z1 + z2 <<endl;
	cout << z1 - z2 <<endl;
	cout << z1 * z2 <<endl;
	cout << z1 / z2 <<endl;
	cout << (z1 += z2) <<endl;
	cout << (z1 -= z2) <<endl;
	cout << (z1 *= z2) <<endl;
	cout << (z1 /= z2) <<endl;

	return 0;
}
