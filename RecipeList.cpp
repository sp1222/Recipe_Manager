#include "IngredientList.h"
#include "RecipeList.h"
#include<iostream>
#include<sstream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<regex>


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

bool removeRecipe(string& name, list<Recipe>& list)
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
			return true;
		}
	}
	return false;
}

void saveRecipeList(string& file, list<Recipe>& list)
{
	ofstream fout;
	fout.open(file, ios::out);
	for (auto& r : list)
	{
		// first we output to file general recipe details.
		string d = r.getDirection();
		regex newlines_re("\n+");
		string direct = regex_replace(d, newlines_re, "`");

		fout << r.getName() << "," << r.getDescription() << "," << direct << ","
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
			string name = row[0], desc = row[1], d = row[2], yieldUnit = row[5], meal = row[6];

			regex newlines_re("`");
			string direct = regex_replace(d, newlines_re, "\n");

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

void sortRecipes(int byCol, list<Recipe>& list)
{
	switch (byCol)
	{
	case 0:
		list.sort(compareRecipeNames);
		break;
	case 1:
		list.sort(compareMealTypes);
		break;
	case 2:
		list.sort(compareServingCounts);
		break;
	default:
		break;
	}
}

// sort the list alphabetized by names, disregarding case sensitivity
bool compareRecipeNames(const Recipe& first, const Recipe& second)
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

// sort the list alphabetized by names, disregarding case sensitivity
bool compareMealTypes(const Recipe& first, const Recipe& second)
{
	unsigned int i = 0;
	while ((i < first.getMealType().length()) && (i < second.getMealType().length()))
	{
		if (tolower(first.getMealType()[i]) < tolower(second.getMealType()[i]))
			return true;
		else if (tolower(first.getMealType()[i]) > tolower(second.getMealType()[i]))
			return false;
		i++;
	}
	return (first.getMealType().length() < second.getMealType().length());
}

bool compareServingCounts(const Recipe& first, const Recipe& second)
{
	return (first.getServingCount() < second.getServingCount());
}

void sortRecipeIngredients(int byCol, list<IngredientInRecipe>& list)
{
	switch (byCol)
	{
	case 0:
		list.sort(compareIngredientInRecipeNames);
		break;
	case 1:
		list.sort(compareIngredientInRecipeQuantity);
		break;
	case 2:
		list.sort(compareIngredientInRecipeUnits);
		break;
	default:
		break;
	}
}

// sort the list alphabetized by names, disregarding case sensitivity
bool compareIngredientInRecipeNames(const IngredientInRecipe& first, const IngredientInRecipe& second)
{
	unsigned int i = 0;
	while ((i < first.getIngredientName().length()) && (i < second.getIngredientName().length()))
	{
		if (tolower(first.getIngredientName()[i]) < tolower(second.getIngredientName()[i]))
			return true;
		else if (tolower(first.getIngredientName()[i]) > tolower(second.getIngredientName()[i]))
			return false;
		i++;
	}
	return (first.getIngredientName().length() < second.getIngredientName().length());
}

// sort the list alphabetized by names, disregarding case sensitivity
bool compareIngredientInRecipeQuantity(const IngredientInRecipe& first, const IngredientInRecipe& second)
{

	return (first.getIngredientQuantity() < second.getIngredientQuantity());
}

bool compareIngredientInRecipeUnits(const IngredientInRecipe& first, const IngredientInRecipe& second)
{
	unsigned int i = 0;
	while ((i < first.getIngredientUnitStr().length()) && (i < second.getIngredientUnitStr().length()))
	{
		if (tolower(first.getIngredientUnitStr()[i]) < tolower(second.getIngredientUnitStr()[i]))
			return true;
		else if (tolower(first.getIngredientUnitStr()[i]) > tolower(second.getIngredientUnitStr()[i]))
			return false;
		i++;
	}
	return (first.getIngredientUnitStr().length() < second.getIngredientUnitStr().length());
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