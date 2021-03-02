#pragma once
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "Category.h"

class Ingredient
{

private:
	// name and description of each ingredients
	string ingredientName;
	string ingredientDescription;
	Category* ingredientCategory = nullptr;
	int recipesUsingIngredientCount;
	
	// consider adding vendorList information with pricing and pack size here..
	
public:
	bool operator == (const Ingredient& i) const;
	bool operator != (const Ingredient& i) const;
	Ingredient();
	Ingredient(string& name, string& description, Category& category);
	void setName(string& name);
	void setDescription(string& description);
	void setCategory(Category& category);
	string getName() const;
	string getDescription();
	Category& getCategoryObj();
	string getCategoryStr() const;
	int getRecipesUsingIngredientCount() const;
	void incrementRecipesUsingIngredientCount();
	void decrementRecipesUsingIngredientCount();
};


#endif