#include "Units.h"
#include <iostream>
#ifdef __WXMSW__
#include <wx/msw/msvcrt.h>      // redefines the new() operator 
#endif
void GetUnitStringList(list<string>& str)
{
	for (int i = 0; i < 16; i++)
		str.push_back(STR_UNIT[i]);
}

bool Units::operator == (const Units& u) const
{
	return unit == u.unit;
}

bool Units::operator != (const Units& u) const
{

	return !operator==(u);
}

// conversion function definitions
bool doesTypeMatchForConversion(Type from, Type to)
{
	if (from == to)
		return true;	
	return false;
}

double standardUnitConversion(Unit start, Unit end, double value)
{
	// increment if we are going up in scale, ounce to pounds
	while (start != end)
	{
		if (start < end)
		{
			value *= UNIT_CONVERSION_VALUES[int(start)];
			start = Unit(int(start) + 1);
		}
		// decrement if we are going down in scale, pounds to ounce.
		else if (start > end)
		{
			value /= UNIT_CONVERSION_VALUES[int(start) - 1];
			start = Unit(int(start) - 1);
		}
	}
	return value;
}


// Units class function definitions
Units::Units(){}

 Units::Units(string& u)
{
	// set the unitStr value in all caps.
	// WILL toupper AND COMMA REMOVAL BE REQUIRED WHEN USING DROPDOWN BOXES?
	for (auto& s : u)
	{
		if (s == ',')
			s = ' ';
		s = toupper(s);
	}
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

void Units::setType(int t)
{
	switch (t)
	{
		// if u is POUND, OUNCEWEIGHT, KILOGRAM, GRAM
		// then thisType == WEIGHT	
		case static_cast<int>(Unit::POUND) :
		case static_cast<int>(Unit::OUNCEWEIGHT) :
		case static_cast<int>(Unit::KILOGRAM) :
		case static_cast<int>(Unit::GRAM) :
			type = Type::WEIGHT;
			break;

		// if u is GALLON, HALFGALLON, QUART, PINT, CUP OUNCEFLUID, TABLESPOON, TEASPOON, LITER, MILLILITER
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

		// if u is EACH
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
	// set the string of StrType to 
	typeStr = STR_TYPE[static_cast<int>(type)];
	typeStrIndex = static_cast<int>(type);
}

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

string Units::getUnitStr() const
{
	return unitStr;
}


Unit Units::getUnit()
{
	return unit;
}


string Units::getTypeStr()
{
	return typeStr;
}


Type Units::getType()
{
	return type;
}
