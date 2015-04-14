#ifndef _INT_H
#define _INT_H

#include <vector>
#include <iostream>
#include <cmath>
#include <string>

typedef unsigned char UNIT;
typedef std::vector<int> IntList;
const int Base = 256;

class Int
{
public:
	Int(int value);
	Int(Int value);
	std::string toStrDec();
	std::string toStrHex();

	Int operator+(int rh);
	Int operator+(Int rh);
	Int operator-(int rh);
	Int operator-(Int rh);
	Int operator-();
	Int operator=(Int rh);

	inline bool sign() {return _sign;}
private:
	std::vector<UNIT> _data;
	std::vector<IntList> _decTable;
	std::vector<IntList> _hexTable;
	bool _sign;

private:
	void extendTransformTable(
		std::vector<IntList> &table, int base, int ext);
	inline void negate() {_sign = !_sign}
};

#endif
