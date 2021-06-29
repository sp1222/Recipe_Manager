/*
	MealList.h
	Handles lists of type Meal functionalities.
*/

#include "Meal.h"

bool addMeal(unsigned short id, std::string& name, std::string& description, wxDateTime& scheduled, int& numberOfServings, bool& isArchived, std::list<Recipe>& mealRecipesLst, std::list<Meal>& lst);

//void addMealFromLoad(unsigned short id, std::string& name, std::string& description, wxDateTime& scheduled, int& numberOfServings, bool& isArchived, std::list<Recipe>& mealRecipesLst, std::list<Meal>& lst);

bool removeMeal(unsigned short id, std::list<Meal>& lst);

void moveMeal(unsigned short id, std::list<Meal>& lst);

bool compareSchedule(const Meal& first, const Meal& second);

Meal& getMealInList(unsigned short& id, std::list<Meal>& lst);

unsigned short getHighestID(std::list<Meal>& lst);

void saveMealList(std::string& fileName, std::list<Meal>& lst);

void loadMealList(std::string& fileName, std::list<Meal>& mealLst, std::list<Recipe>& recipeLst);

