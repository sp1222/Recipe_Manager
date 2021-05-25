#include "CategoryList.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

bool addCategory(string& str, list<Category>& lst)
{
	stringRemoveCommas(str);
	stringToUpperAll(str);
	if (!doesCategoryExist(str, lst))
	{
		Category category(str);
		lst.push_back(category);
		return true;
	}
	return false;
}

// FOR LOADING, IS THIS NECESSARY?
void addCategory(string& str, int& ct, list<Category>& list)
{
	stringRemoveCommas(str);
	stringToUpperAll(str);
	if (!doesCategoryExist(str, list))
	{
		Category category(str);
		list.push_back(category);
	}
}

// Change to using indices to quickly locate and remove the category from the list.
// now that the lists will now be sorted to match MainListCtrl.
bool removeCategory(string& category, list<Category>& list)
{
	// check that there are no ingredients utilizing this category object first.
	// and chech that the category being removed is not NONE.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?  No.

	if (list.size() > 1)
	{
		for (auto& c : list)
		{
			if (c.getName() == category && c.getName() != "NONE" && c.getIngredientsUsingCategoryCount() == 0)
			{
				list.remove(c);
				return true;
			}
		}
	}
	return false;
}

bool doesCategoryExist(string& category, list<Category>& list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		if (it->getName() == category)
			return true;
	}
	return false;
}

void saveCategoryList(string& categoryListFile, list<Category>& list)
{
	ofstream fout;
	fout.open(categoryListFile, ios::out);
	for (auto& c : list)
	{
		fout << c.getName() << endl;
	}
	fout.close();
}

void loadCategoryList(string& categoryListFile, list<Category>& list)
{
	ifstream fin;
	fin.open(categoryListFile, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token;
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);
			addCategory(row[0], list);
		}
	}
	else
		cout << categoryListFile << " was not found, load aborted." << endl;
	fin.close();
}

void sortCategories(int byCol, list<Category>& list)
{
	switch (byCol)
	{
	case 0:
		list.sort(compareCategoryNames);
		break;
	case 1:
		list.sort(compareCategoryIngredientCount);
		break;
	default:
		break;
	}
}

bool compareCategoryNames(const Category& first, const Category& second)
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

bool compareCategoryIngredientCount(const Category& first, const Category& second)
{
	return (first.getIngredientsUsingCategoryCount() < second.getIngredientsUsingCategoryCount());
}

Category& getCategoryInList(string& cat, list<Category>& list)
{
	// decrement the current category's ingredientsUsingCategoryCount value that the ingredient is categorized as.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?
	for (auto& c : list)
	{
		if (c.getName() == cat)
			return c;
	}
	return list.front();
}