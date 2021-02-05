#include "TestCategory.h"
#include "Ingredient.h"

void runCategoryTest()
{
	cout << "Creating Category instance " << endl;
	string a = "NONE";
	Category testCategory(a);
	for (auto& s : a) s = toupper(s);
//	string name = "chicken", desc = "lean protein";
// 	Ingredient testIngred(name, desc, testCategory);


	cout << "Calling getCategory():  " << (testCategory.getCategory() == a ? "Pass" : "Fail") << endl;
	cout << "Calling testCategory.getIngredientsUsingCategoryCount():  " << (testCategory.getIngredientsUsingCategoryCount() == 0 ? "Pass" : "Fail") << endl;
	
	testCategory.incrementIngredientsUsingCategoryCount();
	cout << "Calling testCategory.incrementIngredientsUsingCategoryCount():  " << (testCategory.getIngredientsUsingCategoryCount() == 1 ? "Pass" : "Fail") << endl;


	testCategory.decrementIngredientsUsingCategoryCount();
	cout << "Calling testCategory.decrementIngredientsUsingCategoryCount(&testIngred):  " << (testCategory.getIngredientsUsingCategoryCount() == 0 ? "Pass" : "Fail") << endl;





//	cout << "reference:  " << &testCategory << endl;
//	testCategory.addIngredientUsingCategory(&testIngred);
//	testCategory.incrementIngredientsUsingCategoryCount();
//	cout << "Calling addIngredientUsingCategory(&testIngred):  " << (testCategory.getIngredientsUsingCategoryCount() == 1 ? "Pass" : "Fail") << endl;

	//	testCategory.incrementIngredientsUsingCategoryCount();
//	cout << "reference:  " << &testCategory << endl;

//	testCategory.removeIngredientUsingCategory(&testIngred);
//	testCategory.decrementIngredientsUsingCategoryCount();
//	cout << "Calling removeIngredientUsingCategory(&testIngred):  " << (testCategory.getIngredientsUsingCategoryCount() == 0 ? "Pass" : "Fail") << endl;




}
