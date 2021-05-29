/*
	CategoryList.cpp
	Function definitions for CategoryList.h
*/

#include<fstream>
#include<sstream>
#include<vector>

#include "CategoryList.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Adds a new Category object to a list<Category>.
bool addCategory(string& name, list<Category>& lst)
{
	stringRemoveCommas(name);
	stringToUpperAll(name);
	if (!doesNamedCategoryExist(name, lst))
	{
		Category category(name);
		lst.push_back(category);
		return true;
	}
	return false;
}

// Removes named Category object from list<Category>.
// Change to using indices to quickly locate and remove the category from the list.
// now that the lists will now be sorted to match MainListCtrl.
bool removeCategory(string& name, list<Category>& lst)
{
	// check that there are no ingredients utilizing this category object first.
	// and chech that the category being removed is not NONE.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?  No.

	if (lst.size() > 1)
	{
		for (auto& c : lst)
		{
			if (c.getName() == name && c.getName() != "NONE" && c.getIngredientsUsingCategoryCount() == 0)
			{
				lst.remove(c);
				return true;
			}
		}
	}
	return false;
}

// Save existing list<Category> to designated fileName.
// File is CSV format, fileName value must end in ".csv".
void saveCategoryList(string& fileName, list<Category>& lst)
{
	ofstream fout;
	fout.open(fileName, ios::out);
	if (fout.is_open())
	{
		for (auto& c : lst)
			fout << c.getName() << endl;
	}
	fout.close();
}

// Load list<Category> from designated fileName.
// File is CSV format, fileName value must end in ".csv".
void loadCategoryList(string& fileName, list<Category>& lst)
{
	ifstream fin;
	fin.open(fileName, ios::in);
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
			addCategory(row[0], lst);
		}
	}
	fin.close();
}

// Sorts the list<Category> by indicated column.
void sortCategories(int byCol, list<Category>& lst)
{
	switch (byCol)
	{
	case 0:
		lst.sort(compareCategoryNames);
		break;
	case 1:
		lst.sort(compareCategoryIngredientCount);
		break;
	default:
		break;
	}
}

// Comparator by Name for list sorting.
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

// Comparator by Ingredient Count for list sorting.
bool compareCategoryIngredientCount(const Category& first, const Category& second)
{
	return (first.getIngredientsUsingCategoryCount() < second.getIngredientsUsingCategoryCount());
}

// Checks if a Category object exists in list<Category> based on its name.
bool doesNamedCategoryExist(string& name, list<Category>& lst)
{
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		if (it->getName() == name)
			return true;
	}
	return false;
}

// Returns a reference to named Category object in list<Category> if it exists.
// Otherwise returns first Category object in list<Category>.
Category& getCategoryInList(string& name, list<Category>& lst)
{
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?
	for (auto& c : lst)
	{
		if (c.getName() == name)
			return c;
	}
	return lst.front();
}