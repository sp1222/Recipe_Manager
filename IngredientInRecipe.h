/*
	IngredientInRecipe.h
	Defines a Category IngredientInRecipe.
*/

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

	/*
		Makes two IngredientInRecipe objects comparable using name variable.
		@param i : constant reference to IngredientInRecipe object.
		@return : If object matches this instance of a IngredientInRecipe.
	*/
	bool operator == (const IngredientInRecipe& i) const;

	/*
		Makes two IngredientInRecipe objects comparable using name variable.
		@param i : constant reference to IngredientInRecipe object.
		@return : If object matches this instance of a IngredientInRecipe.
	*/
	bool operator != (const IngredientInRecipe& i) const;

	/*
		Initialize a blank IngredientInRecipe object.
	*/
	IngredientInRecipe();

	/*
		Initialize an Ingredient object with using valid arguments.
		@param ingredient : name of Ingredient object to be referenced.
		@param quantity : quantity of Ingredient to be used in recipe.
		@param unit : unit of measure for the Ingredient object being used.
		@param lst : list<Ingredient> to extract the Ingredient object from.
	*/
	IngredientInRecipe(string& ingredient, float& quantity, string& unit, list<Ingredient>& lst);

	/*		
		Initialize an Ingredient object with using valid arguments.
		@param ingredient : reference to Ingredient object being used in Recipe object.
		@param quantity : quantity of Ingredient to be used in recipe.
		@param unit : unit of measure for the Ingredient object being used.
	*/
	IngredientInRecipe(Ingredient& ingredient, float& quantity, string& unit);

	/*
		Set the reference to Ingredient object for this IngredientInRecipe object.
		@param i : constant reference to Ingredient object.
	*/
	void setIngredient(Ingredient& ingredient);

	/*
		Set the quantity value for this IngredientInRecipe object.
		@param quantity : constant reference to quantity value of this IngredientInRecipe object.
	*/
	void setIngredientQuantity(float& quantity);

	/*
		Set the Units object for this IngredientInRecipe object.
		@param unit : string representing the unit of measure for this IngredientInRecipe object.
	*/
	void setIngredientUnit(string& unit);

	/*
		Returns the reference to Ingredient object of this IngredientInRecipe object.
		@return the reference to Ingredient object of this IngredientInRecipe object.
	*/
	Ingredient& getIngredient();

	/*
		Returns the name of the Ingredient object being referenced.
		@return the name of the Ingredient object used in this IngredientInRecipe object.
	*/
	string getIngredientName() const;

	/*
		Returns the quantity value for this IngredientInRecipe object.
		@return the quantity value of this IngredientInRecipe object.
	*/
	float getIngredientQuantity() const;

	/*
		Returns the Units object for this IngredientInRecipe object.
		@return the Units object of this IngredientInRecipe object.
	*/
	Units getIngredientUnit();

	/*
		Returns the Units object's string value for this IngredientInRecipe object.
		@return the Units object's string value of this IngredientInRecipe object.
	*/
	string getIngredientUnitStr() const;
};

#endif