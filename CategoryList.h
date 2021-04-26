#pragma once
#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H
#include "Category.h"
#include<list>


bool addCategory(string& category, list<Category>& list);
void addCategory(string& str, int& ct, list<Category>& list);
bool removeCategory(string& category, list<Category>& list);
bool doesCategoryExist(string& category, list<Category>& list);
void saveCategoryList(string& categoryListFile, list<Category>& list);
void loadCategoryList(string& categoryListFile, list<Category>& list);
void sortCategories(int byCol, list<Category>& list);
bool compareCategoryNames(const Category& first, const Category& second);
bool compareCategoryIngredientCount(const Category& first, const Category& second);
Category& getCategoryInList(string& cat, list<Category>& list);


#endif
