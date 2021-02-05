#include "TestRecipeList.h"

void runRecipeListTest()
{
	list<Category> categories;
	string catFile = "testCategoryFile.csv";
	loadCategoryList(catFile, categories);
	list<Ingredient> ingredients;
	string ingredFile = "testIngredientFile.csv";
	loadIngredientList(ingredFile, ingredients, categories);
	list<Recipe> recipes;
	cout << "Calling recipes.size():  " << (recipes.size() == 0 ? "Pass" : "Fail") << endl;

	list<pair<string, int>> mealTypes;
	string name1 = "first recipe", desc1 = "this is a tasty recipe", direct1 = "step 1.  first, mix.  step 2. bake.", type1 = "dessert", unitStr1 = "OUNCEWEIGHT";
	int serving1 = 12, yield1 = 4;
	addMealType(type1, mealTypes);
	addRecipe(name1, desc1, direct1, serving1, yield1, unitStr1, type1, mealTypes, recipes);
	cout << "Calling recipes.size():  " << (recipes.size() == 1 ? "Pass" : "Fail") << endl;

	string name2 = "first recipe", desc2 = "this is a sour recipe", direct2 = "step 1.  first, mix.  step 2. bake.", type2 = "dessert", unitStr2 = "OUNCEWEIGHT";
	int serving2 = 12, yield2 = 4;
	addMealType(type2, mealTypes);
	addRecipe(name2, desc2, direct2, serving2, yield2, unitStr2, type2, mealTypes, recipes);
	cout << "Calling recipes.size():  " << (recipes.size() == 1 ? "Pass" : "Fail") << endl;

	string name3 = "Second recipe", desc3 = "this is a delicious recipe", direct3 = "step 1.  first, mix.  step 2. bake.", type3 = "snack", unitStr3 = "OUNCEWEIGHT";
	int serving3 = 3, yield3 = 1;
	Units unit(unitStr3);
	addMealType(type3, mealTypes);
	addRecipe(name3, desc3, direct3, serving3, yield3, unitStr3, type3, mealTypes, recipes);
	cout << "Calling recipes.size():  " << (recipes.size() == 2 ? "Pass" : "Fail") << endl;

	cout << "Calling doesRecipeExist(name1, recipes):  " << (doesRecipeExist(name1, recipes) ? "Pass" : "Fail") << endl;
	cout << "Calling getRecipeInList(name3, recipes).getName():  " << (getRecipeInList(name3, recipes).getName() == name3 ? "Pass" : "Fail") << endl;

	// add some ingredients to each recipe for file save/load testing.
	string ingredName1 = "Chicken Tenders", ingredName2 = "Eggs", ingredUnit1 = "EACH", ingredUnit2 = "OUNCEWEIGHT";
	float ingredQty1 = 4, ingredQty2 = 2;
	getRecipeInList(name1, recipes).addIngredientInRecipe(ingredName1, ingredQty1, ingredUnit1, ingredients);
	getRecipeInList(name1, recipes).addIngredientInRecipe(ingredName2, ingredQty2, ingredUnit2, ingredients);

	// test file saving here!
	string file = "testRecipeFile.csv";
	saveRecipeList(file, recipes);


	removeRecipe(name1, recipes);
	cout << "Calling removeRecipe(name1, recipes):  " << (recipes.size() == 1 ? "Pass" : "Fail") << endl;
	removeRecipe(name3, recipes);
	cout << "Calling removeRecipe(name3, recipes):  " << (recipes.size() == 0 ? "Pass" : "Fail") << endl;

	// fyi, need to load ingredients, mealtypes, categories before loading recipes.
	// test file loading here!
	loadRecipeList(file, recipes, ingredients, mealTypes);
	cout << "Calling recipes.size():  " << (recipes.size() == 2 ? "Pass" : "Fail") << endl;
}