#pragma once
#ifndef STOREINGREDIENT_H
#define STOREINGREDIENT_H

#include <string>

#include "Helpers.h"

class StoreIngredient
{
private:
	std::string name;
	std::string store;
	std::string sku;
	std::string description;
	std::string category;
	std::string parentCategory;
	std::string brand;
	float price;
	std::string UOM;
	float microPrice;
	std::string microUOM;
	std::string href;

public:
	bool operator == (const StoreIngredient& si) const;
	bool operator != (const StoreIngredient& si) const;
	StoreIngredient();
	StoreIngredient(std::string& n, std::string& st, std::string& sk, std::string& d, std::string& c, std::string& pc, std::string& b, float& p, std::string& u, float& mp, std::string& mu, std::string& h);
	void setName(std::string& n);
	void setDescription(std::string& d);
	void setCategory(std::string& c);
	void setParentCategory(std::string& c);
	void setBrand(std::string& b);
	void setStore(std::string& s);
	void setSKU(std::string& s);
	void setPrice(float& p);
	void setUOM(std::string& u);
	void setMicroPrice(float& mp);			
	void setMicroUOM(std::string& mu);
	void setHREF(std::string& h);
	std::string getName() const;
	std::string getDescription() const;
	std::string getCategory() const;
	std::string getParentCategory() const;
	std::string getBrand() const;
	std::string getStore() const;
	std::string getSKU() const;
	float getPrice() const;
	std::string getUOM() const;
	float getMicroPrice() const;			
	std::string getMicroUOM() const;
	std::string getHREF() const;
};

#endif // !STOREINGREDIENT_H
