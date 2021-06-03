/*
	Units.cpp
	Function definitions for Units.h
*/

#include "Units.h"

#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif

// Push onto the referenced list parameter available unit strings.
void GetUnitStringList(list<string>& str)
{
	for (int i = 0; i < 16; i++)
		str.push_back(STR_UNIT[i]);
}

// Set the Units object's Type value.
void Units::setType(int t)
{
	switch (t)
	{
		// if u is POUND, OUNCEWEIGHT, KILOGRAM, GRAM:
		// then thisType == WEIGHT	
		case static_cast<int>(Unit::POUND) :
			case static_cast<int>(Unit::OUNCEWEIGHT) :
			case static_cast<int>(Unit::KILOGRAM) :
			case static_cast<int>(Unit::GRAM) :
			type = Type::WEIGHT;
			break;

			// if u is GALLON, HALFGALLON, QUART, PINT, CUP OUNCEFLUID, TABLESPOON, TEASPOON, LITER, MILLILITER:
			// then thisType == VOLUME
			case static_cast<int>(Unit::GALLON) :
				//		case static_cast<int>(Unit::HALFGALLON) :
				case static_cast<int>(Unit::QUART) :
				case static_cast<int>(Unit::PINT) :
				case static_cast<int>(Unit::CUP) :
				case static_cast<int>(Unit::OUNCEFLUID) :
				case static_cast<int>(Unit::TABLESPOON) :
				case static_cast<int>(Unit::TEASPOON) :
				case static_cast<int>(Unit::LITER) :
				case static_cast<int>(Unit::MILLILITER) :
				type = Type::VOLUME;
				break;

				// if u is EACH:
				// then thisType == COUNT
				case static_cast<int>(Unit::EACH) :
					case static_cast<int>(Unit::DOZEN) :
					//		case static_cast<int>(Unit::STICK) :
					type = Type::COUNT;
					break;

					// else
					// thisType == NONE
					default:
						type = Type::NONE;
						break;
	}
	// set the string of StrType to.
	typeStr = STR_TYPE[static_cast<int>(type)];
	typeStrIndex = static_cast<int>(type);
}

//  Make Units objects comparable based on Unit enum values.
bool Units::operator == (const Units& u) const
{
	return unit == u.unit;
}

//  Make Units objects comparable based on Unit enum values.
bool Units::operator != (const Units& u) const
{

	return !operator==(u);
}

// Initialize a Units object of Unit "NONE" and Type "NONE".
Units::Units(){}

// Initialize a Units object based on a valid string parameter.
 Units::Units(string& u)
{
	// set the unitStr value in all caps.
	stringRemoveCommas(u);
	unitStr = u;

	// set the unit enum value.
	for (int i = 0; i < sizeof(STR_UNIT)/sizeof(STR_UNIT[0]); i++)
	{
		if (u == STR_UNIT[i])
		{
			unit = static_cast<Unit>(i);
			setType(i);
			unitStrIndex = i;
			break;
		}
	}	
}

// Redefine the Units object to a specified Units based on valid string parameter.
void Units::setUnit(string& u)
{
	// set the unitStr value in all caps.
	// WILL toupper AND COMMA REMOVAL BE REQUIRED WHEN USING DROPDOWN BOXES?  No, everything is pretty standardized here.

	unitStr = u;

	// set the unit enum value.
	for (int i = 0; i < sizeof(STR_UNIT) / sizeof(STR_UNIT[0]); i++)
	{
		if (u == STR_UNIT[i])
		{
			unit = static_cast<Unit>(i);
			setType(i);
			unitStrIndex = i;
			break;
		}
	}
}

// Returns the string value of the Units object.
string Units::getUnitStr() const
{
	return unitStr;
}

// Returns the Units enum value.
Unit Units::getUnit()
{
	return unit;
}

// Returns the Units' Type string value of the Units object.
string Units::getTypeStr()
{
	return typeStr;
}

// Returns the Units' Type enum value of the Units object.
Type Units::getType()
{
	return type;
}

// Compares the Type enum value for two Units objects to determine if they are convertible units of measure.
bool doesTypeMatchForConversion(Type from, Type to)
{
	if (from == to)
		return true;
	return false;
}

// Converts a quantity value of Unit start to Unit end.
// In this case, NONE is unconvertible, so we give it a value of -1..
// This includes mismatch type conversions, such as from KILOGRAM to MILLILITER.
// To convert incrementally, match the start Unit enum with its respective index value in UNIT_CONVERSION_VALUES.
// OUNCEWEIGHT to POUND, get index 2, which is OUNCEWEIGHT's enum, and multiply the value to be converted by the value at index.
// To convert decrementally, match the start Unit enum - 1 with its respective index value.
// POUND to OUNCEWEIGHT, get index 3 - 1, which is POUND's enum - 1, and divide the value to be converted by the value at index.
double standardUnitConversion(Unit start, Unit end, double value)
{
	// increment if we are going up in scale, OUNCEWEIGHT to POUND.
	while (start != end)
	{
		if (start < end)
		{
			value *= UNIT_CONVERSION_VALUES[int(start)];
			start = Unit(int(start) + 1);
		}
		// decrement if we are going down in scale, POUND to OUNCEWEIGHT.
		else if (start > end)
		{
			value /= UNIT_CONVERSION_VALUES[int(start) - 1];
			start = Unit(int(start) - 1);
		}
	}
	return value;
}