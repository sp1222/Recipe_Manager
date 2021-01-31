#include "Category.h"

bool Category::operator == (const Category& c) const
{
	return category == c.category;
}

bool Category::operator != (const Category& c) const
{
	return !operator == (c);
}

Category::Category()
{
	category = "NONE";
	ingredientsUsingCategoryCount = 0;
}

Category::Category(string& cat)
{
	for (auto& c : cat) c = toupper(c);
	category = cat;
	ingredientsUsingCategoryCount = 0;
}

string Category::getCategory()
{
	return category;
}

void Category::incrementIngredientsUsingCategoryCount()
{
	ingredientsUsingCategoryCount++;
}

void Category::decrementIngredientsUsingCategoryCount()
{
	ingredientsUsingCategoryCount--;
}

int Category::getIngredientsUsingCategoryCount()
{
	return ingredientsUsingCategoryCount;
}

/*
int Category::getIngredientsUsingCategoryCount()
{
	return ingredientUsingCategory.size();
}

void* getIngredient(string& name)
{

}

// passive functions to increment/decrement the ingredientsUsingCategoryCount variable.
// these are only called when an ingredient is assigned or unassigned to this category
void Category::addIngredientUsingCategory(void* ingred)
{
	ingredientUsingCategory.push_back(ingred);
}

void Category::removeIngredientUsingCategory(void* ingred)
{
	if(ingredientUsingCategory.size() > 0)
		ingredientUsingCategory.remove(ingred);
}

*/