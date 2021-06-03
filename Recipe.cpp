/*
	Recipe.cpp
	Function definitions for Recipe.h
*/

#include"Recipe.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Makes two Recipe objects comparable using name variable.
bool Recipe::operator == (const Recipe& r) const
{
	return name == r.name;
}

// Makes two Recipe objects comparable using name variable.
bool Recipe::operator != (const Recipe& r) const
{
	return !operator == (r);
}

// Initialize a blank Recipe object.
Recipe::Recipe()
{
	name = "";
	cuisine = "";
	description = "";
	direction = "";
	servingCount = 0;
	yield = 0;
	string u = "NONE";
	Units un(u);
	yieldUnit = un;
	mealType = "";
}

// Initialize an Recipe object with using valid arguments.
Recipe::Recipe(string& name, string& cuisine, string& description, string& direction, int& servingCount, int& yield, string& yieldUnit, string& mealtype, list<pair<string, int>>& lst)
{
	setName(name);
	setCuisine(cuisine);
	setDescription(description);
	setDirection(direction);
	setServingCount(servingCount);
	setYield(yield);
	setYieldUnit(yieldUnit);
	setMealType(mealtype, lst);
}

// Set the name of the Recipe object.
void Recipe::setName(string& name)
{
	stringRemoveCommas(name);
	this->name = name;
}

// Set the cuisine of the Recipe object.
void Recipe::setCuisine(string& cuisine)
{
	stringRemoveCommas(cuisine);
	stringToUpperAll(cuisine);
	this->cuisine = cuisine;
}

// Set the description of the Recipe object.
void Recipe::setDescription(string& description)
{
	stringRemoveCommas(description);
	this->description = description;
}

// Set the direction of the Recipe object.
void Recipe::setDirection(string& direction)
{
	stringRemoveCommas(direction);
	this->direction = direction;
}

// Set the serving count of the Recipe object.
void Recipe::setServingCount(int& servingCount)
{
	this->servingCount = servingCount;
}

// Set the number of yielded units of measure of the Recipe object.
void Recipe::setYield(int& yield)
{
	this->yield = yield;
}

// Set the  units of measure of the yielded units of the Recipe object.
void Recipe::setYieldUnit(string& yieldUnit)
{
	string u = yieldUnit;
	Units un(u);
	this->yieldUnit = un;
}

// Set the meal type of the Recipe object.
void Recipe::setMealType(string& mealtype, list<pair<string, int>>& lst)
{
	stringRemoveCommas(mealtype);
	stringToUpperAll(mealtype);
	if (mealtype != mealType && doesMealTypeExist(mealtype, lst))
	{
		decrementRecipeUsingMealTypeCount(mealType, lst);
		mealType = mealtype;
		incrementRecipeUsingMealTypeCount(mealType, lst);
	}
	else
	{
		addMealType(mealtype, lst);
		mealType = mealtype;
		incrementRecipeUsingMealTypeCount(mealType, lst);
	}
}

// Add an IngredientInRecipe object to a list<IngredientInRecipe> for the Recipe object.
void Recipe::addIngredientInRecipe(string& ingredientName, float& quantity, string& unit, list<Ingredient>& lst)
{
	//stringRemoveCommas(ingred);	// Do we need this here?  No.

	if (!doesIngredientInRecipeExist(ingredientName))
	{
		IngredientInRecipe recipeIngred(ingredientName, quantity, unit, lst);
		ingredientsList.push_back(recipeIngred);
	}
}

// Add an IngredientInRecipe object to a list<IngredientInRecipe> for the Recipe object.
void Recipe::addIngredientInRecipe(Ingredient& ingredient, float& quantity, string& unit)
{
	IngredientInRecipe recipeIngred(ingredient, quantity, unit);
	ingredientsList.push_back(recipeIngred);
}

// Returns the name of the Recipe object.
string Recipe::getName() const
{
	return name;
}

// Returns the cuisine of the Recipe object.
string Recipe::getCuisine() const
{
	return cuisine;
}

// Returns the description of the Recipe object.
string Recipe::getDescription()
{
	return description;
}

// Returns the direction of the Recipe object.
string Recipe::getDirection()
{
	return direction;
}

// Returns the number of servings of the Recipe object.
int Recipe::getServingCount() const
{
	return servingCount;
}

// Returns the number of yield of the Recipe object.
int Recipe::getYield()
{
	return yield;
}

// Returns the yield units of measure as a string value of the Recipe object.
string Recipe::getYieldUnitStr()
{
	return yieldUnit.getUnitStr();
}

// Returns the Units object for yield unit of measure of the Recipe object.
Units Recipe::getYieldUnit()
{
	return yieldUnit;
}

// Returns the name of the Recipe object.
string Recipe::getMealType() const
{
	return mealType;
}

// Returns the number of IngredientInRecipe objects in the Recipe object.
int Recipe::getIngredientCount()
{
	return ingredientsList.size();
}

// Returns the reference to list<IngredientInRecipe> of the Recipe object.
list<IngredientInRecipe>& Recipe::getAllIngredientsInRecipe()
{
	return ingredientsList;
}

// Loads list<IngredientInRecipe> into referenced list<IngredientInRecipe> parameter.
void Recipe::getAllIngredientsInRecipe(list<IngredientInRecipe>& lst)
{
	if (ingredientsList.size() > 0)
	{
		for (auto& i : ingredientsList)
		{
			lst.push_back(i);
		}
	}
}

// Returns a reference to IngredientInRecipe object in Recipe's list<IngredientInRecipe>.
IngredientInRecipe& Recipe::getIngredientInRecipe(string& ingredientName)
{
	for (auto& i : ingredientsList)
	{
		if (i.getIngredientName() == ingredientName)
			return i;
	}

	// NOTE: only return the front of the IngredientInRecipe list if the requested ingredient DNE.
	return ingredientsList.front();
}

// Returns a reference to IngredientInRecipe object in Recipe's list<IngredientInRecipe>.
IngredientInRecipe& Recipe::getIngredientInRecipe(int& index)
{
	int counter = 0;
	for (auto& r : ingredientsList)
	{
		if (counter == index)
			return r;
		counter++;
	}
	return ingredientsList.front();
}

// Remove an IngredientInRecipe object from Recipe object's list<IngredientInRecipe>.
void Recipe::removeIngredientFromRecipe(string& ingredientName)
{
	for (auto& r : ingredientsList)
	{
		if (r.getIngredientName() == ingredientName)
		{
			ingredientsList.remove(r);
			break;
		}
	}
}

// Determines if an IngredientInRecipe object exists in Recipe object's list<IngredientInRecipe>.
bool Recipe::doesIngredientInRecipeExist(string& ingredientName)
{
	for (auto& i : ingredientsList)
	{
		if (i.getIngredient().getName() == ingredientName)
			return true;
	}
	return false;
}