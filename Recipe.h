
#pragma once
#ifndef RECIPE_H
#define RECIPE_H

#include "IngredientInRecipe.h"
#include "MealType.h"

class Recipe
{
private:
	string recipeName;
	string recipeDescription;
	string recipeDirections;
	int servingCount;					// 24 servings.
	int yield;							// 8
	Units yieldUnit;					// DOZEN
										// based on servingCount, yield, and yieldUnit, we will be able to determine the quantity of DOZEN makes up one serving 
										// (8 DOZEN = 96 EACH => 96 EACH / 24 servings = 4 EACH per serving, or 1/3 DOZEN per serving)
	string mealType;
	list<IngredientInRecipe> recipeIngredients;	// list of ingredientsInRecipe, class made up of a reference to a chosen ingredient from ingredientList,
												// quantity of ingredient in recipe, and unit of measure for ingreident in recipe
public:
	bool operator == (const Recipe& r) const;
	bool operator != (const Recipe& r) const;
	Recipe();
	Recipe(string& name, string& desc, string& direct, int& count, int& yield, string& unit, string& type, list<pair<string, int>>& list);
	void setName(string& name);
	void setDescription(string& desc);
	void setDirection(string& direct);
	void setServingCount(int& count);
	void setYield(int& yield);
	void setYieldUnit(string& unit);
//	void setMealType(string& type);
	void setMealType(string& type, list<pair<string, int>>& list);
	void addIngredientInRecipe(string& ingred, float& quantity, string& unit, list<Ingredient>& list);
	void addIngredientInRecipe(Ingredient& ingred, float& quantity, string& unit);
	string getName();
	string getDescription();
	string getDirection();
	int getServingCount();
	int getYield();
	string getYieldUnitStr();
	Units getYieldUnit();
	string getMealType();
	int getIngredientCount();
	IngredientInRecipe& getIngredientInRecipe(string& name);
	void removeIngredient(string& ingred);
};

#endif // !RECIPE_H