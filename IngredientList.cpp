/*
	IngredientList.cpp
	Function definitions for IngredientList.h
*/

#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>

#include "IngredientList.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Add an Ingredient object to list<Ingredient>.
bool addIngredient(string& name, string& description, Category& categoryObj, list<Ingredient>& lst)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.
	stringRemoveCommas(name);
	if (!doesNamedIngredientExist(name, lst))
	{
		Ingredient ingred(name, description, categoryObj);
		lst.push_back(ingred);
		return true;
	}
	return false;
}

// Remove an Ingredient object from list<Ingredient>.
bool removeIngredient(string& name, list<Ingredient>& lst)
{
	// NOTE: WILL NEED TO TAKE INTO ACCOUNT ANY RECIPES UTILIZING THE INGREDIENT BEING REMOVED.
	// CONSIDER OPTION TO OFFER CHOOSING AN INGREDIENT TO REPLACE 'REMOVING' INGREDIENT FOR ALL RECIPES USING 'REMOVING'INGREDIENT.

	if (lst.size() > 0)
	{
		for (auto& i : lst)
		{
			if (i.getName() == name && i.getRecipesUsingIngredientCount() == 0)
			{
				// since we are removing an ingredient from the list with the intention of no longer using,
				// decrement the ingredientsUsingCategoryCount by 1.
				// does it make sense to have a destructor for ingredients to handle this operation?
				i.getCategoryObj().decrementIngredientsUsingCategoryCount();
				lst.remove(i);
				return true;
			}
		}
	}
	return false;
}

// Save existing list<Ingredient> to designated fileName.
void saveIngredientList(string& fileName, list<Ingredient>& lst)
{
	ofstream fout;
	fout.open(fileName, ios::out);
	if (fout.is_open())
	{
		for (auto& i : lst)
			fout << i.getName() << "," << i.getDescription() << "," << i.getCategoryStr() << "\n";
	}
	else
		cout << fileName << " was not found, load aborted." << endl;
	fout.close();
}

// Load list<Ingredient> from designated fileName.
void loadIngredientList(string& fileName, list<Ingredient>& ilst, list<Category>& clst)
{
	ifstream fin;
	fin.open(fileName, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token;
			vector<string>row;
			while (getline(s, token, ','))
				row.push_back(token);
			// row[2] is the category name string, 
			// getCategoryInList returns the reference to category object in category list.
			addIngredient(row[0], row[1], getCategoryInList(row[2], clst), ilst);
		}
	}
	else
		cout << fileName << " was not found, load aborted." << endl;
	fin.close();
}

// Sorts a list<Ingredient> by indicated column.
void sortIngredients(int byCol, list<Ingredient>& lst)
{
	switch (byCol)
	{
	case 0:
		lst.sort(compareIngredientNames);
		break;
	case 1:
		lst.sort(compareCategories);
		break;
	case 2:
		lst.sort(compareIngredientRecipeCount);
		break;

	default:

		break;
	}
}

// Comparator by Name.
bool compareIngredientNames(const Ingredient& first, const Ingredient& second)
{
	unsigned int i = 0;
	while ((i < first.getName().length()) && (i < second.getName().length()))
	{
		if (tolower(first.getName()[i]) < tolower(second.getName()[i]))
			return true;
		else if (tolower(first.getName()[i]) > tolower(second.getName()[i]))
			return false;
		i++;
	}
	return (first.getName().length() < second.getName().length());
}

// Comparator by Categories
bool compareCategories(const Ingredient& first, const Ingredient& second)
{
	unsigned int i = 0;
	while ((i < first.getCategoryStr().length()) && (i < second.getCategoryStr().length()))
	{
		if (tolower(first.getCategoryStr()[i]) < tolower(second.getCategoryStr()[i]))
			return true;
		else if (tolower(first.getCategoryStr()[i]) > tolower(second.getCategoryStr()[i]))
			return false;
		i++;
	}
	return (first.getCategoryStr().length() < second.getCategoryStr().length());
}

// Comparator by number of Recipe objects using Ingredient.
bool compareIngredientRecipeCount(const Ingredient& first, const Ingredient& second)
{
	return (first.getRecipesUsingIngredientCount() < second.getRecipesUsingIngredientCount());
}

// Checks if a Ingredient object exists in list<Category> based on its name.
bool doesNamedIngredientExist(string& name, list<Ingredient>& lst)
{
	for (auto it = lst.begin(); it != lst.end(); ++it)
	{
		if (it->getName() == name)
			return true;
	}
	return false;
}

// Returns a reference to named Ingredient object in list<Ingredient> if it exists.
Ingredient& getIngredientInList(string& name, list<Ingredient>& lst)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST? No.

	for (auto& i : lst)
	{
		if (i.getName() == name)
			return i;
	}
	return lst.front();
}
