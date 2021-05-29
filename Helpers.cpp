#include "Helpers.h"

void stringRemoveCommas(string& str)
{
	string n = "";
	for (auto& s : str)
	{
		if (s != ',')
			n += s;
	}
	str = n;
}

void stringToUpperAll(string& str)
{
	for (auto& s : str)
		s = toupper(s);
}

void float2Decimals(float& flt)
{
	flt = int(flt * 100 / 0.5f);
	flt = float(flt / 100);
}