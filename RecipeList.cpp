/*
	RecipeList.h
	Handles lists of type Recipe functionalities.
*/

#include<algorithm>
#include<fstream>
#include<regex>
#include<sstream>
#include<vector>

#include "IngredientList.h"
#include "RecipeList.h"

using namespace std;

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Add a Recipe object to list<Recipe>.
bool addRecipe(string& name, string& cuisine, string& description, string& direction, int& servingCount, int& yield, string& yieldUnit, string& recipetype, list<pair<string, int>>& recipetypelst, list<Recipe>& recipelst)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.

	stringRemoveCommas(name);
	stringRemoveCommas(cuisine);
	stringToUpperAll(cuisine);
	stringRemoveCommas(description);
	stringRemoveCommas(direction);
	stringRemoveCommas(recipetype);
	stringToUpperAll(recipetype);
	if (!doesNamedItemExist<Recipe>(name, recipelst))
	{
		Recipe nRecipe(name, cuisine, description, direction, servingCount, yield, yieldUnit, recipetype, recipetypelst);
		recipelst.push_back(nRecipe);
		return true;
	}
	return false;
}

/*
// Add a Recipe object to list<Recipe>.
void addRecipe(Recipe& recipe, list<Recipe>& lst)
{
	// first, check to make sure the item with the same name (in the same category?) does not exist.
	// second, locate the category that the ingredient is classified under in categoryList
	// if the category does not exist, prompt to select existing category from list.
	// third, create a new ingredient object to save to ingredientList.
	
	if (!doesNamedItemExist<Recipe>(recipe, lst))
	{
		lst.push_back(recipe);
	}
}
*/

// Remove a Recipe object from list<Recipe>.
bool removeRecipe(string& name, list<Recipe>& lst)
{
	// NOTE: WILL NEED TO TAKE INTO ACCOUNT ANY RECIPES UTILIZING THE INGREDIENT BEING REMOVED.
	// CONSIDER OPTION TO OFFER CHOOSING AN INGREDIENT TO REPLACE 'REMOVING' INGREDIENT FOR ALL RECIPES USING 'REMOVING'INGREDIENT.

	for (auto& r : lst)
	{
		if (r.getName() == name)
		{
			// since we are removing an ingredient from the list with the intention of no longer using,
			// decrement the ingredientsUsingCategoryCount by 1.
			// does it make sense to have a destructor for ingredients to handle this operation?

			lst.remove(r);
			return true;
		}
	}
	return false;
}

// Save list<Recipe> to comma separated values file.
void saveRecipeList(string& fileName, list<Recipe>& lst)
{
	ofstream fout;
	fout.open(fileName, ios::out);
	if (fout.is_open())
	{
		for (auto& r : lst)
		{
			// first we output to file general recipe details.
			string d = r.getDirection();
			regex newlines_re("\n+");
			string direct = regex_replace(d, newlines_re, "`");

			fout << r.getName() << "," << r.getCuisine() << "," << r.getDescription() << "," << direct << ","
				<< r.getServingCount() << "," << r.getYield() << "," << r.getYieldUnitStr() << ","
				<< r.getRecipeType() << ",";

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
	}
	fout.close();
}

// Comma separated values file to load list<Recipe> from.
void loadRecipeList(string& fileName, list<Recipe>& recipelst, list<Ingredient>& ingredientlst, list<pair<string, int>>& recipetypelst)
{
	ifstream fin;
	fin.open(fileName, ios::in);
	if (fin.is_open())
	{
		string line = "";
		while (getline(fin, line))
		{
			stringstream s(line);
			string token = "";
			vector<string> row;
			while (getline(s, token, ','))
				row.push_back(token);

			// consider a cleaner way to do this...

			string name = row[0], cuis = row[1], desc = row[2], d = row[3], yieldUnit = row[6], type = row[7];
			int serv = stoi(row[4]), yield = stoi(row[5]);
			row.erase(row.begin(), row.begin() + 8);
			regex newlines_re("`");
			string direct = regex_replace(d, newlines_re, "\n");

			Recipe rec(name, cuis, desc, direct, serv, yield, yieldUnit, type, recipetypelst);
			while (row.size() > 0 && row[0] != "")
			{
				string ingredName = row[0];
				float ingredQty = stof(row[1]);
				string ingredUnit = row[2];
				rec.addIngredientInRecipeFromLoad(ingredName, ingredQty, ingredUnit, ingredientlst);
				row.erase(row.begin(), row.begin() + 3);
			}
			recipelst.push_back(rec);
		}
	}
	fin.close();
}

// Sort the list<Recipe> by column indicated in front end.
void sortRecipes(int byCol, list<Recipe>& lst)
{
	switch (byCol)
	{
	case 0:
		lst.sort(compareRecipeNames);
		break;
	case 1:
		lst.sort(compareRecipeCuisines);
		break;
	case 2:
		lst.sort(compareRecipeTypes);
		break;
	case 3:
		lst.sort(compareServingCounts);
		break;
	default:
		break;
	}
}

// Comparator by name for two Recipe objects.
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

// Comparator by cuisine for two Recipe objects.
bool compareRecipeCuisines(const Recipe& first, const Recipe& second)
{
	unsigned int i = 0;
	while ((i < first.getCuisine().length()) && (i < second.getCuisine().length()))
	{
		if (tolower(first.getCuisine()[i]) < tolower(second.getCuisine()[i]))
			return true;
		else if (tolower(first.getCuisine()[i]) > tolower(second.getCuisine()[i]))
			return false;
		i++;
	}
	return (first.getCuisine().length() < second.getCuisine().length());
}

// Comparator by recipetype for two Recipe objects.
bool compareRecipeTypes(const Recipe& first, const Recipe& second)
{
	unsigned int i = 0;
	while ((i < first.getRecipeType().length()) && (i < second.getRecipeType().length()))
	{
		if (tolower(first.getRecipeType()[i]) < tolower(second.getRecipeType()[i]))
			return true;
		else if (tolower(first.getRecipeType()[i]) > tolower(second.getRecipeType()[i]))
			return false;
		i++;
	}
	return (first.getRecipeType().length() < second.getRecipeType().length());
}

// Comparator by servingCount for two Recipe objects.
bool compareServingCounts(const Recipe& first, const Recipe& second)
{
	return (first.getServingCount() < second.getServingCount());
}

// Sort the list<IngredientInRecipe> by column indicated in front end.
void sortRecipeIngredients(int byCol, list<IngredientInRecipe>& lst)
{
	switch (byCol)
	{
	case 0:
		lst.sort(compareIngredientInRecipeNames);
		break;
	case 1:
		lst.sort(compareIngredientInRecipeQuantity);
		break;
	case 2:
		lst.sort(compareIngredientInRecipeUnits);
		break;
	default:
		break;
	}
}

// Comparator by name for two IngredientInRecipe objects.
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

// Comparator by quantity for two IngredientInRecipe objects.
bool compareIngredientInRecipeQuantity(const IngredientInRecipe& first, const IngredientInRecipe& second)
{

	return (first.getIngredientQuantity() < second.getIngredientQuantity());
}

// Comparator by Unit for two IngredientInRecipe objects.
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

/*
// Determines if a Recipe object exists in list<Recipe> by name.
bool doesRecipeExist(string& name, list<Recipe>& lst)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& r : lst)
	{
		if (r.getName() == name)
			return true;
	}
	return false;
}*/

// Returns the reference to Recipe object by name in list<Recipe>.
Recipe& getRecipeInList(string& name, list<Recipe>& lst)
{
	// WILL I NEED REMOVE COMMAS WHEN GETTING NAME FROM THE LIST?

	for (auto& r : lst)
	{
		if (r.getName() == name)
			return r;
	}
	return lst.front();
}