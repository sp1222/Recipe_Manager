#include "Units.h"
#include<iostream>
using namespace std;

void runUnitsTest()
{
	cout << "Testing Units Class:" << endl;
	string uStr1 = "PoUnD", uStr2 = "OUNCEFLUID", uStr3 = "TEASPOON", uStr4 = "DOZEN";
	string tStr1 = "WEIGHT", tStr2 = "VOLUME", tStr3 = "COUNT";

	Units testUnit1(uStr1);
	for (auto& s : uStr1) s = toupper(s);
	Units testUnit2(uStr1);
	Units testUnit3(uStr3);
	Units testUnit4(uStr4);

	cout << "Calling testUnit1.getUnitStr():  " << (testUnit1.getUnitStr() == uStr1 ? "Pass" : "Fail") << endl;
	cout << "Calling testUnit1.getTypeStr():  " << (testUnit1.getTypeStr() == tStr1 ? "Pass" : "Fail") << endl;
	cout << "Calling testUnit1.getUnit():  " << (testUnit1.getUnit() == Unit::POUND ? "Pass" : "Fail") << endl;
	cout << "Calling testUnit1.getUnit():  " << (testUnit1.getType() == Type::WEIGHT ? "Pass" : "Fail") << endl;

	testUnit2.setUnit(uStr2);

	cout << "Calling testUnit2.setUnit(uStr2):  " << (testUnit2.getUnitStr() == uStr2 ? "Pass" : "Fail") << endl;
	cout << "Calling testUnit2.getTypeStr():  " << (testUnit2.getTypeStr() == tStr2 ? "Pass" : "Fail") << endl;
	cout << "Calling testUnit2.getUnit():  " << (testUnit2.getUnit() == Unit::OUNCEFLUID ? "Pass" : "Fail") << endl;
	cout << "Calling testUnit2.getUnit():  " << (testUnit2.getType() == Type::VOLUME ? "Pass" : "Fail") << endl;

	// here we test standard conversions.
	cout << "Calling doesTypeMatchForConversion(testUnit1.getType(), testUnit2.getType()):  " << (doesTypeMatchForConversion(testUnit1.getType(), testUnit2.getType()) == false ? "Pass" : "Fail") << endl;
	cout << "Calling doesTypeMatchForConversion(testUnit1.getType(), testUnit4.getType()):  " << (doesTypeMatchForConversion(testUnit1.getType(), testUnit4.getType()) == false ? "Pass" : "Fail") << endl;
	cout << "Calling doesTypeMatchForConversion(testUnit3.getType(), testUnit2.getType()):  " << (doesTypeMatchForConversion(testUnit3.getType(), testUnit2.getType()) == true ? "Pass" : "Fail") << endl;

	if (doesTypeMatchForConversion(testUnit1.getType(), testUnit2.getType()))
		cout << endl << "Calling if(doesTypeMatchForConversion(testUnit1.getType(), testUnit2.getType())):  Fail" << endl;
	else
		cout << endl << "Calling if(doesTypeMatchForConversion(testUnit1.getType(), testUnit2.getType())):  Pass" << endl;



	string unit[] = { "NONE", "GRAM", "OUNCEWEIGHT", "POUND", "KILOGRAM",
											"MILLILITER", "TEASPOON", "TABLESPOON", "OUNCEFLUID",
											"CUP","PINT", "QUART", "LITER", "GALLON",
											"EACH", "DOZEN" };//, "STICK"};


	cout << "*********************************************************************************" << endl << endl;
	for (int i = 0; i < sizeof(unit) / sizeof(unit[0]); i++)
	{
		Units iUnit(unit[i]);
		for (int j = i; j < sizeof(unit) / sizeof(unit[0]); j++)
		{
			Units jUnit(unit[j]);
			float currentValue = 1.0;
			float convertedValue = 0.0;
			if (doesTypeMatchForConversion(iUnit.getType(), jUnit.getType()))
			{
				cout << "\nConverting " << iUnit.getUnitStr() << " to " << jUnit.getUnitStr() << endl;
				convertedValue = standardUnitConversion(iUnit.getUnit(), jUnit.getUnit(), currentValue);
				cout << "currentValue:                                                            " << currentValue << endl;
				cout << "convertedValue:                                                          " << convertedValue << endl;
				cout << "standardUnitConversion(iUnit.getUnit(), jUnit.getUnit(), currentValue):  " << standardUnitConversion(iUnit.getUnit(), jUnit.getUnit(), currentValue) << endl;
			}
			else
			{
				cout << "\nUnconvertible types: " << endl;
				cout << "iUnit.getTypeStr():  " << iUnit.getTypeStr() << endl;
				cout << "jUnit.getTypeStr():  " << jUnit.getTypeStr() << endl;
			}
		}
	}

	cout << "*********************************************************************************" << endl << endl;
	for (int i = (sizeof(unit) / sizeof(unit[0])) - 1; i >= 0; i--)
	{
		Units iUnit(unit[i]);
		for (int j = i; j >= 0; j--)
		{
			Units jUnit(unit[j]);
			float currentValue = 1.0;
			float convertedValue = 0.0;
			if (doesTypeMatchForConversion(iUnit.getType(), jUnit.getType()))
			{
				cout << "\nConverting " << iUnit.getUnitStr() << " to " << jUnit.getUnitStr() << endl;
				convertedValue = standardUnitConversion(iUnit.getUnit(), jUnit.getUnit(), currentValue);
				cout << "currentValue:                                                            " << currentValue << endl;
				cout << "convertedValue:                                                          " << convertedValue << endl;
				cout << "standardUnitConversion(iUnit.getUnit(), jUnit.getUnit(), currentValue):  " << standardUnitConversion(iUnit.getUnit(), jUnit.getUnit(), currentValue) << endl;
			}
			else
			{
				cout << "\nUnconvertible types: " << endl;
				cout << "iUnit.getTypeStr():  " << iUnit.getTypeStr() << endl;
				cout << "jUnit.getTypeStr():  " << jUnit.getTypeStr() << endl;
			}
		}
	}


	/*
	if (doesTypeMatchForConversion(testUnit3.getType(), testUnit2.getType()))
	{
		cout << endl << "Calling if(doesTypeMatchForConversion(testUnit3.getType(), testUnit2.getType())):  Pass" << endl;
		convertedValue = standardUnitConversion(testUnit3.getUnit(), testUnit2.getUnit(), currentValue);
		float newCurrentValue = currentValue * 0.3333 * 0.5;
		cout << endl <<  "convertedValue:  " << convertedValue << endl;
		cout << "newCurrentValue:  " << newCurrentValue << endl;
		cout << "standardUnitConversion(testUnit3.getUnit(), testUnit2.getUnit(), currentValue):  " << standardUnitConversion(testUnit3.getUnit(), testUnit2.getUnit(), currentValue) << endl << endl;
		cout << (convertedValue == newCurrentValue) << endl;
		cout << "Calling standardUnitConversion(testUnit3.getUnit(), testUnit2,getUnit(), currentValue):  " << (convertedValue == newCurrentValue ? "Pass" : "Fail" ) << endl;

	}
	else
		cout << endl << "Calling if(doesTypeMatchForConversion(testUnit3.getType(), testUnit2.getType())):  Fail" << endl;


	if (doesTypeMatchForConversion(testUnit2.getType(), testUnit3.getType()))
	{
		cout << endl << "Calling if(doesTypeMatchForConversion(testUnit2.getType(), testUnit3.getType())):  Pass" << endl;
		convertedValue = standardUnitConversion(testUnit2.getUnit(), testUnit3.getUnit(), currentValue);
		float newCurrentValue = currentValue / 0.5 / 0.3333;
		cout << endl << "convertedValue:  " << convertedValue << endl;
		cout << "newCurrentValue:  " << newCurrentValue << endl;
		cout << "standardUnitConversion(testUnit2.getUnit(), testUnit3.getUnit(), currentValue):  " << standardUnitConversion(testUnit2.getUnit(), testUnit3.getUnit(), currentValue) << endl << endl;
		cout << (convertedValue == newCurrentValue) << endl;
		cout << "Calling standardUnitConversion(testUnit2.getUnit(), testUnit3,getUnit(), currentValue):  " << (convertedValue == newCurrentValue ? "Pass" : "Fail") << endl;


	}
	else
		cout << endl << "Calling if(doesTypeMatchForConversion(testUnit2.getType(), testUnit3.getType())):  Fail" << endl;
*/
}