#include "Ingredient.h"

bool Ingredient::operator == (const Ingredient & i) const
{
	return ingredientName == i.ingredientName;
}

bool Ingredient::operator != (const Ingredient& i) const
{
	return !operator == (i);
}

Ingredient::Ingredient() 
{
	ingredientName = "";
	ingredientDescription = "";
	ingredientCategory = nullptr;
	recipesUsingIngredientCount = 0;
}

Ingredient::Ingredient(string& name, string& description, Category& category)
{
	// NOTE: need to remove commas from each string values when creating a new ingredient.
	string d;
	for (auto& s : description)
	{
		if (s != ',')
			d += s;
	}

	ingredientName = name;
	ingredientDescription = d;
	ingredientCategory = &category;
	ingredientCategory->incrementIngredientsUsingCategoryCount();
//	ingredientCategory->addIngredientUsingCategory(*this);		// increment this category's ingredientsUsingCategoryCount value 
															//that this ingredient is categorized as.  defaults to Category::NONE
	recipesUsingIngredientCount = 0;
}

// set and get name of ingredient
void Ingredient::setName(string& name)
{
	string n;
	for (auto& s : name)
	{
		if (s != ',')
			n += s;
	}
	ingredientName = n;
}

// set and get description of ingredient
void Ingredient::setDescription(string& description)
{
	string d;
	for (auto& s : description)
	{
		if (s != ',')
			d += s;
	}
	ingredientDescription = d;
}

void Ingredient::setCategory(Category& category)//, CategoryList& curList)
{
	// NOTE: do we need to remove commas from each string values?
	// WILL toupper BE REQUIRED WHEN USING DROPDOWN BOXES?

	// since this implies a re-categorizing of this instance of an ingredient, 
	// we first decrement the ingredientsUsingCategoryCount value for the current category.
	// reassign ingredientCategory to a reference of its new category in the categoryList object.
	// then increment the ingredientsUsingCategoryCount value for the new current category.
	if (ingredientCategory != nullptr)
		ingredientCategory->decrementIngredientsUsingCategoryCount();
//		ingredientCategory->removeIngredientUsingCategory(*this);
	ingredientCategory = &category;
	ingredientCategory->incrementIngredientsUsingCategoryCount();
//	ingredientCategory->addIngredientUsingCategory(*this);
}

string Ingredient::getName() const
{
	return ingredientName;
}

string Ingredient::getDescription()
{
	return ingredientDescription;
}

string Ingredient::getCategoryStr() const
{
	return ingredientCategory->getCategory();
}

Category& Ingredient::getCategoryObj()
{
	return *ingredientCategory;
}

int Ingredient::getRecipesUsingIngredientCount() const
{
	return recipesUsingIngredientCount;
}

void Ingredient::incrementRecipesUsingIngredientCount()
{
	recipesUsingIngredientCount++;
}

void Ingredient::decrementRecipesUsingIngredientCount()
{
	if (recipesUsingIngredientCount > 0)
		recipesUsingIngredientCount--;
}


/*
// return the ingredient's unit as datatype Unit
Unit Ingredient::getUnit()
{
	return ingredientUnit.unit;
}


// return the ingredinet's unit as datatype string
std::string Ingredient::getUnitString()
{
	std::string str;

	switch (static_cast<int>(ingredientUnit.unit))
	{

		case static_cast<int>(Unit::NONE) :

			str = "NONE";

			break;

		case static_cast<int>(Unit::POUND) :

			str = "POUND";

			break;

		case static_cast<int>(Unit::OUNCEWEIGHT) :

			str = "OUNCEWEIGHT";

			break;

		case static_cast<int>(Unit::KILOGRAM) :

			str = "KILOGRAM";

			break;

		case static_cast<int>(Unit::GRAM) :

			str = "GRAM";

			break;

		case static_cast<int>(Unit::GALLON) :

			str = "GALLON";

			break;

		case static_cast<int>(Unit::HALFGALLON) :

			str = "HALFGALLON";

			break;

		case static_cast<int>(Unit::QUART) :

			str = "QUART";

			break;

		case static_cast<int>(Unit::PINT) :

			str = "PINT";

			break;

		case static_cast<int>(Unit::CUP) :

			str = "CUP";

			break;

		case static_cast<int>(Unit::OUNCEFLUID) :

			str = "OUNCEFLUID";

			break;

		case static_cast<int>(Unit::TABLESPOON) :

			str = "TABLESPOON";

			break;

		case static_cast<int>(Unit::TEASPOON) :

			str = "TEASPOON";

			break;

		case static_cast<int>(Unit::LITER) :

			str = "LITER";

			break;

		case static_cast<int>(Unit::MILLILITER) :

			str = "MILLILITER";

			break;

		case static_cast<int>(Unit::EACH) :

			str = "EACH";

			break;

		default:

			str = "NONE";
			// THROW EXCEPTIONS AND STATE ERROR~!

			break;

	}
	return str;
}

// return the ingredient's type as datatype UnitType
UnitType Ingredient::getType()
{
	return ingredientUnit.type;
}

// returns the ingredient's type as datatyp string
std::string Ingredient::getTypeStr()
{
	std::string str;

	switch (static_cast<int>(ingredientUnit.type))
	{

		case static_cast<int>(UnitType::NONE) :

			str = "NONE";

			break;

		case static_cast<int>(UnitType::WEIGHT) :

			str = "WEIGHT";

			break;

		case static_cast<int>(UnitType::VOLUME) :

			str = "VOLUME";

			break;

		case static_cast<int>(UnitType::COUNT) :

			str = "COUNT";

			break;

		default:

			str = "NONE";
			// THROW EXCEPTIONS AND STATE ERROR~!

			break;

	}
	return str;
}

/*
// sets the ingredient's category
void Ingredients::setCategory(const int& c)
{
	ingredientCategory.category = static_cast<Category>(c);
}

// returns the ingredient's category as datatype Category
Category Ingredients::getCategory()
{
	return ingredientCategory.category;
}

// returns the ingredient's category as datatype string
std::string Ingredient::getCategoryString()
{

	MAP OUT CATEGORIES
	
	std::string str;

	switch (static_cast<int>(ingredientCategory.category))
	{

		case static_cast<int>(Category::NONE) :

			str = "NONE";

			break;

		case static_cast<int>(Category::SEAFOOD) :

			str = "SEAFOOD";

			break;

		case static_cast<int>(Category::POULTRY) :

			str = "POULTRY";

			break;

		case static_cast<int>(Category::BEEF) :

			str = "BEEF";

			break;

		case static_cast<int>(Category::PORK) :

			str = "PORK";

			break;

		case static_cast<int>(Category::EGGS) :

			str = "EGGS";

			break;

		case static_cast<int>(Category::DAIRYLIQUID) :

			str = "DAIRYLIQUID";

			break;

		case static_cast<int>(Category::DAIRYNONLIQUID) :

			str = "DAIRYNONLIQUID";

			break;

		case static_cast<int>(Category::STARCH) :

			str = "STARCH";

			break;

		case static_cast<int>(Category::VEGETABLEHEARTY) :

			str = "VEGETABLEHEARTY";

			break;

		case static_cast<int>(Category::VEGETABLELIGHT) :

			str = "VEGETABLELIGHT";

			break;

		case static_cast<int>(Category::FRUIT) :

			str = "FRUIT";

			break;

		case static_cast<int>(Category::GRAIN) :

			str = "GRAIN";

			break;

		case static_cast<int>(Category::LEGUMES) :

			str = "LEGUMES";

			break;

		case static_cast<int>(Category::NUTSANDSEEDS) :

			str = "NUTSANDSEEDS";

			break;

		case static_cast<int>(Category::OILS) :

			str = "OILS";

			break;

		case static_cast<int>(Category::VINEGARS) :

			str = "VINEGARS";

			break;

		case static_cast<int>(Category::SPICESANDSEASONINGS) :

			str = "SPICESANDSEASONINGS";

			break;

		default:

			str = "NONE";
			// THROW EXCEPTIONS AND STATE ERROR~!

			break;

	}
	return str;
	
}
*/

/*

// adds an Allergen to the ingredient's vector of Allergens
void Ingredient::addAllergen(const int& a)
{
	// DO NOT ALLOW ADDS IF THE FIRST ALLERGEN IS NONE.
	// CONSIDER MAKING ALLERGENS ALTERABLE..
	if(ingredientAllergensList.allergen[0] != Allergens::NONE)
		ingredientAllergensList.allergen.push_back(static_cast<Allergens>(a));
}

// returns ingredient's individual Allergens as datatype Allergens
Allergens Ingredient::getAllergens(const int& index)
{
	return ingredientAllergensList.allergen[index];
}

// returns the ingredient's individual Allergens as datatype string
std::string Ingredient::getAllergensString(const int& index)
{
	
	std::string str;

	switch (static_cast<int>(ingredientAllergensList.allergen[index]))
	{

		case static_cast<int>(Allergens::NONE) :

			str = "NONE";

			break;

		case static_cast<int>(Allergens::SHELLFISH) :

			str = "SHELLFISH";

			break;

		case static_cast<int>(Allergens::DAIRY) :

			str = "DAIRY";

			break;

		case static_cast<int>(Allergens::EGGS) :

			str = "EGGS";

			break;

		case static_cast<int>(Allergens::WHEAT) :

			str = "WHEAT";

			break;

		case static_cast<int>(Allergens::GLUTEN) :

			str = "GLUTEN";

			break;

			
		case static_cast<int>(Allergens::TREENUTS) :

			str = "TREENUTS";

			break;

		case static_cast<int>(Allergens::PEANUTS) :

			str = "PEANUTS";

			break;

		case static_cast<int>(Allergens::SEEDS) :

			str = "SEEDS";

			break;

		case static_cast<int>(Allergens::SESAME) :

			str = "SESAME";

			break;

		case static_cast<int>(Allergens::SOY) :

			str = "SOY";

			break;

		case static_cast<int>(Allergens::CAPSICUM) :

			str = "CAPSICUM";

			break;
			
		case static_cast<int>(Allergens::TOMATOES) :

			str = "TOMATOES";

			break;

		case static_cast<int>(Allergens::POULTRY) :

			str = "POULTRY";

			break;

		case static_cast<int>(Allergens::LUPIN) :

			str = "LUPIN";

			break;

		case static_cast<int>(Allergens::SULFITES) :

			str = "SULFITES";

			break;
			
		default:

			str = "EMPTY";
			// THROW EXCEPTIONS AND STATE ERROR~!
			// CANNOT HAVE AN EMPTY LIST OF ALLERGENS.

			break;

	}
	return str;
}
*/
