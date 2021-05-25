#include "StoreIngredient.h"
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
bool StoreIngredient::operator == (const StoreIngredient& si) const
{
	return category == si.sku;
}

bool StoreIngredient::operator != (const StoreIngredient& si) const
{
	return !operator == (si);
}

StoreIngredient::StoreIngredient()
{
	name = "";
	description = "";
	category = "";
	parentCategory = "";
	brand = "";
	store = "";
	sku = "";
	price = 0.00;
	UOM = "";
	microPrice = 0.00;
	microUOM = "";
	href = "";
}

StoreIngredient::StoreIngredient(string& n, string& d, string& c, string& pc, string& b, string& st, string& sk, float& p, string& u, float& mp, string& mu, string& h)
{
	setName(n);
	setDescription(d);
	setCategory(c);
	setParentCategory(pc);
	setBrand(b);
	setStore(st);
	setSKU(sk);
	setPrice(p);
	setUOM(u);
	setMicroPrice(mp);
	setMicroUOM(mu);
	setHREF(h);
}

void StoreIngredient::setName(string& n)
{
	stringRemoveCommas(n);
	name = n;
}

void StoreIngredient::setDescription(string& d)
{
	stringRemoveCommas(d);
	description = d;
}

void StoreIngredient::setCategory(string& c)
{
	stringRemoveCommas(c);
	category = c;
}
void StoreIngredient::setParentCategory(string& pc)
{
	stringRemoveCommas(pc);
	parentCategory = pc;
}

void StoreIngredient::setBrand(string& b)
{
	stringRemoveCommas(b);
	brand = b;
}

void StoreIngredient::setStore(string& st)
{
	stringRemoveCommas(st);
	store = st;
}

void StoreIngredient::setSKU(string& sk)
{
	sku = sk;
}

void StoreIngredient::setPrice(float& p)
{
	price = p;
}

void StoreIngredient::setUOM(string& u)
{
	stringRemoveCommas(u);
	UOM = u;
}

void StoreIngredient::setMicroPrice(float& mp)
{
	microPrice = mp;
}

void StoreIngredient::setMicroUOM(string& mu)
{
	stringRemoveCommas(mu);
	microUOM = mu;
}

void StoreIngredient::setHREF(string& h)
{
	href = h;
}

string StoreIngredient::getName() const
{
	return name;
}

string StoreIngredient::getDescription() const
{
	return description;
}

string StoreIngredient::getCategory() const
{
	return category;
}

string StoreIngredient::getParentCategory() const
{
	return parentCategory;
}

string StoreIngredient::getBrand() const
{
	return brand;
}

string StoreIngredient::getStore() const
{
	return store;
}

string StoreIngredient::getSKU() const
{
	return sku;
}

float StoreIngredient::getPrice() const
{
	return price;
}

string StoreIngredient::getUOM() const
{
	return UOM;
}

float StoreIngredient::getMicroPrice() const
{
	return microPrice;
}

string StoreIngredient::getMicroUOM() const
{
	return microUOM;
}

string StoreIngredient::getHREF() const
{
	return href;
}