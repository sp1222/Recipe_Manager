#include "TestIngredient.h"
#include<iostream>
using namespace std;


void runIngredientTest()
{
	cout << "Creating CategoryList instance" << endl;
	string file = "testCategoryFile.csv";
	string ingred1 = "Brisket", ingred2 = "Cheese", ingred3 = "Salmon";
	string ingredDesc1 = "Tough beef good for slow cooking", ingredDesc2 = "great on top of pizza", ingredDesc3 = "delicious when smoked";
	string cat1 = "None", cat2 = "Dairy", cat3 = "Protein";
	Category category1(cat1), category2(cat2), category3(cat3);
	cout << "category1:  " << category1.getCategory() << endl;
	cout << "category2:  " << category2.getCategory() << endl;
	cout << "category3:  " << category3.getCategory() << endl;

	Ingredient ingredient1(ingred1, ingredDesc1, category1);
	Ingredient ingredient2;
	ingredient2.setName(ingred2);
	ingredient2.setDescription(ingredDesc2);
	ingredient2.setCategory(category2);

	cout << "Calling ingredient1.getName():  " << (ingredient1.getName() == ingred1 ? "Pass" : "Fail") << endl;
	cout << "Calling ingredient1.getDescription():  " << (ingredient1.getDescription() == ingredDesc1 ? "Pass" : "Fail") << endl;
	cout << "Calling ingredient1.getCategoryStr():  " << (ingredient1.getCategoryStr() == cat1 ? "Pass" : "Fail") << endl;
	cout << "Calling ingredient1.getCategoryObj():  " << (&(ingredient1.getCategoryObj()) == &category1 ? "Pass" : "Fail") << endl;


	cout << "Calling ingredient2.getName():  " << (ingredient2.getName() == ingred2? "Pass" : "Fail") << endl;
	cout << "Calling ingredient2.getDescription():  " << (ingredient2.getDescription() == ingredDesc2 ? "Pass" : "Fail") << endl;
	cout << "Calling ingredient2.getCategoryStr():  " << (ingredient2.getCategoryStr() == cat2 ? "Pass" : "Fail") << endl;
	cout << "Calling ingredient2.getCategoryObj():  " << (&(ingredient2.getCategoryObj()) == &category2 ? "Pass" : "Fail") << endl;




}
