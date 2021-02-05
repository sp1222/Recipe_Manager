#include "IngredientList.h"
#include "RecipeList.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>


void addRecipe(string& name, string& desc, string& direct, int& count, int& yield, string& unit, string& type, list<pair<string, int>>& tList, list<Recipe>& list)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.
	for (auto& s : name)
	{
		if (s == ',')
			s = ' ';
	}

	if (!doesRecipeExist(name, list))
	{
		Recipe nRecipe(name, desc, direct, count, yield, unit, type, tList);
		list.push_back(nRecipe);
	}

}

void addRecipe(Recipe& recipe, list<Recipe>& list)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.
	string name = recipe.getName();
	if (!doesRecipeExist(name, list))
	{
		list.push_back(recipe);
	}
}

void removeRecipe(string& name, list<Recipe>& list)
{
	// NOTE: WILL NEED TO TAKE INTO ACCOUNT ANY RECIPES UTILIZING THE INGREDIENT BEING REMOVED.
	// CONSIDER OPTION TO OFFER CHOOSING AN INGREDIENT TO REPLACE 'REMOVING' INGREDIENT FOR ALL RECIPES USING 'REMOVING'INGREDIENT.

	for (auto& r : list)
	{
		if (r.getName() == name)
		{
			// since we are removing an ingredient from the list with the intention of no longer using,
			// decrement the ingredientsUsingCategoryCount by 1.
			// does it make sense to have a destructor for ingredients to handle this operation?

			list.remove(r);
			break;
		}
	}
}

void saveRecipeList(string& file, list<Recipe>& list)
{
	ofstream fout;
	fout.open(file, ios::out);
	for (auto& r : list)
	{
		// first we output to file general recipe details.
		fout << r.getName() << "," << r.getDescription() << "," << r.getDirection() << "," 
			<< r.getServingCount() << "," << r.getYield() << "," << r.getYieldUnitStr() << "," 
			<< r.getMealType() << ",";

		// next we output to file the details for each ingredient in the recipe.
		for (int i = 0; i < r.getIngredientCount(); i++)
		{
			IngredientInRecipe& curIngred = r.getIngredientInRecipe(i);
			fout << curIngred.getIngredientName() << ","
				<< curIngred.getIngredientQuantity() << ","
				<< curIngred.getIngredientUnitStr() << ",";
		}
		// indicates the end of a recipe being outputted.
		fout << endl;
	}
	fout.close();
}


void loadRecipeList(string& file, list<Recipe>& rList, list<Ingredient>& iList, list<pair<string, int>>& mlist)
{
	ifstream fin;
	fin.open(file, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token;
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);
			for (int i = 0; i < row.size(); i++)
			{
				cout << row[i] << endl;
			}
			// in file
			// name,description,direction,serving,yield,yieldunit,mealtype,ingredname,ingredqty,ingredunitstr
			string name = row[0], desc = row[1], direct = row[2], yieldUnit = row[5], meal = row[6];
			int serv = stoi(row[3]), yield = stoi(row[4]);
			row.erase(row.begin(), row.begin() + 7);
			Recipe rec(name, desc, direct, serv, yield, yieldUnit, meal, mlist);
			while (row.size() > 0)
			{
				string ingredName = row[0];
				float ingredQty = stoi(row[1]);
				string ingredUnit = row[2];
				rec.addIngredientInRecipe(ingredName, ingredQty, ingredUnit, iList);
				row.erase(row.begin(), row.begin() + 3);
			}
			// add recipe to recipeList.
			rList.push_back(rec);
		}
	}
	else
		cout << file << " was not found, load aborted." << endl;
	fin.close();
}

void sortByMealType()
{

}

void sortByNameRecipe()
{

}

bool doesRecipeExist(string& name, list<Recipe>& list)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& r : list)
	{
		if (r.getName() == name)
			return true;
	}
	return false;
}

Recipe& getRecipeInList(string& name, list<Recipe>& list)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& r : list)
	{
		if (r.getName() == name)
			return r;
	}
	return list.front();
}