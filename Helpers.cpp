#include "Helpers.h"
using namespace std;

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

bool stringIsDigit(string& str)
{
	return all_of(str.begin(), str.end(), ::isdigit);
}

void float2Decimals(float& flt)
{
	flt = int(flt * 100 / 0.5f);
	flt = float(flt / 100);
}

bool isFloat(string& str)
{
	// if string is empty
	if (str.empty())
		return false;

	bool decimalFound = false;
	bool signFound = false;
	for (int i = 0; i < str.length(); i++)
	{
		// if the first value in the string is "+", "-", ".", or digit, mark sign found.
		if (i == 0)
		{
			if (str[i] == '+' || str[i] == '-' || isdigit(str[i]) || str[i] == '.')
				signFound = true;
			if (str[i] == '.')
				decimalFound = true;
		}
		// evaluate every value after.
		else
		{
			// if decimal is not found and str[i] == '.'
			if (str[i] == '.' && decimalFound == false)
				decimalFound = true;	// decimal found
			// else if decimal is found and str[i] == '.'
			else if (str[i] == '.' && decimalFound == true)
				return false;			// not float, multiple decimals
			// else if str[i] != '.' && str[i] != digit
			else if (str[i] != '.' && isdigit(str[i]) == false)
				return false;			// not float, unusual character in string
		}
	}
	return true;
}