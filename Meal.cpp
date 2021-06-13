/*
	Meal.cpp
	Function definitions for Meal.h
*/

#include "Meal.h"

using namespace std;

/*
	Makes two Meal objects comparable using name variable.
*/
bool Meal::operator == (const Meal& m) const
{
	return name == m.getName();
}

/*
	Makes two Meal objects comparable using name variable.
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
	description = "";
	scheduled = wxDateTime::Today();	// consider means to default to the date currently highlighted in calendar.
	numberOfServings = 0;
}

/*
	Initialize a Meal object with valid parameter values.
*/
Meal::Meal(string& name, string& description, wxDateTime& scheduled, int numberOfServings, list<Recipe>& recipes)
{
	this->name = name;
	this->description = description;
	this->scheduled = scheduled;
	this->numberOfServings = numberOfServings;
	for (auto& r : recipes)
		this->recipes->push_back(r);
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
	Returns the name of Meal object.
*/
string Meal::getName() const
{
	return name;
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
wxDateTime Meal::getScheduled()
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
	Add a reference to a Recipe object to list<Recipes> for this Menu object.
*/
void Meal::addRecipeToMenu(string& name, list<Recipe>& lst)
{
	recipes->push_back(getRecipeInList(name, lst));
}

/*
	Remove a reference to a Recipe object from list<Recipes> for this Menu object.
*/
void Meal::removeRecipeFromMenu(string& name)
{
	for (auto& r : *recipes)
	{
		if (r.getName() == name)
		{
			recipes->remove(r);
			break;
		}
	}
}

/*
	Return a reference to a Recipe object from list<Recipe> for this Menu object.
*/
Recipe& Meal::getRecipeInMeal(string& name)
{
	for (auto& r : *recipes)
	{
		if (r.getName() == name)
		{
			return r;
		}
	}
	return recipes->front();
}