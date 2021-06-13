/*
	RecipeTypeList.cpp
	Function definitions for RecipeTypeList.h
*/

#include "Helpers.h"
#include "RecipeTypeList.h"

using namespace std;

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Adds a new RecipeType object to a list< pair<string, int> >.
void addRecipeType(string& name, list<pair<string, int>>& lst)
{
	stringToUpperAll(name);
	if (!doesRecipeTypeExist(name, lst))
	{
		pair<string, int> newType(name, 0);
		lst.push_back(newType);
	}
}

// Checks if a RecipeType object exists in list< pair<string, int> > based on its name.
bool doesRecipeTypeExist(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name)
			return true;
	}
	return false;
}

// Returns how many Recipe objects are using this RecipeType, pair<string, int>, object.
int getRecipeUsingRecipeTypeCount(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name)
			return m.second;
	}
	return 0;
}

// Increments a variable that tracks how many Recipe objects are using this RecipeType, pair<string, int>, object.
void incrementRecipeUsingRecipeTypeCount(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name)
			m.second++;
	}
}

// Decrements a variable that tracks how many Recipe objects are using this RecipeType, pair<string, int>, object.
void decrementRecipeUsingRecipeTypeCount(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name && m.second > 0)
		{
			m.second--;
			//			if (m.second <= 0)
			//				lst.remove(m);
			break;
		}
	}
}