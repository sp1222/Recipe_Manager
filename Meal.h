/*
	Meal.h
	Defines a Meal Class.
*/

#pragma once
#ifndef CATEGORY_H
#define CATEGORY_H

#include <wx/datetime.h>

#include "Recipe.h"
#include "RecipeList.h"

/*
	Meal class for instances of Meal objects in meal planning calendars.
*/
class Meal
{
private:
	std::string name;
	std::string description;
	wxDateTime scheduled;	// consider howto save and load this information..
	int numberOfServings;
	std::list<Recipe>* recipes;
public:
	/*
		Makes two Meal objects comparable using name variable.
		@param m : constant reference to Meal object.
		@return : If object matches this instance of a Meal.
	*/
	bool operator == (const Meal& m) const;

	/*
		Makes two Meal objects comparable using name variable.
		@param m : constant reference to Meal object.
		@return : If object does not match this instance of a Meal.
	*/
	bool operator != (const Meal& m) const;

	/*
		Create an empty Meal object.
	*/
	Meal();

	/*
		Initialize a Meal object with valid parameter values.
		@param name : reference to string to initialize the name of the Meal object.
		@param description : reference to string to initialize the description of the Meal object.
		@param scheduled : reference to wxDateTime object that represents the scheduled date and time of the Meal object.
		@param numberOfServings : reference to int to initialize the number of servings of the Meal object.
		@param recipes : reference to list<Recipe> to initialize the list of recipes of the Meal object.
	*/
	Meal(std::string& name, std::string& description, wxDateTime& scheduled, int numberOfServings, std::list<Recipe>& recipes);

	/*
		Set the name of the Meal object.
		@param name : reference to string to initialize the name of the Meal object.
	*/
	void setName(std::string& name);

	/*
		Set the description of the Meal object.
		@param description : reference to string to initialize the description of the Meal object.
	*/
	void setDescription(std::string& description);

	/*
		Set the scheduled of the Meal object.
		@param scheduled : reference to wxDateTime to initialize the scheduled date and time of the Meal object.
	*/
	void setScheduled(wxDateTime& scheduled);

	/*
		Set the numberOfServings of the Meal object.
		@param numberOfServings : reference to int to initialize the number of servings of the Meal object.
	*/
	void setNumberOfServings(int& numberOfServings);

	/*
		Returns the name of Meal object.
		@return the name of this Meal object.
	*/
	std::string getName() const;

	/*
		Returns the description of Meal object.
		@return the description of this Meal object.
	*/
	std::string getDescription();

	/*
		Returns the wxDateTime object of this Menu object.
		@return wxDateTime object of this Menu object.
	*/
	wxDateTime getScheduled();

	/*
		Returns the number of servings for this Meal object.
		@return numberOfServings;
	*/

	int getNumberOfServings();

	/*
		Add a reference to a Recipe object to list<Recipes> for this Menu object.
		@param name : reference to string of Recipe object's name to add to this Menu object's list<Recipe>*.
		@param lst : list<Recipe> master Recipe list to reference Recipe object from for adding to Menu object's list<Recipes>*
	*/
	void addRecipeToMenu(std::string& name, std::list<Recipe>& lst);

	/*
		Remove a reference to a Recipe object from list<Recipes> for this Menu object.
		@param recipeName : string of name of reference to Recipe object being removed from list<Recipe>* in this Menu object.
	*/
	void removeRecipeFromMenu(std::string& name);

	/*
		Return a reference to a Recipe object from list<Recipe> for this Menu object.
		@param recipeName : string containing name of reference to Recipe object in list<Recipe>* for this Menu object.
		@return reference to Recipe object.
	*/
	Recipe& getRecipeInMeal(std::string& name);
};

#endif