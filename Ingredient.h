#pragma once
#ifndef INGREDIENT_H
#define INGREDIENT_H
#include "Category.h"
//#include "StoreIngredient.h"

class Ingredient
{

private:
	// name and description of each ingredients
	string ingredientName;
	string ingredientDescription;
	Category* ingredientCategory = nullptr;
	int recipesUsingIngredientCount;
//	list<StoreIngredient*> storeIngredient;
	
public:
	bool operator == (const Ingredient& i) const;
	bool operator != (const Ingredient& i) const;
	Ingredient();
	Ingredient(string& name, string& description, Category& category);
	void setName(string& name);
	void setDescription(string& description);
	void setCategory(Category& category);
	//	void addStoreIngredient(string& n, string& d, string& c, string& st, string& sk, float& p);  // treat this like we do with categories, where we have a list of pointers to StoreIngredient objects?
	string getName() const;
	string getDescription();
	Category& getCategoryObj();
	string getCategoryStr() const;
	int getRecipesUsingIngredientCount() const;
	void incrementRecipesUsingIngredientCount();
	void decrementRecipesUsingIngredientCount();
	void getStoreIngredientListStr(list<string>& lstr);
};


#endif