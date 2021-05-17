#pragma once
#ifndef CATEGORY_H
#define CATEGORY_H
#include<string>
#include<list>
using namespace std;

/*
This will be the user controlled ingredient category management system.
The user will be able to add and remove categories as they see fit.

*/

class Category
{
private:
	string category;
	int ingredientsUsingCategoryCount;
public:
	bool operator == (const Category& c) const;
	bool operator != (const Category& c) const;
	Category();
	Category(string& cat);
	void setCategoryName(string& cat);
	string getCategory() const;
	void incrementIngredientsUsingCategoryCount();
	void decrementIngredientsUsingCategoryCount();
	int getIngredientsUsingCategoryCount() const;
};

#endif
