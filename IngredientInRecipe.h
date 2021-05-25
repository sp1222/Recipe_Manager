#pragma once
#ifndef INGREDIENTINRECIPE_H
#define INGREDIENTINRECIPE_H

#include "IngredientList.h"
#include<iostream>
#include "Units.h"

class IngredientInRecipe
{
private:
	Ingredient* ingredient = nullptr;
	float ingredientQuantity = 0.0f;
	Units ingredientUnit;
public:
	bool operator == (const IngredientInRecipe& i) const;
	bool operator != (const IngredientInRecipe& i) const;
	IngredientInRecipe();
	IngredientInRecipe(string& ingred, float& quantity, string& unit, list<Ingredient>& list);
	IngredientInRecipe(Ingredient& ingred, float& quantity, string& unit);
	void setIngredient(Ingredient& ingred);
	void setIngredient(string& ingred);
	void setIngredientQuantity(float& quantity);
	void setIngredientUnit(string& unit);
	Ingredient& getIngredient();
	string getIngredientName() const;
	float getIngredientQuantity() const;
	Units getIngredientUnit();
	string getIngredientUnitStr() const;
};

#endif