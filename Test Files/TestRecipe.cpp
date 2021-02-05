
#include "TestRecipe.h"

void runRecipeTest()
{
	string catFile = "testCategoryFile.csv", ingredFile = "testIngredientFile.csv";
	list<Category> categories;
	loadCategoryList(catFile, categories);
	list<Ingredient> ingredients;
	loadIngredientList(ingredFile, ingredients, categories);
	list<pair<string, int>> mealTypes;
	string name = "first recipe", desc = "this is a tasty recipe", direct = "step 1.  first, mix.  step 2. bake.", type = "dessert", unitStr = "OUNCEWEIGHT";
	int serving = 12, yield = 4;
	Units unit(unitStr);
	addMealType(type, mealTypes);
	string ingred2 = "Eggs", ingredUnit = "POUND";
	float qty = 2.4;

	Recipe testRecipe;
	testRecipe.setName(name);
	cout << "Calling testRecipe.getName():  " << (testRecipe.getName() == name ? "Pass" : "Fail") << endl;
	testRecipe.setDescription(desc);
	cout << "Calling testRecipe.getDescription():  " << (testRecipe.getDescription() == desc ? "Pass" : "Fail") << endl;
	testRecipe.setDirection(direct);
	cout << "Calling testRecipe.getDirection():  " << (testRecipe.getDirection() == direct ? "Pass" : "Fail") << endl;
	testRecipe.setServingCount(serving);
	cout << "Calling testRecipe.getServingCount():  " << (testRecipe.getServingCount() == serving ? "Pass" : "Fail") << endl;
	testRecipe.setYield(yield);
	cout << "Calling testRecipe.getYield():  " << (testRecipe.getYield() == yield ? "Pass" : "Fail") << endl;
	testRecipe.setYieldUnit(unitStr);
	cout << "Calling testRecipe.getYieldUnitStr():  " << (testRecipe.getYieldUnitStr() == unitStr ? "Pass" : "Fail") << endl;
	cout << "Calling testRecipe.getYieldUnit():  " << (testRecipe.getYieldUnit() == unit ? "Pass" : "Fail") << endl;
	testRecipe.setMealType(type, mealTypes);
	cout << "Calling testRecipe.getMealType():  " << (testRecipe.getMealType() == type ? "Pass" : "Fail") << endl;
	testRecipe.addIngredientInRecipe(ingred2, qty, ingredUnit, ingredients);
	cout << "Calling testRecipe.getIngredientInRecipe(ingred2).getIngredientName():  " << (testRecipe.getIngredientInRecipe(ingred2).getIngredientName() == ingred2 ? "Pass" : "Fail") << endl;
	cout << "Calling testRecipe.getIngredientInRecipe(ingred2).getIngredientQuantity():  " << (testRecipe.getIngredientInRecipe(ingred2).getIngredientQuantity() == qty ? "Pass" : "Fail") << endl;
	cout << "Calling testRecipe.getIngredientInRecipe(ingred2).getIngredientUnitStr():  " << (testRecipe.getIngredientInRecipe(ingred2).getIngredientUnitStr() == ingredUnit ? "Pass" : "Fail") << endl;

}
