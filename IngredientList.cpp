#include "IngredientList.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>

string ingredientListFile;

void setIngredientListFile(string& fileName)
{
	ingredientListFile = fileName;
}

void addIngredient(string& name, string& description, Category& category, list<Ingredient>& list)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.

	string n;
	for (auto& s : name)
	{
		if (s != ',')
			n += s;
	}
	if (!doesIngredientExist(n, list))
	{
		Ingredient ingred(n, description, category);
		list.push_back(ingred);
		category.incrementIngredientsUsingCategoryCount();
	}
}
/*
void addIngredient(string& name, string& description, string& category, list<Ingredient>& list)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.

	if (!doesIngredientExist(name, list))
	{
		for (auto& s : name)
		{
			if (s == ',')
				s = ' ';
		}
		Ingredient ingred(name, description, category);
		list.push_back(ingred);
		category.addIngredientsUsingCategoryCount();
	}
}
*/
void removeIngredient(string& name, list<Ingredient>& list)
{
	// NOTE: WILL NEED TO TAKE INTO ACCOUNT ANY RECIPES UTILIZING THE INGREDIENT BEING REMOVED.
	// CONSIDER OPTION TO OFFER CHOOSING AN INGREDIENT TO REPLACE 'REMOVING' INGREDIENT FOR ALL RECIPES USING 'REMOVING'INGREDIENT.

	if (list.size() > 0)
	{
		for (auto& i : list)
		{
			if (i.getName() == name)
			{
				// since we are removing an ingredient from the list with the intention of no longer using,
				// decrement the ingredientsUsingCategoryCount by 1.
				// does it make sense to have a destructor for ingredients to handle this operation?
				i.getCategoryObj().decrementIngredientsUsingCategoryCount();
				list.remove(i);
				break;
			}
		}
	}
}

void saveIngredientList(string& ingredientListFile, list<Ingredient>& list)
{
	ofstream fout;
	fout.open(ingredientListFile, ios::out);
	for (auto& i : list)
	{
		fout << i.getName() << "," << i.getDescription() << "," << i.getCategoryStr() << "\n";
	}
	fout.close();
}

void loadIngredientList(string& ingredientListFile, list<Ingredient>& ilist, list<Category>& clist)
{
	ifstream fin;
	fin.open(ingredientListFile, ios::in);
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
			addIngredient(row[0], row[1], getCategoryInList(row[2], clist), ilist);
		}
	}
	else
		cout << ingredientListFile << " was not found, load aborted." << endl;
	fin.close();
}

void sortByCategory()
{

}

void sortByName()
{

}

bool doesIngredientExist(string& name, list<Ingredient>& list)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& i : list)
	{
		if (i.getName() == name)
			return true;
	}
	return false;
}

Ingredient& getIngredientInList(string& name, list<Ingredient>& list)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& i : list)
	{
		if (i.getName() == name)
			return i;
	}
	return list.front();
}



/*
IngredientList::IngredientList()
{
	// does it make sense to intialize a "NONE" ingredient?
	ingredientListFile = "Ingredient_List.csv";
}

IngredientList::IngredientList(string& fileName)
{
	// does it make sense to intialize a "NONE" ingredient?
	ingredientListFile = fileName;
}

void IngredientList::addIngredient(string& name, string& description, string& category, CategoryList& curList)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.

	if (!doesIngredientExist(name))
	{
		for (auto& s : name)
		{
			if (s == ',')
				s = ' ';
		}

		string cat;
		if (curList.doesCategoryExist(category))
			cat = category;
		else
			cat = "NONE";

		Ingredient ingred(name, description, cat, curList);
		ingredientList.push_back(ingred);
		ingred.getCategoryObj().addIngredientsUsingCategoryCount();
	}
}

void IngredientList::removeIngredient(string& name)
{
	// NOTE: WILL NEED TO TAKE INTO ACCOUNT ANY RECIPES UTILIZING THE INGREDIENT BEING REMOVED.
	// CONSIDER OPTION TO OFFER CHOOSING AN INGREDIENT TO REPLACE 'REMOVING' INGREDIENT FOR ALL RECIPES USING 'REMOVING'INGREDIENT.

	for (auto& i : ingredientList)
	{
		if (i.getName() == name)
		{
			// since we are removing an ingredient from the list with the intention of no longer using,
			// decrement the ingredientsUsingCategoryCount by 1.
			// does it make sense to have a destructor for ingredients to handle this operation?
			i.getCategoryObj().subIngredientsUsingCategoryCount();
			ingredientList.remove(i);
			break;
		}
	}
}

void IngredientList::saveIngredientList()
{
	ofstream fout;
	fout.open(ingredientListFile, ios::out);
	for (auto& i : ingredientList)
	{
		fout << i.getName() << "," << i.getDescription() << "," << i.getCategoryStr() << "\n";
	}
	fout.close();
}

void IngredientList::loadIngredientList(CategoryList& list)
{
	ifstream fin;
	fin.open(ingredientListFile, ios::in);
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
			addIngredient(row[0], row[1], row[2], list);
		}
	}
	else
		cout << ingredientListFile << " was not found, load aborted." << endl;
	fin.close();
}

void IngredientList::sortByCategory()
{

}

void IngredientList::sortByName()
{

}

int IngredientList::getSize()
{
	return ingredientList.size();
}

bool IngredientList::isEmpty()
{
	return (ingredientList.size() == 0);
}

bool IngredientList::doesIngredientExist(string& name)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& i : ingredientList)
	{
		if (i.getName() == name)
			return true;
	}
	return false;
}

Ingredient& IngredientList::getIngredientInList(string& name)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& i : ingredientList)
	{
		if (i.getName() == name)
			return i;
	}
	return ingredientList.front();
}
*/