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
	category = cat;
	ingredientsUsingCategoryCount = 0;
}

void Category::setCategoryName(string& cat)
{
	for (auto& c : cat) c = toupper(c);
	category = cat;
}

string Category::getCategory() const
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

int Category::getIngredientsUsingCategoryCount() const
{
	return ingredientsUsingCategoryCount;
}