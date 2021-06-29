/*
	MealList.cpp
	Function definitions for MealList.h
*/

#include<algorithm>
#include<fstream>
#include<iostream>
#include<regex>
#include<sstream>
#include<vector>

#include "MealList.h"

using namespace std;

bool addMeal(unsigned short id, string& name, string& description, wxDateTime& scheduled, int& numberOfServings, bool& isArchived, list<Recipe>& mealRecipesLst, std::list<Meal>& lst)
{
//  duplicate menus should technically be allowed..
	Meal meal(name, description, scheduled, numberOfServings, isArchived, mealRecipesLst);
	meal.setID(id);
	// need to insert meal object in list sorted by scheduled date and time.
	list<Meal>::iterator iter;
	for (iter = lst.begin(); iter != lst.end(); iter++)
	{
		if (!scheduled.IsLaterThan(iter->getScheduled()))
		{
			lst.insert(iter, meal);
			return true;
		}
	}
	lst.push_back(meal);
	return true;
}

/*
void addMealFromLoad(unsigned short id, std::string& name, std::string& description, wxDateTime& scheduled, int& numberOfServings, bool& isArchived, std::list<Recipe>& mealRecipesLst, std::list<Meal>& lst)
{

}
/*/

bool removeMeal(unsigned short id, list<Meal>& lst)
{
	for (auto& meal : lst)
	{
		if (meal.getID() == id)
		{
			lst.remove(meal);
			return true;
		}
	}
	return false;
}

void moveMeal(unsigned short id, std::list<Meal>& lst)
{
	lst.sort(compareSchedule);
}

bool compareSchedule(const Meal& first, const Meal& second)
{
	return first.getScheduled().IsEarlierThan(second.getScheduled());
}

Meal& getMealInList(unsigned short& id, list<Meal>& lst)
{
	for (auto& m : lst)
	{
		if (m.getID() == id)
			return m;
	}
	return lst.front();
}

unsigned short getHighestID(list<Meal>& lst)
{
	unsigned short highest = 0;
	for (auto& m : lst)
	{
		if (m.getID() > highest)
			highest = m.getID();
	}
	return highest;
}

void saveMealList(string& fileName, list<Meal>& lst)
{
	ofstream fout;
	fout.open(fileName, ios::out);
	if (fout.is_open())
	{
		for (auto& m : lst)
		{
			wxDateTime sched = m.getScheduled();
			string ds = m.getDescription();
			regex newlines_re("\n+");
			string desc = regex_replace(ds, newlines_re, "`");

			// note, need to add one to month when saving. 
			// I am assuming that numerically months are represented in terms of indices (0 to 11 instead of 1 to 12)
//			fout << m.getName() << "," << desc << "," << m.getNumberOfServings() << "," << m.isMealArchived() << "," << sched.GetYear() << ","
//				<< sched.GetMonth() + 1 << "," << sched.GetDay() << "," << sched.GetHour() << "," << sched.GetMinute() << "," << string(sched.FormatTime()) << ",";
			fout << m.getID() << ',' << m.getName() << "," << desc << "," << m.getNumberOfServings() << "," << m.isMealArchived() << "," << string(sched.FormatISODate()) << "," << string(sched.FormatISOTime()) << ",";

			list<Recipe> recs;
//			m.getRecipeListInMeal(recs);
			for (auto& rec : recs)
			{
				fout << rec.getName() << ",";
			}

			// indicates the end of a meal being outputted.
			fout << endl;
		}
	}
	fout.close();
}

void loadMealList(string& fileName, list<Meal>& mealLst, list<Recipe>& recipeLst)
{
	// during the loading process, mark older menus as archived.
	// archived menus cannot be edited, but they can be viewed and copied for new menus.

	ifstream fin;
	fin.open(fileName, ios::in);

	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token = "";
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);

			string name = row[1], ds = row[2], i = row[4], dt = row[5], tm = row[6];			
			unsigned short id = (unsigned short)strtoul(row[0].c_str(), NULL, 0);			
			int noS = (int)strtoul(row[3].c_str(), NULL, 0);
			bool ia = (bool)stoi(i);
			wxString wxdt = wxString(row[5]);
			wxString wxtm = wxString(row[6]);
			row.erase(row.begin(), row.begin() + 7);
			regex newlines_re("`");
			string desc = regex_replace(ds, newlines_re, "\n");

			wxDateTime sch;

			sch.ParseDate(wxdt);
			sch.ParseTime(wxtm);

			/*
			// parse dt and tm, then set Y, M, D, H, M, S

			stringstream sdt(dt);
			string val = "";
			vector<string> dttm;
			while (getline(sdt, val, '/'))
				dttm.push_back(val);

			sch.Set((unsigned)stoi(dttm[1]), static_cast<wxDateTime::Month>(stoi(dttm[0]) - 1), stoi(dttm[2]));

//			sch.SetMonth(static_cast<wxDateTime::Month>(stoi(dttm[0]) - 1));
//			sch.SetDay(stoi(dttm[1]));
//			sch.SetYear(stoi(dttm[2]));

//			dttm.clear();

			stringstream stm(tm);
			val = "";
			while (getline(stm, val, ':'))
				dttm.push_back(val);

//			sch.SetHour(stoi(dttm[0]));
//			sch.SetMinute(stoi(dttm[1]));
//			sch.SetSecond(stoi(dttm[2]));

//			sch.Set((unsigned int)stoi(dttm[1]), static_cast<wxDateTime::Month>(stoi(dttm[0]) - 1), stoi(dttm[2]));
*/

			// get references to recipes in list<Recipe> for this meal based on recipe names.
			list<Recipe> reclst;
			while (row.size() > 0 && row[0] != "")
			{
				reclst.push_back(getRecipeInList(row[0], recipeLst));
				row.erase(row.begin());
			}

			Meal m(name, desc, sch, noS, ia, reclst);
			m.setID(id);

			mealLst.push_back(m);
		}
	}

	fin.close();
}

