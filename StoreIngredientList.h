#pragma once
#ifndef STOREINGREDIENTLIST_H
#define STOREINGREDIENTLIST_H

#include <fstream>
#include <sstream>
#include <vector>

#include "StoreIngredient.h"

void addStoreIngredient(string& n, string& d, string& c, string& pc, string& b, string& st, string& sk, float& p, string& u, float& mp, string& mu, string& h, list<StoreIngredient>& lst);
void loadStoreIngredientList(string& file, list<StoreIngredient>& lst);
//bool doesStoreIngredientExist(string& st, string& sk, list<StoreIngredient>& lst);

#endif // !STOREINGREDIENTLIST_H
