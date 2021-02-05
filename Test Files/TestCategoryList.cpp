#include "TestCategoryList.h"


void runCategoryListTest()
{
	string a = "PROTEIN", b = "FRUIT", c = "protein", d = "seafood", n = "none";

	cout << "Creating CategoryList instance " << endl;
	string file = "testCategoryFile.csv";
	list<Category> categories;
	addCategory(n, categories);


	cout << "Calling size():  " << (categories.size() == 1 ? "Pass" : "Fail") << endl;
	addCategory(a, categories);
	cout << "Calling addCategory(a):  " << (categories.size() == 2 ? "Pass" : "Fail") << endl;
	addCategory(a, categories);
	cout << "Calling addCategory(a):  " << (categories.size() == 2 ? "Pass" : "Fail") << endl;
	addCategory(b, categories);
	cout << "Calling addCategory(b):  " << (categories.size() == 3 ? "Pass" : "Fail") << endl;
	cout << "Calling doesCategoryExist(a):  " << (doesCategoryExist(a, categories) == true ? "Pass" : "Fail") << endl;
	cout << "Calling doesCategoryExist(b):  " << (doesCategoryExist(b, categories) == true ? "Pass" : "Fail") << endl;
	cout << "Calling doesCategoryExist(c):  " << (doesCategoryExist(c, categories) == false ? "Pass" : "Fail") << endl;
	cout << "Calling getCategoryInList(a):  " << (getCategoryInList(a, categories) == a ? "Pass" : "Fail") << endl;

	// here we test saving and loadinglists.
	saveCategoryList(file, categories);


	removeCategory(a, categories);
	cout << "Calling addCategory(a):  " << (categories.size() == 2 ? "Pass" : "Fail") << endl;
	removeCategory(b, categories);
	cout << "Calling addCategory(b):  " << (categories.size() == 1 ? "Pass" : "Fail") << endl;
	removeCategory(n, categories);
	cout << "Calling addCategory(n):  " << (categories.size() == 1 ? "Pass" : "Fail") << endl;

	loadCategoryList(file, categories);
	cout << "Calling loadCategoryList():  " << (categories.size() == 3 ? "Pass" : "Fail") << endl;
	
	removeCategory(n, categories);
	cout << "Calling removeCategory(none):  " << (categories.size() == 3 ? "Pass" : "Fail") << endl;
	removeCategory(a, categories);
	cout << "Calling removeCategory(a):  " << (categories.size() == 2 ? "Pass" : "Fail") << endl;
	removeCategory(d, categories);
	cout << "Calling removeCategory(b):  " << (categories.size() == 2 ? "Pass" : "Fail") << endl;

	categories.empty();
}
