#include "Ingredient.h"
#include "Category.h"

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

// set and get name of ingredient
void Ingredient::setName(string& name)
{
	string n;
	for (auto& s : name)
	{
		if (s != ',')
			n += s;
	}
	ingredientName = n;
}

// set and get description of ingredient
void Ingredient::setDescription(string& description)
{
	string d;
	for (auto& s : description)
	{
		if (s != ',')
			d += s;
	}
	ingredientDescription = d;
}

void Ingredient::setCategory(Category& category)//, CategoryList& curList)
{
	// NOTE: do we need to remove commas from each string values?
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?

	// since this implies a re-categorizing of this instance of an ingredient, 
	// we first decrement the ingredientsUsingCategoryCount value for the current category if needed.
	// reassign ingredientCategory to a reference of its new category in the categoryList object.
	// then increment the ingredientsUsingCategoryCount value for the new current category.
	if (ingredientCategory != nullptr)
		ingredientCategory->decrementIngredientsUsingCategoryCount();
//		ingredientCategory->removeIngredientUsingCategory(*this);
	ingredientCategory = &category;
	ingredientCategory->incrementIngredientsUsingCategoryCount();
//	ingredientCategory->addIngredientUsingCategory(*this);
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
	return ingredientCategory->getCategory();
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