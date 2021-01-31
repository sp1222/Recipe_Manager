#include"MealType.h"

void addMealType(string& type, list<pair<string, int>>& list)
{
	for (auto& t : type) t = toupper(t);
	if (!doesMealTypeExist(type, list))
	{
		pair<string, int> newType(type, 0);
		list.push_back(newType);
	}
}

void removeMealType(string& type, list<pair<string, int>>& list)
{
	for (auto& t : type) t = toupper(t);
	if (doesMealTypeExist(type, list))
	{
		for (auto& m : list)
		{
			if (m.first == type && m.second > 0)
			{
				list.remove(m);
				break;
			}
		}
	}
}

bool doesMealTypeExist(string& type, list<pair<string, int>>& list)
{
	for (auto& t : type) t = toupper(t);
	for (auto& m : list)
	{
		if (m.first == type)
			return true;
	}
	return false;
}

int getRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list)
{
	for (auto& t : type) t = toupper(t);
	for (auto& m : list)
	{
		if (m.first == type)
			return m.second;
	}
	return 0;
}

void incrementRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list)
{
	for (auto& m : list)
	{
		if (m.first == type)
			m.second++;
	}
}

void decrementRecipeUsingMealTypeCount(string& type, list<pair<string, int>>& list)
{
	for (auto& m : list)
	{
		if (m.first == type && m.second > 0)
			m.second--;
	}
}

void saveMealType(list<pair<string, int>>& list)
{

}

void loadMealType(list<pair<string, int>>& list)
{

}