#include "TestMealType.h"
#include<iostream>

void runMealTypeTest()
{
	list<pair<string, int>> mealTypeList;
	string type1 = "dessert", type2 = "salad";
	addMealType(type1, mealTypeList);
	cout << "Calling mealTypeList.size(type1, mealTypeList):  " << (mealTypeList.size() == 1 ? "Pass" : "Fail") << endl;
	
	incrementRecipeUsingMealTypeCount(type1, mealTypeList);
	cout << "Calling incrementRecipeUsingMealTypeCount(type1, mealTypeList):  " << (getRecipeUsingMealTypeCount(type1, mealTypeList) == 1 ? "Pass" : "Fail") << endl;


	addMealType(type2, mealTypeList);
	cout << "Calling mealTypeList.size(type2, mealTypeList):  " << (mealTypeList.size() == 2 ? "Pass" : "Fail") << endl;
	cout << "doesMealTypeExist(type1, mealTypeList):  " << (doesMealTypeExist(type1, mealTypeList) == true ? "Pass" : "Fail") << endl;

	removeMealType(type1, mealTypeList);
	cout << "Calling mealTypeList.size(type1, mealTypeList):  " << (mealTypeList.size() == 1 ? "Pass" : "Fail") << endl;

}