#include "Category.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

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

void Category::setName(string& cat)
{
	stringRemoveCommas(cat);
	stringToUpperAll(cat);
	category = cat;
}

string Category::getName() const
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