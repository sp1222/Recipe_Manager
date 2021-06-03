/*
    Units.h
    Defines a Units class, conducts valid conversion from one unit to another unit.
*/

#pragma once
#ifndef UNITS_H
#define UNITS_H

#include <list>
#include <string>

#include "Helpers.h"

using namespace std;

/*
    Constants for string values of Unit.
*/
const string STR_UNIT[] = { "NONE", "GRAM", "OUNCEWEIGHT", "POUND", "KILOGRAM",
                                            "MILLILITER", "TEASPOON", "TABLESPOON", "OUNCEFLUID",
                                            "CUP","PINT", "QUART", "LITER", "GALLON",
                                            "EACH", "DOZEN" };

/*
    Constants for string values of Type.
*/
const string STR_TYPE[] = { "NONE", "WEIGHT", "VOLUME", "COUNT", };

/* 
    Push onto the referenced list parameter available unit strings.
    @param str : reference to list of strings.
*/
void GetUnitStringList(list<string>& str);

/* 
    Enumerator that define the Unit values.
*/
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

/*
    Enumerator that define the Type values.
*/
enum class Type
{
    NONE,
    WEIGHT,
    VOLUME,
    COUNT
};

/*
    Units class for instances of Units objects.
*/
class Units
{
private:	
    Unit unit = Unit::NONE;
    Type type = Type::NONE;
    int unitStrIndex = 0;
    int typeStrIndex = 0;
    string unitStr = STR_UNIT[unitStrIndex];
    string typeStr = STR_TYPE[typeStrIndex];

    /*
        Set the Units object's Type value.
        @param t : integer value representing Type enum.
    */
    void setType(int t);

public:
    /*
        Make Units objects comparable based on Unit enum values.
        @param u : constant reference to Units object.
        @return : If object matches this instance of a Units.
    */
    bool operator == (const Units& u) const;

    /*
        Make Units objects comparable based on Unit enum values.
        @param u : constant reference to Units object.
        @return : If object does not match this instance of a Units.
    */
    bool operator != (const Units& u) const;

    /*
        Initialize a Units object of Unit "NONE" and Type "NONE".
    */
    Units();

    /*
        Initialize a Units object based on a valid string parameter.
        @param unit : reference to string indicating the unit's definition.
    */
    Units(string& unit);

    /*
        Redefine the Units object to a specified Units based on valid string parameter.
        This in turn sets the Units Type enum to its corresponding Type, handled internally.
        @param unit : reference to string indicating the unit's definition.
    */
    void setUnit(string& unit);

    /*
        Returns the string value of the Units object.
        @return : String value of this Units object.
    */
    string getUnitStr() const;

    /*
        Returns the Units enum value.
        @return : The enum value of this Units object.
    */
    Unit getUnit();

    /*
        Returns the Units' Type string value of the Units object.
        @return : Units' Type string value of this Units object.
    */
    string getTypeStr();

    /*
        Returns the Units' Type enum value of the Units object.
        @return : Units' Type enum value of this Units object.
    */
    Type getType();

};

/*
    Compares the Type enum value for two Units objects to determine if they are convertible units of measure.
    @param from : Type of Units object being converted from.
    @param to : Type of Units object being converted to.
    @return : If the Units object is convertible from one Units object to another Units object.
*/
bool doesTypeMatchForConversion(Type from, Type to);

/*
    Converts a quantity value of Unit start to Unit end.
    Converts the Units object's unit values if they are convertible.
    CUP -> GALLON and vice versa, cannot convert GALLON -> POUND as they are two different Type values.
    @param start : the starting Unit enum value.
    @param end : the ending Unit enum value.
    @param value : the quantity value to be converted.
    @return : The converted quantity value.
*/
double standardUnitConversion(Unit start, Unit end, double value);

/*
    unit conversion values, in order of enum class Unit.
*/
const double UNIT_CONVERSION_VALUES[] = { -1, 0.035274, 0.0625, 0.453592, -1, 0.202884, 0.3333333, 0.5, 0.125, 0.5, 0.5, 0.9463534, 0.264172, -1, 0.0833333, -1 };


#endif