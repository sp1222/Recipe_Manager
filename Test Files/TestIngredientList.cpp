#include "TestIngredientList.h"


void runIngredientListTest()
{
	cout << "Testing IngredientList Class:" << endl;
	cout << "\nConducting a correct test:" << endl;

	string name1 = "Beef Jerky", name2 = "Eggs, Liquid", name2a = "Eggs Liquid", name3 = "Roast Beef", name4 = "Shrimp";
	string desc1 = "Beefy Snack", desc2 = "Eggs, Liquid, Whole", desc3 = "Sandwich meat", desc4 = "crustacean";
	string cat1 = "Protein", cat2 = "Eggs", cat3 = "Beef", cat4 = "Seafood";
	string cfile = "testCategoryFile.csv";
	list<Category> categories;
	loadCategoryList(cfile, categories);
	string ifile = "testIngredientFile.csv";
	list<Ingredient> ingredients;

	cout << "Calling ingredients.size():  " << (ingredients.size() == 0 ? "Pass" : "Fail") << endl;

	addIngredient(name1, desc1, getCategoryInList(cat1, categories), ingredients);
	cout << "Calling addIngredient(name1, desc1, getCategoryInList(cat1, categories), categories):  " << (ingredients.size() == 1 ? "Pass" : "Fail") << endl;
	cout << "Calling getIngredientInList(name1, ingredients).getName():  " << (getIngredientInList(name1, ingredients).getName() == name1 ? "Pass" : "Fail") << endl;
//	cout << name1 << endl;
//	cout << getIngredientInList(name1, ingredients).getName() << endl << endl;

	addIngredient(name2, desc2, getCategoryInList(cat2, categories), ingredients);
	cout << "Calling addIngredient(name2, desc2, getCategoryInList(cat2, categories), categories):  " << (ingredients.size() == 2 ? "Pass" : "Fail") << endl;
	// fail case
	cout << "Calling getIngredientInList(name2, ingredients).getName() <Expecting to fail>:  " << (getIngredientInList(name2, ingredients).getName() == name2 ? "Pass" : "Fail") << endl;
//	cout << name2 << endl;
//	cout << getIngredientInList(name2a, ingredients).getName() << endl << endl;

	addIngredient(name3, desc3, getCategoryInList(cat3, categories), ingredients);
	cout << "Calling addIngredient(name3, desc3, getCategoryInList(cat3, categories), categories):  " << (ingredients.size() == 3 ? "Pass" : "Fail") << endl;
	cout << "Calling doesIngredientExist(name3, ingredients):  " << (doesIngredientExist(name3, ingredients) == true ? "Pass" : "Fail") << endl;
//	cout << name3 << endl;
//	cout << getIngredientInList(name3, ingredients).getName() << endl << endl;

	addIngredient(name4, desc4, getCategoryInList(cat4, categories), ingredients);
	cout << "Calling addIngredient(name4, desc4, getCategoryInList(cat4, categories), categories):  " << (ingredients.size() == 4 ? "Pass" : "Fail") << endl;
//	cout << name4 << endl;
//	cout << getIngredientInList(name4, ingredients).getName() << endl << endl;

	cout << "Calling getIngredientInList(name4, ingredients):  " << (getIngredientInList(name4, ingredients).getName() == name4 ? "Pass" : "Fail") << endl;

	removeIngredient(name4, ingredients);
	cout << "Calling removeIngredient(name4, ingredients):  " << (ingredients.size() == 3 ? "Pass" : "Fail") << endl;
	removeIngredient(name3, ingredients);
	cout << "Calling removeIngredient(name3, ingredients):  " << (ingredients.size() == 2 ? "Pass" : "Fail") << endl;
	removeIngredient(name2, ingredients);
	cout << "Calling removeIngredient(name2, ingredients):  " << (ingredients.size() == 2 ? "Pass" : "Fail") << endl;
	removeIngredient(name2a, ingredients);
	cout << "Calling removeIngredient(name2a, ingredients):  " << (ingredients.size() == 1 ? "Pass" : "Fail") << endl;
	removeIngredient(name1, ingredients);
	cout << "Calling removeIngredient(name1, ingredients):  " << (ingredients.size() == 0 ? "Pass" : "Fail") << endl;

	loadIngredientList(ifile, ingredients, categories);
	cout << "Calling ingredients.size():  " << (ingredients.size() == 8 ? "Pass" : "Fail") << endl;

	ingredients.empty();

	/*

	cout << "Creating IngredientList instance " << endl;
	string ingredFile = "testIngredientFile.csv";
	IngredientList ingredients(ingredFile);
	string file = "testCategoryFile.csv";
	CategoryList categories(file);
	categories.loadCategoryList();

	cout << "Calling getSize():  " << (ingredients.getSize() == 0 ? "Pass" : "Fail") << endl;
	ingredients.addIngredient(a, b, c, categories);
	cout << "Calling addIngredient(a, b, c, categories):  " << (ingredients.getSize() == 1 ? "Pass" : "Fail") << endl;
	ingredients.addIngredient(a, b, c, categories);
	cout << "Calling addIngredient(a, b, c, categories):  " << (ingredients.getSize() == 1 ? "Pass" : "Fail") << endl;
	ingredients.addIngredient(d, e, f, categories);
	cout << "Calling addIngredient(d, e, f, categories):  " << (ingredients.getSize() == 2 ? "Pass" : "Fail") << endl;
	ingredients.addIngredient(g, h, i, categories);
	cout << "Calling addIngredient(g, h, i, categories):  " << (ingredients.getSize() == 3 ? "Pass" : "Fail") << endl;

	string x = "Smoked Salmon", y = "Smokey", z = "pantry";
	cout << "Calling doesIngredientExist(a):  " << (ingredients.doesIngredientExist(a) == true ? "Pass" : "Fail") << endl;
	cout << "Calling doesIngredientExist(x):  " << (ingredients.doesIngredientExist(x) == false ? "Pass" : "Fail") << endl;

	// NOTE: smoked salmon fails to be added when the category does not exist.
	ingredients.addIngredient(x, y, z, categories);
	cout << "Calling addIngredient(x, y, z, categories):  " << (ingredients.getSize() == 4 ? "Pass" : "Fail") << endl;
	cout << ingredients.getIngredientInList(x).getCategoryStr() << endl;
	cout << "Calling ingredients.getIngredientInList(x).getCategoryStr():  " << (ingredients.getIngredientInList(x).getCategoryStr() == "NONE" ? "Pass" : "Fail") << endl;


	// here we test saving and loadinglists.
	ingredients.saveIngredientList();
	ingredients.removeIngredient(y);
	cout << "Calling removeIngredient(y):  " << (ingredients.getSize() == 4 ? "Pass" : "Fail") << endl;
	ingredients.removeIngredient(x);
	cout << "Calling removeIngredient(x):  " << (ingredients.getSize() == 3 ? "Pass" : "Fail") << endl;
	ingredients.removeIngredient(a);
	cout << "Calling removeIngredient(a):  " << (ingredients.getSize() == 2 ? "Pass" : "Fail") << endl;
	ingredients.removeIngredient(d);
	cout << "Calling removeIngredient(d):  " << (ingredients.getSize() == 1 ? "Pass" : "Fail") << endl;
	ingredients.removeIngredient(g);
	cout << "Calling removeIngredient(g):  " << (ingredients.getSize() == 0 ? "Pass" : "Fail") << endl;

	fstream fin;
	fin.open(file);
	cout << "Calling saveIngredientList():  " << (fin.is_open() == true ? "Pass" : "Fail") << endl;
	fin.close();
	ingredients.loadIngredientList(categories);
	cout << "Calling loadIngredientList():  " << (ingredients.getSize() == 4 ? "Pass" : "Fail") << endl;
	*/
}
