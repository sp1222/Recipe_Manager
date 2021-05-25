#include "StoreIngredientList.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
void addStoreIngredient(string& n, string& d, string& c, string& pc, string& b, string& st, string& sk, float& p, string& u, float& mp, string& mu, string& h, list<StoreIngredient>& lst)
{
	StoreIngredient ingred(n, d, c, pc, b, st, sk, p, u, mp, mu, h);
	lst.push_back(ingred);
}

void loadStoreIngredientList(string& file, list<StoreIngredient>& lst)
{

}

/*
bool doesStoreIngredientExist(string& st, string& sk, list<StoreIngredient>& lst)
{
	for (auto& l : lst)
	{
		if (l.getStore() == st && l.getSKU() == sk)
			return true;
	}
	return false;
}
*/