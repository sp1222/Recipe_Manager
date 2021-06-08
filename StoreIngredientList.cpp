
#include "StoreIngredientList.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif


// item csv file header for HEB.
// Name						0
// Variant Price			1
// Variant					2
// Variant Pack Size		3
// Variant Alt Price		4	
// Variant Alt UOM			5	
// UOM Price				6
// UOM						7
// Brand					8
// href						9
// Item SKU key				10
// Category Name			11
// Category Key				12
// Parent Category Name		13
// Parent Category Key		14


void addStoreIngredient(string& n, string& st, string& sk, string& d, string& c, string& pc, string& b, float& p, string& u, float& mp, string& mu, string& h, list<StoreIngredient>& lst)
{
	StoreIngredient ingred(n, st, sk, d, c, pc, b, p, u, mp, mu, h);
	lst.push_back(ingred);
}

void loadStoreIngredientList(string& fileName, list<StoreIngredient>& lst)
{
	ifstream fin;
	fin.open(fileName, ios::in);
	if (fin.is_open())
	{
		bool notHeader = false;
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token;
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);
			
			if (notHeader == false)
			{
				notHeader = true;
				continue;
			}

			/*
			* 
			*	BEFORE CONTINUING, IT MAKES SENSE TO HAVE THE DATA COLLECTOR CLEAN THE DATA MORE THOROUGHLY.
			* 
				nm = Name
				st = Store, in this case HEB exclusively
				sk = Item SKU Key
				d = description, which we do not have in file currently
				c = Category Name
				pc = Parent Category Name
				b = Brand
				p = Variant Price
				u = if Variant != "NA" ? Variant : "each"
				h = https://www.heb.com + href
				mu = if UOM != "NA" ? UOM : Variant Alt UOM
				mp = if UOM != "NA" ? UOM Price : Variant Alt Price

			*/
			string nm = row[0], st = fileName, sk = row[10], d = "", c = row[11], pc = row[13], b = row[8], u = row[2], mu = row[7], h = "https://www.heb.com" + row[9];
			float p = stof(row[1]), mp = stof(row[6]);
			if (mu == "NA")
			{
				mu = row[5];
				mp = stof(row[4]);
			}
			if (u == "NA")
				u = "each";
			
			stringToUpperAll(st);
			stringToUpperAll(c);
			stringToUpperAll(pc);
			stringToUpperAll(u);
			stringToUpperAll(mu);
		}
	}
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