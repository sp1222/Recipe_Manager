#include "Helpers.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

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

/*
template<class T>
bool doesItemExist(string& str, list<T>& lst)
{
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		if (it->getName() == str)
			return true;
	}
	return false;
}


template<class T>
bool compareNames(const T& first, const T& second)
{
	unsigned  i = 0;
	while ((i < first.getName().length()) && (i < second.getName().length()))
	{
		if (tolower(first.getName()[i]) < tolower(second.getName()[i]))
			return true;
		else if (tolower(first.getName()[i]) > tolower(second.getName()[i]))
			return false;
		i++;
	}
	return (first.getName().length() < second.getName().length());
}
*/