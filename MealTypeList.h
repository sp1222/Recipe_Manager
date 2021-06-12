/*
	MealTypeList.h
	Handles lists of MealTypes, pair<string, int>, functionalities.*/

#pragma once
#ifndef MEALTYPELIST_H
#define MEALTYPELIST_H

#include<list>
#include<string>

/*
	Adds a new MealType object to a list< pair<string, int> >.
	@param name : Reference to string, the name of the MealType object being added to list< pair<string, int> >.
	@param lst : The list<Category> that the Category object is being added to.
*/
void addMealType(std::string& name, std::list<std::pair<std::string, int>>& lst);

/*
	Removes named MealType object from list< pair<string, int> >.
	CURRENTLY NOT IN USE.  THIS LIST IS "REFRESHED" AT STARTUP WHEN LISTS ARE LOADED.
	@param name : Reference to string, the name of the MealType object being removed from list< pair<string, int> >.
	@param lst : The list< pair<string, int> > that the MealType object is being removed from.
*/
//void removeMealType(string& name, list<pair<string, int>>& lst);

/*
	Checks if a MealType object exists in list< pair<string, int> > based on its name.
	@param name : Reference to string, the name of the MealType object searched for in list< pair<string, int> >.
	@param lst : The list< pair<string, int> > that the MealType object is being removed from.
*/
bool doesMealTypeExist(std::string& name, std::list< std::pair<std::string, int> >& lst);

/*
	Returns how many Recipe objects are using this MealType, pair<string, int>, object.
	@return : number of Recipe objects using this MealType object.
*/
int getRecipeUsingMealTypeCount(std::string& name, std::list< std::pair<std::string, int> >& lst);

/*
	Increments a variable that tracks how many Recipe objects are using this MealType, pair<string, int>, object.
*/
void incrementRecipeUsingMealTypeCount(std::string& name, std::list< std::pair<std::string, int> >& lst);

/*
	Decrements a variable that tracks how many Recipe objects are using this MealType, pair<string, int>, object.
*/
void decrementRecipeUsingMealTypeCount(std::string& name, std::list< std::pair<std::string, int> >& lst);

#endif // !MEALTYPELIST_H