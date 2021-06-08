#pragma once
#ifndef STOREINGREDIENT_H
#define STOREINGREDIENT_H

#include <string>

#include "Helpers.h"

using namespace std;

class StoreIngredient
{
private:
	string name;
	string store;
	string sku;
	string description;
	string category;
	string parentCategory;
	string brand;
	float price;
	string UOM;
	float microPrice;
	string microUOM;
	string href;

public:
	bool operator == (const StoreIngredient& si) const;
	bool operator != (const StoreIngredient& si) const;
	StoreIngredient();
	StoreIngredient(string& n, string& st, string& sk, string& d, string& c, string& pc, string& b, float& p, string& u, float& mp, string& mu, string& h);
	void setName(string& n);
	void setDescription(string& d);
	void setCategory(string& c);
	void setParentCategory(string& c);
	void setBrand(string& b);			
	void setStore(string& s);
	void setSKU(string& s);
	void setPrice(float& p);
	void setUOM(string& u);				
	void setMicroPrice(float& mp);			
	void setMicroUOM(string& mu);		
	void setHREF(string& h);
	string getName() const;
	string getDescription() const;
	string getCategory() const;
	string getParentCategory() const;
	string getBrand() const;					
	string getStore() const;
	string getSKU() const;
	float getPrice() const;
	string getUOM() const;				
	float getMicroPrice() const;			
	string getMicroUOM() const;		
	string getHREF() const;
};

#endif // !STOREINGREDIENT_H
