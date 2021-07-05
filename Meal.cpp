/*
	Meal.cpp
	Function definitions for Meal.h
*/

#include "Meal.h"

using namespace std;

/*
	Makes two Meal objects comparable using id variable.
*/
bool Meal::operator == (const Meal& m) const
{
	return id == m.getID();
}

/*
	Makes two Meal objects comparable using id variable.
*/
bool Meal::operator != (const Meal& m) const
{
	return !operator==(m);
}

/*
	Create an empty Meal object.
*/
Meal::Meal()
{
	name = "";
	id = -1;
	description = "";
	scheduled = wxDateTime::Today();	// consider means to default to the date currently highlighted in calendar.
	numberOfServings = 0;
	isArchived = false;
}

/*
	Initialize a Meal object with valid parameter values.
*/
Meal::Meal(string& name, string& description, wxDateTime& scheduled, int& numberOfServings, bool& isArchived, list<Recipe*>& recipes)
{
	this->name = name;
	this->description = description;
	this->scheduled = scheduled;
	this->numberOfServings = numberOfServings;
	this->isArchived = isArchived;
	this->recipes = recipes;
//	for (auto& r : recipes)
//		this->recipes->push_back(r);
}

/*
	Set the name of the Meal object.
*/
void Meal::setName(string& name)
{
	stringRemoveCommas(name);
	this->name = name;
}

/*
	Set the ID of the Meal object.
*/
void Meal::setID(unsigned short id)
{
	this->id = id;
}

/*
	Set the description of the Meal object.
*/
void Meal::setDescription(string& description)
{
	stringRemoveCommas(description);
	this->description = description;
}

/*
	Set the scheduled of the Meal object.
*/
void Meal::setScheduled(wxDateTime& scheduled)
{
	this->scheduled = scheduled;
}

/*
	Set the numberOfServings of the Meal object.
*/
void Meal::setNumberOfServings(int& numberOfServings)
{
	this->numberOfServings = numberOfServings;
}

/*
	Set the Meal object to archived by default when its date and time is before current date and time.
	Set the Meal object to not archived when copying an old Meal object for a future date.
*/
void Meal::setIsArchived(bool isArchived)
{
	this->isArchived = isArchived;
}

/*
	Returns the name of Meal object.
*/
string Meal::getName() const
{
	return name;
}

/*
	Returns the ID of Meal object.
*/
unsigned short Meal::getID() const
{
	return id;
}

/*
	Returns the description of Meal object.
*/
string Meal::getDescription()
{
	return description;
}

/*
	Returns the wxDateTime object of this Menu object.
*/
wxDateTime Meal::getScheduled() const
{
	return scheduled;
}

/*
	Returns the number of servings for this Meal object.
*/
int Meal::getNumberOfServings()
{
	return numberOfServings;
}

/*
	Returns if this Meal object is an archived Meal object.
*/
bool Meal::isMealArchived()
{
	return isArchived;
}

/*
	Add a reference to a Recipe object to list<Recipes>* for this Menu object.
*/
void Meal::addRecipeToMeal(string& name, list<Recipe>& lst)
{
	recipes.push_back(&getRecipeInList(name, lst));
}

/*
	Remove a reference to a Recipe object from list<Recipes>* for this Menu object.
*/
void Meal::removeRecipeFromMeal(string& name)
{
	for (auto& r : recipes)
	{
		if (r->getName() == name)
		{
			recipes.remove(r);
			break;
		}
	}
}

/*
	Return a reference to a Recipe object from list<Recipe>* for this Menu object.
*/
Recipe& Meal::getRecipeInMeal(string& name)
{
	for (auto& r : recipes)
	{
		if (r->getName() == name)
		{
			return *r;
		}
	}
	return *recipes.front();
}

/*
	Return a reference to a Recipe object from list<Recipe>* for this Menu object.
*/
void Meal::getRecipeListInMeal(list<Recipe*>& lst)
{
	for (auto& r : recipes)
	{
		lst.push_back(r);
	}
}

/*
	Return the number of Recipe objects in list<Recipe>* for this Menu object.
*/
int Meal::getRecipeCount() const
{
	return recipes.size();
}