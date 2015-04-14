#include "Int.h"

//#define DEBUG

const char *hexString = "0123456789ABCDEF";

Int::Int(int value)
{
	int v = std::abs(value);
	_data = std::vector<UNIT> ();
	while(v)
	{
		_data.push_back(v % 256);
		v /= 256;
	}
	if(_data.empty()) _data.push_back(0);
#ifdef DEBUG
#if 0
	for(int i = 0; i < _data.size(); i++)
		std::cout << (int) _data.at(i) << ' ';
	std::cout << std::endl;
#endif
#endif
	_sign = value >= 0;
	extendTransformTable(_decTable, 10, 10);
	extendTransformTable(_hexTable, 16, 10);
}

Int::Int(Int value)
{
	_data = value.data;
	_decTable = value._decTable;
	_hexTable = value._hexTable;
	_sign = value._sign;
}

void Int::extendTransformTable(
	std::vector<IntList> &table, int base, int ext)
{
	while(table.size() < ext)
	{
		if(table.empty())
		{
			table.push_back(IntList());
			table.at(0).push_back(1);
		}
		else
		{
			table.push_back(table.back());
			for(int k = 0; k < table.back().size(); k++)
				table.back().at(k) *= Base;
			for(int k = 0; k < table.back().size(); k++)
			{
				if(table.back().at(k) >= base)
				{
					if(k == table.back().size() - 1)
						table.back().push_back(0);
					table.back().at(k+1) += table.back().at(k)/base;
					table.back().at(k) %= base;
				}
			}
		}
	}
#ifdef DEBUG
#if 0
	for(int i = 0; i < table.size(); i++)
	{
		for(int j = 0; j < table.at(i).size(); j++)
		{
			std::cout << table.at(i).at(j) << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
#endif
#endif
}

std::string Int::toStrDec()
{
	extendTransformTable(_decTable,10,_data.size());
	IntList result(_decTable.at(_data.size()-1).size());
	for(int i = 0; i < _data.size(); i++)
	{
		for(int j = 0; j < _decTable.at(i).size(); j++)
			result.at(j) += _decTable.at(i).at(j) * _data.at(i);
	}
	for(int i = 0; i < result.size(); i++)
	{
		if(result.at(i) >= 10)
		{
			if(i == result.size() - 1) result.push_back(0);
			result.at(i+1) += result.at(i) / 10;
			result.at(i) %= 10;
		}
	}
	std::string str;
	if(!_sign) str += '-';
	for(int i = 0; i < result.size(); i++)
		str += result.at(result.size() - i - 1) + '0';
	return str;
}

std::string Int::toStrHex()
{
	extendTransformTable(_hexTable,16,_data.size());
	IntList result(_decTable.at(_data.size()-1).size());
	for(int i = 0; i < _data.size(); i++)
	{
		for(int j = 0; j < _decTable.at(i).size(); j++)
			result.at(j) += _decTable.at(i).at(j) * _data.at(i);
	}
	for(int i = 0; i < result.size(); i++)
	{
		if(result.at(i) >= 16)
		{
			if(i == result.size() - 1) result.push_back(0);
			result.at(i+1) += result.at(i) / 16;
			result.at(i) %= 16;
		}
	}
	std::string str;
	if(!_sign) str += '-';
	for(int i = 0; i < result.size(); i++)
		str += hexString[result.at(result.size() - i - 1)];
	return str;
}

Int Int::operator+(int rh)
{
	Int Rh(rh);
	return *this+Rh;
}

Int Int::operator+(Int rh)
{
	if((rh.sign() && _sign) || (!rh.sign() && !_sign))
	{
	}
	else
	{
		if(rh.sign())
			return rh - *this;
		else
			return *this - rh;
	}
	return *this;
}

Int Int::operator-(int rh)
{
	return *this + (-rh);
}

Int Int::operator-(Int rh)
{
	return *this + (-rh);
}

Int Int::operator-()
{
	Int cp(*this);
	cp.negate();
	return cp;
}

Int Int::operator=(Int rh)
{
	_data = value.data;
	_decTable = value._decTable;
	_hexTable = value._hexTable;
	_sign = value._sign;
	return *this;
}
