#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

//tells if the string has an upper case or not
bool hasUpper (std::string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (isupper(input[i]))
		{
			return true;
		}
	}

	return false;
}

bool hasColon (std::string input)
{
	if (input.find(":") != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

bool curlyAndSpaceChecker(std::string input)
{
	if(input.length() < 3 || input[input.length()-1] != '{')
		return false;

	int curlyPosition = input.find("{");
	if (input[curlyPosition-1] == ' ' && input[curlyPosition-2] != ' ')
	{
		return true;
	}
	else 
		return false;

}

bool endsEmptySpace(std::string input)
{
	if (input.length() == 0)
	{
		return false;
	}
	if (input[input.length()-1] == ' ')
	{
		return true;
	}
	else 
		return false;
}

bool startsEmptySpace(std::string input)
{
	if (input[0] == ' ')
	{
		return true;
	}
	else 
		return false;
}

//tells us if the line we are looking at is a selector
bool hasSelector (std::string input)
{
	if (input.length() == 0)
		return false;

	if (input.find("{") != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

bool hasClosingSelector (std::string input) //tells you when you find a closing selector }
{
	if (input.length() == 0)
		return false;

	if (input.find("}") != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

bool hasProperSelectorFormat(std::string input) //guaranteed it wont recieve a null input
{
	if (hasUpper(input) || startsEmptySpace(input))
	{
		return false;
	}

	if (curlyAndSpaceChecker(input))
	{
		return true;
	}

	return false;
}

bool hasProperClosingSelectorFormat(std::string input) //guaranteed it wont recieve a null input
{
	if (input.length() > 1)
	{
		return false;
	}
	else 
		return true;
}

string getProperty(std::string input)
{
	if (input.length() == 0)
	{
		return "";
	}

	size_t colonPosition = input.find(":");
	if (colonPosition != std::string::npos) //return everything up to the :
	{
		return input.substr(0, colonPosition);
	}
	else //couldn't find a : inside the line
		return "";


}

string getPropertyValue(std::string input)
{
	if (input.length() == 0)
	{
		return "";
	}

	size_t colonPosition = input.find(":");
	if (colonPosition != std::string::npos) //return everything up to the :
	{
		return input.substr(colonPosition+1);
	}
	else //couldn't find a : inside the line
		return "";
}

bool hasProperPropertyAndValueFormat(std::string input)
{
	if (input.length() == 0)
	{
		return false;
	}

	if (hasUpper(input))
	{
		return false;
	}

	return true;
}

int findIndentation(std::string input) //finds how many spaces there are in the line before the text
{
	int count = 0;
	int i = 0;
	
	while(input[i] == ' ')
	{
		count++;
		i++;
	}

	return count;
}

bool isConjunctionSelector(std::string input) //tells you if you have a conjunction of element names and Ids/classes
{
	if(input.length() == 0)
	{
		return false;
	}

	size_t foundPeriod = input.find('.');
	size_t foundHash = input.find('#');
	//return false true we find a . or # within the selector AND its not at the beginning
	if ((foundPeriod != std::string::npos && foundPeriod!=0) || (foundHash != std::string::npos && foundHash!=0))
	{
		return true;
	}
	else
		return false;
}

bool isIDSelector (std::string input)
{
	if (input.length() == 0)
	{
		return false;
	}

	if (input[0] == '#')
	{
		return true;
	}
	else
		return false;
}

bool shouldAddToSet(std::string input) //tells you if you should add an item to the set
{
	if (input.length() == 0)
	{
		return false;
	}

	if (input.find("background") != std::string::npos || input.find("border")!= std::string::npos
		|| input.find("margin")!= std::string::npos || input.find("overflow")!= std::string::npos
		|| input.find("padding")!= std::string::npos || input.find("list-style")!= std::string::npos
		|| input.find("animation")!= std::string::npos || input.find("transition")!= std::string::npos)
	{
		return true;
	}
	else
		return false;
}

string shorthandToAdd (string input) //tells you which string to add to the set
{
	if (input.find("background") != std::string::npos)
	{
		return "background";
	}
	else if (input.find("border")!= std::string::npos)
	{
		return "border";
	}
	else if (input.find("margin")!= std::string::npos)
	{
		return "margin";
	}
	else if (input.find("overflow")!= std::string::npos)
	{
		return "overflow";
	}
	else if (input.find("padding")!= std::string::npos)
	{
		return "padding";
	}
	else if (input.find("list-style")!= std::string::npos)
	{
		return "list-style";
	}
	else if (input.find("animation")!= std::string::npos)
	{
		return "animation";
	}
	else if (input.find("transition")!= std::string::npos)
	{
		return "transition";
	}
	else
		return "";
}


int howManyNum(std::string input) //will be used in isZeroandUnits
{
	int count = 0;
	for (int i = 0; i < input.length(); i++)
	{
		if (isdigit(input[i]))
		{
			count++;
		}
	}
	return count;
}

bool hasZero(std::string input) 
{
	if (input.find("0") != std::string::npos)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

bool hasAlpha(std::string input)
{
	for (int i = 0; i < input.length(); i++)
	{
		if (isalpha(input[i]))
		{
			return true;
		}
	}
	return false;
}

bool isZeroAndUnits(std::string propertyValue) //tells you if you have something like margin: 0em;
{
	if (howManyNum(propertyValue) == 1 && hasZero(propertyValue) && hasAlpha(propertyValue))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

//tells you if you have something like .8em; and should add a 0 to the start
bool needsLeadingZero(std::string propertyValue)
{
	int periodPosition = propertyValue.find('.');

	if (periodPosition != std::string::npos)
	{
		if(isdigit(propertyValue[periodPosition-1])) //if we find 0-9, then it is valid to be put in front of a .
		{
			return false;
		}
		else
		{
			return true;
		}
	} 
	else //if dont find period then no point in even checking
	{
		return false;
	}
}


bool hasHexadecimal (std::string input)
{
	if (input.find('#') != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//tells you if you can replace the string with hexadecimal or not || guaranteed to get a # as an input || based on the fact that hex value will be last
bool canReplaceHexadecimal (std::string input)
{
	int semicolonPostion = input.find(';');
	int hexPostion = input.find('#');
	int difference = semicolonPostion - hexPostion;
	string hexString = input.substr(hexPostion+1, difference-1);
	
	if (hexString.length() == 3)
	{
		return false;
	}
	else //its not already of length 3, so we need to see if we can reduce it or not
	{
		if(hexString.length() == 6) //go through it in pairs, and it at any point the two next to each other arent the same, then  return false;
		{
			for (int i = 0; i < hexString.length(); i+=2)
			{
				if (hexString[i] != hexString[i+1])
				{
					return false;
				}
			}
			return true;
		}
		else
			return false;
	}
}

bool incorrectSeparateDelimiters(std::string input)
{
	if (input.find('_') != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

bool missingSemicolon(std::string input) //all lines inside a selector should end in a semi colon
{
	if (input.find(';') != std::string::npos)
	{
		return false;
	}
	else //couldn't find a semicolon
		return true;
}

bool isIDorClass (std::string input) //tells us if this is a class or id
{
	if (input[0] == '.' || input[0] == '#')
	{
		return true;
	}
	else
		return false;
}

bool incorrectPropertyNameStop (std::string input) //we are inside a selector so we are guaranteed a : exists and check to see if the format is anything other than a: b
{
	int colonPosition = input.find(':');
	if (colonPosition != std::string::npos && (input[colonPosition-1] == ' ' || input[colonPosition+1] != ' '))
	{
		return true;
	}
	else
		return false;

}

//if we find even a single comma, we know that there must be multiple selectors
bool hasMultipleSelectors (std::string input)
{
	int commaPosition = input.find(',');
	if (commaPosition != std::string::npos)
	{
		return true;
	}
	else //there is no , and hence there cannot be multiple selectors
		return false;
}

//if we find multiple ; we know there are multiple declarations || finding 1 is not enough
bool hasMultipleDeclarations(std::string input)
{
	int firstSemiColon = input.find_first_of(';');
	int lastSemiColon = input.find_last_of(';');
	if (firstSemiColon != lastSemiColon) //we found at LEAST two semicolons and they are in different positions
	{
		return true;
	} 
	else
	{
		return false;
	}
}

//based on the assumption that there will never be just a ' alone and that they will always come in pairs! also based on the assumption that people won't use ' unless it is to surround a string
bool hasSingleQuotes(std::string input)
{
	int quotePosition = input.find('\'');
	if (quotePosition != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

bool hasDoubleQuotes(std::string input)
{
	int quotePosition = input.find('"');
	if (quotePosition != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//tells you if the line above the selector is valid or not
bool isValidLineAboveSelector(std::string input)
{
	int commaPosition = input.find(',');
	if (commaPosition != std::string::npos && input[input.length()-1] == ',')
	{
		return true;
	}
	else
		return false;
}
