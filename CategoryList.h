#pragma once
#ifndef CATEGORYLIST_H
#define CATEGORYLIST_H
#include "Category.h"
#include<list>


void addCategory(string& category, list<Category>& list);
void addCategory(string& str, int& ct, list<Category>& list);
void removeCategory(string& category, list<Category>& list);
bool doesCategoryExist(string& category, list<Category>& list);
void saveCategoryList(string& categoryListFile, list<Category>& list);
void loadCategoryList(string& categoryListFile, list<Category>& list);
Category& getCategoryInList(string& cat, list<Category>& list);


#endif
