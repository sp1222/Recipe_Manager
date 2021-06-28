/*
	Meal.h
	Defines a Meal Class.
*/

#pragma once
#ifndef MEAL_H
#define MEAL_H

#include <list>
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
	unsigned short id;
	std::string description;
	wxDateTime scheduled;	// consider howto save and load this information..
	int numberOfServings;
	bool isArchived;
	std::list<Recipe>* recipes;
public:
	/*
		Makes two Meal objects comparable using id variable.
		@param m : constant reference to Meal object.
		@return : If object matches this instance of a Meal.
	*/
	bool operator == (const Meal& m) const;

	/*
		Makes two Meal objects comparable using id variable.
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
	Meal(std::string& name, std::string& description, wxDateTime& scheduled, int& numberOfServings, bool& isArchived, std::list<Recipe>& recipes);

	/*
		Set the name of the Meal object.
		@param name : reference to string to define the name of the Meal object.
	*/
	void setName(std::string& name);

	/*
		Set the ID of the Meal object.
		@param id : int to define the ID of the Meal object.
	*/
	void setID(unsigned short id);

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
		Set the Meal object to archived by default when its date and time is before current date and time.
		Set the Meal object to not archived when copying an old Meal object for a future date.
		@param isArchived = false : boolean stating if this Meal object is to be archived.
	*/
	void setIsArchived(bool isArchived = false);

	/*
		Returns the name of Meal object.
		@return the name of this Meal object.
	*/
	std::string getName() const;

	/*
		Returns the ID of Meal object.
		@return the id of this Meal object.
	*/
	unsigned short getID() const;

	/*
		Returns the description of Meal object.
		@return the description of this Meal object.
	*/
	std::string getDescription();

	/*
		Returns the wxDateTime object of this Meal object.
		@return wxDateTime object of this Meal object.
	*/
	wxDateTime getScheduled() const;

	/*
		Returns the number of servings for this Meal object.
		@return numberOfServings;
	*/

	int getNumberOfServings();

	/*
		Returns if this Meal object is an archived Meal object.
		@return If the Meal object is an archived Meal object.
	*/
	bool isMealArchived();

	/*
		Add a reference to a Recipe object to list<Recipes> for this Meal object.
		@param name : reference to string of Recipe object's name to add to this Meal object's list<Recipe>*.
		@param lst : list<Recipe> master Recipe list to reference Recipe object from for adding to Meal object's list<Recipes>*
	*/
	void addRecipeToMeal(std::string& name, std::list<Recipe>& lst);

	/*
		Remove a reference to a Recipe object from list<Recipes> for this Meal object.
		@param recipeName : string of name of reference to Recipe object being removed from list<Recipe>* in this Meal object.
	*/
	void removeRecipeFromMeal(std::string& name);

	/*
		Return a reference to a Recipe object from list<Recipe> for this Meal object.
		@param recipeName : string containing name of reference to Recipe object in list<Recipe>* for this Meal object.
		@return reference to Recipe object.
	*/
	Recipe& getRecipeInMeal(std::string& name);

	/*
		Sets a reference to list<Recipe>* for this Meal object.
		@param lst : reference to list<Recipe> to reference list<Recipe>* in this Meal object.
	*/
	void getRecipeListInMeal(std::list<Recipe>& lst);

	/*
		Return the number of Recipe objects in list<Recipe>* for this Meal object.
		@return count of Recipe objects in list<Recipe>*.
	*/
	int getRecipeCount() const;
};

#endif