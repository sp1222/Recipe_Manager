/*
	Recipe.h
	Defines a Recipe Class.
*/

#pragma once
#ifndef RECIPE_H
#define RECIPE_H

#include "IngredientInRecipe.h"
#include "MealTypeList.h"

/*
	Recipe class for instaces of Recipe objects.
	This will be the user controlled Recipe management system.
	The user will be able to add and remove Recipe as they see fit.
*/
class Recipe
{
private:
	string name;
	string cuisine;
	string description;
	string direction;
	int servingCount;					// 24 servings.
	int yield;							// 8
	Units yieldUnit;					// DOZEN
										// based on servingCount, yield, and yieldUnit, we will be able to determine the quantity of DOZEN makes up one serving 
										// (8 DOZEN = 96 EACH => 96 EACH / 24 servings = 4 EACH per serving, or 1/3 DOZEN per serving)
	string mealType;
	list<IngredientInRecipe> ingredientsList;	// list of ingredientsInRecipe, class made up of a reference to an ingredient from ingredientList,
												// quantity of ingredient in recipe, and unit of measure for ingreident in recipe
public:

	/*
		Makes two Recipe objects comparable using name variable.
		@param r : constant reference to Recipe object.
		@return : If object matches this instance of a Recipe.
	*/
	bool operator == (const Recipe& r) const;

	/*
		Makes two Recipe objects comparable using name variable.
		@param r : constant reference to Recipe object.
		@return : If object matches this instance of a Recipe.
	*/
	bool operator != (const Recipe& r) const;

	/*
		Initialize a blank Recipe object.
	*/
	Recipe();

	/*
		Initialize an Recipe object with using valid arguments.
		@param name : name of Recipe object.
		@param cuisine : cuisine of Recipe.
		@param description : description of Recipe.
		@param direction : direction of Recipe.
		@param servingCount : number of servings produced from Recipe.
		@param yield : number of yielded units of measure.
		@param yieldUnit : yield units of measure.
		@param mealtype : mealtype of Recipe.
		@param lst : list of mealtypes in the form of pair<string, int>.
	*/
	Recipe(string& name, string& cuisine, string& description, string& direction, int& servingCount, int& yield, string& yieldUnit, string& mealtype, list<pair<string, int>>& lst);

	/*
		Set the name of the Recipe object.
		@param name : name of Recipe object.
	*/
	void setName(string& name);

	/*
		Set the cuisine of the Recipe object.
		@param cuisine : cuisine of Recipe object.
	*/
	void setCuisine(string& cuisine);

	/*
		Set the description of the Recipe object.
		@param description : description of Recipe object.
	*/
	void setDescription(string& description);

	/*
		Set the direction of the Recipe object.
		@param direction : direction of Recipe object.
	*/
	void setDirection(string& direction);

	/*
		Set the serving count of the Recipe object.
		@param servingCount : servingCount of Recipe object.
	*/
	void setServingCount(int& servingCount);

	/*
		Set the number of yielded units of measure of the Recipe object.
		@param yield : number of yielded units of measure of Recipe object.
	*/
	void setYield(int& yield);

	/*
		Set the  units of measure of the yielded units of the Recipe object.
		@param yieldUnit : units of measure of the yielded units of Recipe object.
	*/
	void setYieldUnit(string& yieldUnit);

	/*
		Set the meal type of the Recipe object.
		@param mealtype : meal type of Recipe object.
		@param lst : list< pair<string, int> > of meal types.
	*/
	void setMealType(string& mealtype, list<pair<string, int>>& lst);

	/*
		Add an IngredientInRecipe object to a list<IngredientInRecipe> for the Recipe object.
		@param ingredientName : name of the Ingredient object to reference to add to list<IngredientInRecipe> of Recipe object.
		@param quantity : quantity of the IngredientInRecipe object.
		@param unit : unit of measure for the IngredientInRecipe object.
		@param lst : list<Ingredient> to get referenced Ingredient object from.
	*/
	void addIngredientInRecipe(string& ingredientName, float& quantity, string& unit, list<Ingredient>& lst);

	/*
		Add an IngredientInRecipe object to a list<IngredientInRecipe> for the Recipe object.
		@param ingredientName : name of the Ingredient object to reference to add to list<IngredientInRecipe> of Recipe object.
		@param quantity : quantity of the IngredientInRecipe object.
		@param unit : unit of measure for the IngredientInRecipe object.
		@param lst : list<Ingredient> to get referenced Ingredient object from.
	*/
	void addIngredientInRecipeFromLoad(string& ingredientName, float& quantity, string& unit, list<Ingredient>& lst);

	/*
		Returns the name of the Recipe object.
		@return the name of Recipe object.
	*/
	string getName() const;

	/*
		Returns the cuisine of the Recipe object.
		@return the cuisine of Recipe object.
	*/
	string getCuisine() const;

	/*
		Returns the description of the Recipe object.
		@return the description of Recipe object.
	*/
	string getDescription();

	/*
		Returns the direction of the Recipe object.
		@return the direction of Recipe object.
	*/
	string getDirection();

	/*
		Returns the number of servings of the Recipe object.
		@return number of servings of Recipe object.
	*/
	int getServingCount() const;

	/*
		Returns the number of yield of the Recipe object.
		@return the number of yielded unit of measure of Recipe object.
	*/
	int getYield();

	/*
		Returns the yield units of measure as a string value of the Recipe object.
		@return the yield units of measure as a string value of Recipe object.
	*/
	string getYieldUnitStr();

	/*
		Returns the Units object for yield unit of measure of the Recipe object.
		@return the Units object.
	*/
	Units getYieldUnit();

	/*
		Returns the name of the Recipe object.
		@return the mealType string value of Recipe object.
	*/
	string getMealType() const;

	/*
		Returns the number of IngredientInRecipe objects in the Recipe object.
		@return the length of list<IngredientInRecipe> of the Recipe object.
	*/
	int getIngredientCount();

	/*
		Returns the reference to list<IngredientInRecipe> of the Recipe object.
		@return reference to list<IngredientInRecipe> of this Recipe object.
	*/
	list<IngredientInRecipe>& getAllIngredientsInRecipe();	// CHANGE THIS METHOD TO THE METHOD BELOW!  

	/*
		Loads list<IngredientInRecipe> into referenced list<IngredientInRecipe> parameter.
		@param lst : list to be populated with this Recipe object's list<IngredientInRecipe>.
	*/
	void getAllIngredientsInRecipe(list<IngredientInRecipe>& lst);

	/*
		Returns a reference to IngredientInRecipe object in Recipe's list<IngredientInRecipe>.
		@param ingredientName : name of ingredient in Recipe object's list<IngredientInRecipe> to be returned.
		@return The IngredientInRecipe reference from list<IngredientInRecipe>.
	*/
	IngredientInRecipe& getIngredientInRecipe(string& ingredientName);

	/*
		Returns a reference to IngredientInRecipe object in Recipe's list<IngredientInRecipe>.
		@param index : index of ingredient in Recipe object's list<IngredientInRecipe> to be returned.
		@return The IngredientInRecipe reference from list<IngredientInRecipe>.
	*/
	IngredientInRecipe& getIngredientInRecipe(int& index);

	/*
		Remove an IngredientInRecipe object from Recipe object's list<IngredientInRecipe>.
		@param ingredientName : name of ingredient in Recipe object's list<IngredientInRecipe> to be removed.
	*/
	void removeIngredientFromRecipe(string& ingredientName);

	/*
		Determines if an IngredientInRecipe object exists in Recipe object's list<IngredientInRecipe>.
		@param ingredientName : name of ingredient in Recipe object's list<IngredientInRecipe> to be searched for.
		@return Whether the ingredient by name exists in the Recipe object's list<IngredientInRecipe>.
	*/
	bool doesIngredientInRecipeExist(string& ingredientName);

};
#endif // !RECIPE_H