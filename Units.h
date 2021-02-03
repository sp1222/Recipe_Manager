#pragma once
#ifndef UNITS_H
#define UNITS_H
#include<string>
using namespace std;
// question, what if we want to add measurements to this?

// constants for enums Unit and Type
const string STR_UNIT[] = { "NONE", "GRAM", "OUNCEWEIGHT", "POUND", "KILOGRAM",
                                            "MILLILITER", "TEASPOON", "TABLESPOON", "OUNCEFLUID",
                                            "CUP","PINT", "QUART", "LITER", "GALLON",
                                            "EACH", "DOZEN" };//, "STICK"};
const string STR_TYPE[] = { "NONE", "WEIGHT", "VOLUME", "COUNT", };

// enumerators that define the Unit and Unit Type.
enum class Unit
{
    NONE,
    GRAM,
    OUNCEWEIGHT,
    POUND,
    KILOGRAM,
    MILLILITER,
    TEASPOON,
    TABLESPOON,
    OUNCEFLUID,
    CUP,
    PINT,
    QUART,
    LITER,
    GALLON,
    EACH,
    DOZEN,
//    STICK
};

enum class Type
{
    NONE,
    WEIGHT,
    VOLUME,
    COUNT
};

// Units class for instances of units.
class Units
{
private:	
    Unit unit = Unit::NONE;
    Type type = Type::NONE;
    int unitStrIndex = 0;
    int typeStrIndex = 0;
    string unitStr = STR_UNIT[unitStrIndex];
    string typeStr = STR_TYPE[typeStrIndex];
    
    // private functions
    void setType(int t);

public:
    bool operator == (const Units& u) const;
    bool operator != (const Units& u) const;
    Units();
    Units(string& unit);
    void setUnit(string& unit);
    string getUnitStr();
    Unit getUnit();
    string getTypeStr();
    Type getType();

};

// prototype functions for conversions
bool doesTypeMatchForConversion(Type from, Type to);
float standardUnitConversion(Unit start, Unit end, float value);

/*
// constants for unit conversions
//weights
const float GRAM_TO_OUNCEWEIGHT = 0.0353;
const float OUNCEWEIGHT_TO_POUND = 0.0625;
const float POUND_TO_KILOGRAM = 0.4536;

// volumes
const float MILLILITER_TO_TEASPOON = 0.2029;
const float TEASPOON_TO_TABLESPOON = 0.3333;
const float TABLESPOON_TO_OUNCEFLUID = 0.5;
const float OUNCEFLUID_TO_CUP = 0.125;
const float CUP_TO_PINT = 0.5;
const float PINT_TO_QUART = 0.5;
const float QUART_TO_GALLON = 0.25;

// counts
const float EACH_TO_DOZEN = .0833;
*/

// index zero represents converting from Unit a to Unit b.
// in this case, NONE is unconvertible, so we give it a value of -1.
// this includes mismatch type conversions, such as from KILOGRAM to MILLILITER

// to convert incrementally, match the start Unit enum with its respective index value in UNIT_CONVERSION_VALUES
// ounce to pounds, get index 2, which is OUNCEWEIGHT's enum, and MULTIPLY the value to be converted by the value at index
// to convert decrementally, match the start Unit enum - 1 with its respective index value.
// pounds to ounce, get index 3 - 1, which is POUND's enum - 1, and DIVIDE the value to be converted by the value at index
const float UNIT_CONVERSION_VALUES[] = { -1, 0.035274, 0.0625, 0.453592, -1, 0.202884, 0.3333333, 0.5, 0.125, 0.5, 0.5, 0.9463534, 0.264172, -1, 0.0833333 };


#endif