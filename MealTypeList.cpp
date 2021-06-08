/*
	MealTypeList.cpp
	Function definitions for MealTypeList.h
*/

#include "Helpers.h"
#include "MealTypeList.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Adds a new MealType object to a list< pair<string, int> >.
void addMealType(string& name, list<pair<string, int>>& lst)
{
	stringToUpperAll(name);
	if (!doesMealTypeExist(name, lst))
	{
		pair<string, int> newType(name, 0);
		lst.push_back(newType);
	}
}

/*	CURRENTLY NOT IN USE.  THIS LIST IS "REFRESHED" AT STARTUP WHEN LISTS ARE LOADED.

// Removes named MealType object from list< pair<string, int> >.
void removeMealType(string& name, list<pair<string, int>>& lst)
{
	if (doesMealTypeExist(name, lst))
	{
		for (auto& m : lst)
		{
			if (m.first == name && m.second > 0)
			{
				lst.remove(m);
				break;
			}
		}
	}
}
*/

// Checks if a MealType object exists in list< pair<string, int> > based on its name.
bool doesMealTypeExist(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name)
			return true;
	}
	return false;
}

// Returns how many Recipe objects are using this MealType, pair<string, int>, object.
int getRecipeUsingMealTypeCount(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name)
			return m.second;
	}
	return 0;
}

// Increments a variable that tracks how many Recipe objects are using this MealType, pair<string, int>, object.
void incrementRecipeUsingMealTypeCount(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name)
			m.second++;
	}
}

// Decrements a variable that tracks how many Recipe objects are using this MealType, pair<string, int>, object.
void decrementRecipeUsingMealTypeCount(string& name, list<pair<string, int>>& lst)
{
	for (auto& m : lst)
	{
		if (m.first == name && m.second > 0)
			m.second--;
	}
}