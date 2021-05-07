#include"MealTypeList.h"

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

void saveMealType(string& file, list<pair<string, int>>& list)
{
	ofstream fout;
	fout.open(file, ios::out);
	for (auto& m : list)
	{
		fout << m.first << endl;
	}
	fout.close();
}

void loadMealType(string& file, list<pair<string, int>>& list)
{
	ifstream fin;
	fin.open(file, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			;
			list.push_back(pair<string, int>(line, 0));
		}
	}
	else
		cout << file << " was not found, load aborted." << endl;
	fin.close();
}