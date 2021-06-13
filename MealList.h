/*
	MealList.h
	Handles lists of type Meal functionalities.
*/

#include "Meal.h"

bool addMeal(std::string& name, std::string& description, wxDateTime& scheduled, int& numberOfServings, std::list<Recipe>& mealRecipesLst, std::list<Meal>& lst);

bool removeMeal(std::string& name, std::list<Meal>& lst);

void saveMealList(std::string& fileName, std::list<Meal>& lst);

void loadMealList(std::string& fileName, std::list<Meal>& mealLst, std::list<Recipe>& recipeLst);

