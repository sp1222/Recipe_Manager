#pragma once
#ifndef STOREINGREDIENTLIST_H
#define STOREINGREDIENTLIST_H

#include <fstream>
#include <list>
#include <sstream>
#include <vector>

#include "StoreIngredient.h"

void addStoreIngredient(std::string& n, std::string& d, std::string& c, std::string& pc, std::string& b, std::string& st, std::string& sk, float& p, std::string& u, float& mp, std::string& mu, std::string& h, std::list<StoreIngredient>& lst);
void loadStoreIngredientList(std::string& file, std::list<StoreIngredient>& lst);
//bool doesStoreIngredientExist(string& st, string& sk, list<StoreIngredient>& lst);

#endif // !STOREINGREDIENTLIST_H
