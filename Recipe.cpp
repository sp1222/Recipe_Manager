#include"Recipe.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

bool Recipe::operator == (const Recipe& r) const
{
	return recipeName == r.recipeName;
}

bool Recipe::operator != (const Recipe& r) const
{
	return !operator == (r);
}

Recipe::Recipe()
{
	recipeName = "";
	cuisine = "";
	recipeDescription = "";
	recipeDirections = "";
	servingCount = 0;
	yield = 0;
	string u = "NONE";
	Units un(u);
	yieldUnit = un;
	mealType = "";
//	recipeIngredients.empty();
}

Recipe::Recipe(string& name, string& cuis, string& desc, string& direct, int& count, int& y, string& unit, string& type, list<pair<string, int>>& list)
{
	setName(name);
	setCuisine(cuis);
	setDescription(desc);
	setDirection(direct);
	setServingCount(count);
	setYield(y);
	setYieldUnit(unit);
	setMealType(type, list);
//	recipeIngredients.empty();
}

void Recipe::setName(string& name)
{
	stringRemoveCommas(name);
	recipeName = name;
}
void Recipe::setCuisine(string& cuis)
{
	stringRemoveCommas(cuis);
	stringToUpperAll(cuis);
	cuisine = cuis;
}

void Recipe::setDescription(string& desc)
{
	stringRemoveCommas(desc);
	recipeDescription = desc;
}

void Recipe::setDirection(string& direct)
{
	stringRemoveCommas(direct);
	recipeDirections = direct;
}

void Recipe::setServingCount(int& count)
{
	servingCount = count;
}

void Recipe::setYield(int& y)
{
	yield = y;
}

// change this to reference a list of units?
void Recipe::setYieldUnit(string& unit)
{
	string u = unit;
	Units un(u);
	yieldUnit = un;
}

void Recipe::setMealType(string& type, list<pair<string, int>>& list)
{
	stringRemoveCommas(type);
	if (type != mealType && doesMealTypeExist(type, list))
	{
		decrementRecipeUsingMealTypeCount(mealType, list);
		mealType = type;
		incrementRecipeUsingMealTypeCount(mealType, list);
	}
	else
	{
		addMealType(type, list);
		mealType = type;
		incrementRecipeUsingMealTypeCount(mealType, list);
	}
}

void Recipe::addIngredientInRecipe(string& ingred, float& quantity, string& unit, list<Ingredient>& list)
{
	stringRemoveCommas(ingred);	// Do we need this here?

	if (!doesIngredientInRecipeExist(ingred))
	{
		IngredientInRecipe recipeIngred(ingred, quantity, unit, list);
		recipeIngredients.push_back(recipeIngred);
	}
	else
		cout << "\nUnable to find ingredient in ingredientList to add to recipe." << endl;
}

void Recipe::addIngredientInRecipe(Ingredient& ingred, float& quantity, string& unit)
{
	IngredientInRecipe recipeIngred(ingred, quantity, unit);
	recipeIngredients.push_back(recipeIngred);
}

string Recipe::getName() const
{
	return recipeName;
}

string Recipe::getCuisine() const
{
	return cuisine;
}

string Recipe::getDescription()
{
	return recipeDescription;
}

string Recipe::getDirection()
{
	return recipeDirections;
}

int Recipe::getServingCount() const
{
	return servingCount;
}

int Recipe::getYield()
{
	return yield;
}

string Recipe::getYieldUnitStr()
{
	return yieldUnit.getUnitStr();
}

Units Recipe::getYieldUnit()
{
	return yieldUnit;
}

string Recipe::getMealType() const
{
	return mealType;
}

int Recipe::getIngredientCount()
{
	return recipeIngredients.size();
}

list<IngredientInRecipe>& Recipe::getAllIngredientsInRecipe()
{
	return recipeIngredients;
}

// we want to return each ingredient's name, quantity, and unit?
IngredientInRecipe& Recipe::getIngredientInRecipe(string& name)
{
	for (auto& i : recipeIngredients)
	{
		if (i.getIngredientName() == name)
			return i;
	}

	// NOTE: only return the front of the IngredientInRecipe list if the requested ingredient DNE.
	return recipeIngredients.front();
}

IngredientInRecipe& Recipe::getIngredientInRecipe(int& index)
{
	int counter = 0;
	for (auto& r : recipeIngredients)
	{
		if (counter == index)
			return r;
		counter++;
	}
	return recipeIngredients.front();
}

void Recipe::removeIngredientFromRecipe(string& ingred)
{
	for (auto& r : recipeIngredients)
	{
		if (r.getIngredientName() == ingred)
		{
			recipeIngredients.remove(r);
			break;
		}
	}
}

bool Recipe::doesIngredientInRecipeExist(string& str)
{
	for (auto& i : recipeIngredients)
	{
		if (i.getIngredient().getName() == str)
			return true;
	}
	return false;
}