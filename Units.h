#pragma once
#ifndef UNITS_H
#define UNITS_H
#include<string>
#include<list>
using namespace std;


// constants for enums Unit and Type
const string STR_UNIT[] = { "NONE", "GRAM", "OUNCEWEIGHT", "POUND", "KILOGRAM",
                                            "MILLILITER", "TEASPOON", "TABLESPOON", "OUNCEFLUID",
                                            "CUP","PINT", "QUART", "LITER", "GALLON",
                                            "EACH", "DOZEN" };
const string STR_TYPE[] = { "NONE", "WEIGHT", "VOLUME", "COUNT", };

// push onto the referenced list parameter available unit strings
void GetUnitStringList(list<string>& str);

// enumerator that define the Unit values
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

};

// enumerator that define the Type values
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
    // make Units objects comparable based on Unit enum values
    bool operator == (const Units& u) const;
    // make Units objects comparable based on Unit enum values
    bool operator != (const Units& u) const;
    // defines empty Units object
    Units();
    // defines a Units object based on a valid string parameter
    Units(string& unit);
    // sets the Units object to a specified Units based on valid string parameter
    // this in turn sets the Units Type enum to its corresponding Type, handled internally
    void setUnit(string& unit);
    // returns the string value of the Units object
    string getUnitStr() const;
    // returns the Units enum value
    Unit getUnit();
    // returns the Units' Type string value of the Units object
    string getTypeStr();
    // returns the Units' Type enum value of the Units object
    Type getType();

};

// compares the Type enum value for two Units objects to determine if they are convertible units of measure
bool doesTypeMatchForConversion(Type from, Type to);
// converts the Units object's unit values if they are convertible.
// CUP -> GALLON and vice versa, cannot convert GALLON -> POUND as they are two different Type values
double standardUnitConversion(Unit start, Unit end, float value);

// index zero represents converting from Unit a to Unit b.
// in this case, NONE is unconvertible, so we give it a value of -1.
// this includes mismatch type conversions, such as from KILOGRAM to MILLILITER

// to convert incrementally, match the start Unit enum with its respective index value in UNIT_CONVERSION_VALUES
// ounce to pounds, get index 2, which is OUNCEWEIGHT's enum, and MULTIPLY the value to be converted by the value at index
// to convert decrementally, match the start Unit enum - 1 with its respective index value.
// pounds to ounce, get index 3 - 1, which is POUND's enum - 1, and DIVIDE the value to be converted by the value at index
const double UNIT_CONVERSION_VALUES[] = { -1, 0.035274, 0.0625, 0.453592, -1, 0.202884, 0.3333333, 0.5, 0.125, 0.5, 0.5, 0.9463534, 0.264172, -1, 0.0833333, -1 };


#endif