#include "TestIngredientInRecipe.h"

void runIngredientInRecipeTest()
{
	cout << "Testing IngredientList Class:" << endl;
	string catFile = "testCategoryFile.csv";
	string ingredFile = "testIngredientFile.csv";
	list<Category> categories;
	list<Ingredient> ingredients;
	loadCategoryList(catFile, categories);
	loadIngredientList(ingredFile, ingredients, categories);
	string ingredStr1 = "Chickn Wings", ingredStr2 = "Smoked Salmon";
	string unitStr1 = "Pound", unitStr2 = "seafood";
	float qty1 = 6.2, qty2 = 4.9;
	IngredientInRecipe recipeIngredient(ingredStr1, qty1, unitStr1, ingredients);

	cout << "Calling recipeIngredient.getIngredientName():  " << (recipeIngredient.getIngredientName() == ingredStr1 ? "Pass" : "Fail") << endl;
	cout << "Calling recipeIngredient.getIngredientQuantity():  " << (recipeIngredient.getIngredientQuantity() == qty1 ? "Pass" : "Fail") << endl;
	cout << "Calling recipeIngredient.unitStr1():  " << (recipeIngredient.getIngredientUnitStr() == unitStr1 ? "Pass" : "Fail") << endl;

	cout << "Reassigning recipeIngredient values..." << endl;
	recipeIngredient.setIngredient(getIngredientInList(ingredStr2, ingredients));
	recipeIngredient.setIngredientQuantity(qty2);
	recipeIngredient.setIngredientUnit(unitStr2);

	cout << "Calling recipeIngredient.getIngredientName():  " << (recipeIngredient.getIngredientName() == ingredStr2 ? "Pass" : "Fail") << endl;
	cout << "Calling recipeIngredient.getIngredientQuantity():  " << (recipeIngredient.getIngredientQuantity() == qty2 ? "Pass" : "Fail") << endl;
	cout << "Calling recipeIngredient.unitStr1():  " << (recipeIngredient.getIngredientUnitStr() == unitStr2 ? "Pass" : "Fail") << endl;

}
