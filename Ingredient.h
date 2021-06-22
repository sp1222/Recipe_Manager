/*
	Ingredient.h
	Defines an Ingredient class.
*/

#pragma once
#ifndef INGREDIENT_H
#define INGREDIENT_H

#include "Category.h"
//#include "StoreIngredient.h"

/*
	Ingredient class definition.
*/
class Ingredient
{

private:
	std::string name;
	std::string description;
	Category* category = nullptr;
	int recipesUsingIngredientCount;
//	list<StoreIngredient*> storeIngredient;
	
public:

	/*
		Makes two Ingredient objects comparable by name.
        @param c : constant reference to Ingredient object.
        @return : If object matches this instance of a Ingredient.
	*/
	bool operator == (const Ingredient& i) const;

	/*
		Makes two Ingredient objects comparable by name.
		@param c : constant reference to Ingredient object.
		@return : If object does not match this instance of a Ingredient.
	*/
	bool operator != (const Ingredient& i) const;

	/*
		Create an empty Ingredient object.
	*/
	Ingredient();

	/*
		Initialize an Ingredient object with valid parameter values.
		@param name : reference to string to initialize the name of the Ingredient object.
		@param description : reference to string to initialize the description of the Ingredient object.
		@param categoryObj : reference to Category object (from list<Category>) to initialize the pointer to Category object in this Ingredient.
	*/
	Ingredient(std::string& name, std::string& description, Category& categoryObj);

	/*
		Set the name of the Ingredient object.
		@param name : reference to string to initialize the name of the Ingredient object.
		@return If the name has successfully changed.
	*/
	bool setName(std::string& name);

	/*
		Set the description of the Ingredient object.
		@param description : reference to string to initialize the description of the Ingredient object.
	*/
	void setDescription(std::string& description);

	/*
		Set the reference to Category object from list<Category> object.
		@param categoryObj : reference to Category object (from list<Category>) to initialize the pointer to Category object in this Ingredient.
	*/
	void setCategory(Category& categoryObj);

	/*
		UNDER CONSTRUCTION
	*/
//	void addStoreIngredient(string& n, string& d, string& c, string& st, string& sk, float& p);  // treat this like we do with categories, where we have a list of pointers to StoreIngredient objects?

	/*
		Returns the name of Ingredient object.
		@return the name of this Ingredient object.
	*/
	std::string getName() const;

	/*
		Returns the description of Ingredient object.
		@return the description of this Ingredient object.
	*/
	std::string getDescription();

	/*
		Returns the Category object this Ingredient object points to.
		@return the reference to Category object of this Ingredient object.
	*/
	Category& getCategoryObj();

	/*
		Returns the string representation of Category object this Ingredient object points to.
		@return the name of the Category object of this Ingredient object.
	*/
	std::string getCategoryStr() const;

	/*
		Returns the number of Recipe objects this Ingredient object is a part of.
		@return the number of Recipe objects using this Ingredient object.
	*/
	int getRecipesUsingIngredientCount() const;

	/*
		Increments the number of Recipe objects this Ingredient object is a part of.
	*/
	void incrementRecipesUsingIngredientCount();

	/*
		Decrements the number of Recipe objects this Ingredient object is a part of.
	*/
	void decrementRecipesUsingIngredientCount();

	/*
		UNDER CONSTRUCTION
	*/
//	void getStoreIngredientListStr(list<string>& lstr);
};


#endif