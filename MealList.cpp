/*
	MealList.cpp
	Function definitions for MealList.h
*/

#include "MealList.h"

bool addMeal(std::string& name, std::string& description, wxDateTime& scheduled, int& numberOfServings, std::list<Recipe>& mealRecipesLst, std::list<Meal>& lst)
{
	if (!doesNamedItemExist(name, lst))
	{
		Meal meal(name, description, scheduled, numberOfServings, mealRecipesLst);
		// need to insert meal object in list sorted by scheduled date and time.
		return true;
	}
	return false;
}

bool removeMeal(std::string& name, std::list<Meal>& lst)
{
	for (auto& meal : lst)
	{
		if (meal.getName() == name)
		{
			lst.remove(meal);
			return true;
		}
	}
	return false;
}

void saveMealList(std::string& fileName, std::list<Meal>& lst)
{

}

void loadMealList(std::string& fileName, std::list<Meal>& mealLst, std::list<Recipe>& recipeLst)
{

}

