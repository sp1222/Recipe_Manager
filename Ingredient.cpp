#include "Ingredient.h"
#include "Category.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

bool Ingredient::operator == (const Ingredient & i) const
{
	return ingredientName == i.ingredientName;
}

bool Ingredient::operator != (const Ingredient& i) const
{
	return !operator == (i);
}

Ingredient::Ingredient() 
{
	ingredientName = "";
	ingredientDescription = "";
	ingredientCategory = nullptr;
	recipesUsingIngredientCount = 0;
}

Ingredient::Ingredient(string& name, string& description, Category& category)
{

	setName(name);
	setDescription(description);
	ingredientCategory = &category;
	setCategory(category);
	recipesUsingIngredientCount = 0;
}

void Ingredient::setName(string& name)
{
	stringRemoveCommas(name);
	ingredientName = name;
}

// set and get description of ingredient
void Ingredient::setDescription(string& description)
{
	stringRemoveCommas(description);
	ingredientDescription = description;
}

void Ingredient::setCategory(Category& category)//, CategoryList& curList)
{
	// NOTE: do we need to remove commas from each string value?  No.
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?  No.

	// since this implies a re-categorizing of this instance of an ingredient, 
	// we first decrement the ingredientsUsingCategoryCount value for the current category if needed.
	// reassign ingredientCategory to a reference of its new category in the categoryList object.
	// then increment the ingredientsUsingCategoryCount value for the new current category.
	if (ingredientCategory != nullptr)
		ingredientCategory->decrementIngredientsUsingCategoryCount();
	ingredientCategory = &category;
	ingredientCategory->incrementIngredientsUsingCategoryCount();
}

string Ingredient::getName() const
{
	return ingredientName;
}

string Ingredient::getDescription()
{
	return ingredientDescription;
}

string Ingredient::getCategoryStr() const
{
	return ingredientCategory->getName();
}

Category& Ingredient::getCategoryObj()
{
	return *ingredientCategory;
}

int Ingredient::getRecipesUsingIngredientCount() const
{
	return recipesUsingIngredientCount;
}

void Ingredient::incrementRecipesUsingIngredientCount()
{
	recipesUsingIngredientCount++;
}

void Ingredient::decrementRecipesUsingIngredientCount()
{
	if (recipesUsingIngredientCount > 0)
		recipesUsingIngredientCount--;
}