/*
	RecipeTypeList.h
	Handles lists of RecipeType, pair<string, int>, functionalities.*/

#pragma once
#ifndef RECIPETYPELIST_H
#define RECIPETYPELIST_H

#include<list>
#include<string>

	/*
		Adds a new RecipeType object to a list< pair<string, int> >.
		@param name : Reference to string, the name of the RecipeType object being added to list< pair<string, int> >.
		@param lst : The list<Category> that the RecipeType pair<string, int> object is being added to.
	*/
void addRecipeType(std::string& name, std::list<std::pair<std::string, int>>& lst);

/*
	Removes named RecipeType object from list< pair<string, int> >.
	CURRENTLY NOT IN USE.  THIS LIST IS "REFRESHED" AT STARTUP WHEN LISTS ARE LOADED.
	@param name : Reference to string, the name of the RecipeType object being removed from list< pair<string, int> >.
	@param lst : The list< pair<string, int> > that the RecipeType object is being removed from.
*/
//void removeRecipeType(string& name, list<pair<string, int>>& lst);

/*
	Checks if a RecipeType object exists in list< pair<string, int> > based on its name.
	@param name : Reference to string, the name of the RecipeType object searched for in list< pair<string, int> >.
	@param lst : The list< pair<string, int> > that the RecipeType object is being removed from.
*/
bool doesRecipeTypeExist(std::string& name, std::list< std::pair<std::string, int> >& lst);

/*
	Returns how many Recipe objects are using this RecipeType, pair<string, int>, object.
	@return : number of Recipe objects using this RecipeType object.
*/
int getRecipeUsingRecipeTypeCount(std::string& name, std::list< std::pair<std::string, int> >& lst);

/*
	Increments a variable that tracks how many Recipe objects are using this RecipeType, pair<string, int>, object.
*/
void incrementRecipeUsingRecipeTypeCount(std::string& name, std::list< std::pair<std::string, int> >& lst);

/*
	Decrements a variable that tracks how many Recipe objects are using this RecipeType, pair<string, int>, object.
*/
void decrementRecipeUsingRecipeTypeCount(std::string& name, std::list< std::pair<std::string, int> >& lst);

#endif // !RecipeTypeLIST_H