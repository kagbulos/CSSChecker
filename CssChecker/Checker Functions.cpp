#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
using namespace std;

//tells if the string has an upper case character or not
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

//tells if the string has a colon or not
bool hasColon (std::string input)
{
	if (input.find(":") != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//checks that that there is a space before the curly and there is no empty space after
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

//checks if there is any empty space at the end of the string
bool endsEmptySpace(std::string input)
{
	if (input.length() > 0 && input[input.length()-1] == ' ')
	{
		return true;
	}
	else 
		return false;
}

//checks if the string starts with an empty space
bool startsEmptySpace(std::string input)
{
	if (input.length() > 0 && input[0] == ' ')
	{
		return true;
	}
	else 
		return false;
}

//tells us if the line we are looking at is a selector
bool hasSelector (std::string input)
{
	if (input.length() > 0 && input.find("{") != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//tells you when you find a closing selector }
bool hasClosingSelector (std::string input)
{
	if (input.length() > 0 && input.find("}") != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//checks the format of the opening selector (doesn't have a capital, doesn't start with a space, and has the correct format for a {)
bool hasProperSelectorFormat(std::string input) 
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

//checks the format of the closing selector || it shouldnt be more than }
bool hasProperClosingSelectorFormat(std::string input)
{
	if (input.length() > 1)
	{
		return false;
	}
	else 
		return true;
}

//returns the property of the line (i.e. margin, background, etc.)
string getProperty(std::string input)
{
	size_t colonPosition = input.find(":");
	if (input.length() > 0 && colonPosition != std::string::npos) //return everything up to the :
	{
		return input.substr(0, colonPosition);
	}
	else //couldn't find a : inside the line
		return "";

}

//returns the property value of the line (i.e. #fff, 0.8, etc.)
string getPropertyValue(std::string input)
{
	size_t colonPosition = input.find(":");
	if (input.length() > 0 && colonPosition != std::string::npos) //return everything up to the :
	{
		return input.substr(colonPosition+1);
	}
	else //couldn't find a : inside the line
		return "";
}

//checks the format of the line with a property and property value
bool hasProperPropertyAndValueFormat(std::string input)
{
	if (input.length() == 0 || hasUpper(input))
	{
		return false;
	}

	return true;
}

//finds how many spaces there are in the line before the text
int findIndentation(std::string input)
{
	int count = 0;
	int i = 0;

	if (input.length() == 0)
	{
		return 0;
	}
	
	while(input[i] == ' ')
	{
		count++;
		i++;
	}

	return count;
}

//tells you if you have a conjunction of element names and Ids/classes
bool isConjunctionSelector(std::string input) 
{
	size_t foundPeriod = input.find('.');
	size_t foundHash = input.find('#');
	//return true when find a . or # within the selector AND its not at the beginning
	if (input.length() > 0 && ((foundPeriod != std::string::npos && foundPeriod!=0) || (foundHash != std::string::npos && foundHash!=0)))
	{
		return true;
	}
	else
		return false;
}

//Tells you if the line is an id selector
bool isIDSelector (std::string input)
{
	if (input.length() > 0 && input[0] == '#')
	{
		return true;
	}
	else
		return false;
}

//tells you if you should add an item to the set containing one of the options that can be written in shorthand
bool shouldAddToSet(std::string input) 
{
	if (input.length() > 0 && (input.find("background") != std::string::npos || input.find("border")!= std::string::npos
		|| input.find("margin")!= std::string::npos || input.find("overflow")!= std::string::npos
		|| input.find("padding")!= std::string::npos || input.find("list-style")!= std::string::npos
		|| input.find("animation")!= std::string::npos || input.find("transition")!= std::string::npos))
	{
		return true;
	}
	else
		return false;
}

//tells you which string to add to the set based on what we find within the string
string shorthandToAdd (string input)
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

//helper function used in isZeroandUnits that tells you how many numerical characters there are in a string
int howManyNum(std::string input)
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

//helper function used in isZeroandUnits that checks whether the string has 0 inside of it or not
bool hasZero(std::string input) 
{
	if (input.length() > 0 && input.find("0") != std::string::npos)
	{
		return true;
	} 
	else
	{
		return false;
	}
}

//helper function used in isZeroandUnits that tells you whether or not the string has an alpha character in it or not
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

//tells you if you have something like margin: 0em;
bool isZeroAndUnits(std::string propertyValue)
{
	if (propertyValue.length() > 0 && howManyNum(propertyValue) == 1 && hasZero(propertyValue) && hasAlpha(propertyValue))
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

	if (propertyValue.length() > 0 && periodPosition != std::string::npos)
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
	else //if don't find period then no point in even checking
	{
		return false;
	}
}

//tells you if there is a hexadecimal in the property value or not
bool hasHexadecimal (std::string propertyValue)
{
	if (propertyValue.length() > 0 && propertyValue.find('#') != std::string::npos)
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
	
	if (hexString.length() == 3) //can't replace #eee only #eeeeee
	{
		return false;
	}
	else //its not already of length 3, so we need to see if we can reduce it or not
	{
		if(hexString.length() == 6) //go through it in pairs, and if at any point the two next to each other arent the same, then  return false;
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

//tells you if you have incorrect delimiters in the name i.e. hello_bye
bool incorrectSeparateDelimiters(std::string input)
{
	if (input.length() > 0 && input.find('_') != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//tells you if you are missing a semi colon or not || all lines inside a selector should end in a semi colon
bool missingSemicolon(std::string input)
{
	if (input.length() > 0 && input.find(';') != std::string::npos)
	{
		return false;
	}
	else //couldn't find a semicolon
		return true;
}

//tells us if this is a class or id line
bool isIDorClass (std::string input)
{
	if (input.length() > 0 && (input[0] == '.' || input[0] == '#'))
	{
		return true;
	}
	else
		return false;
}

//we are inside a selector so we are guaranteed a : exists and check to see if the format is anything other than a: b
bool incorrectPropertyNameStop (std::string input) 
{
	int colonPosition = input.find(':');
	if (colonPosition != std::string::npos && (input[colonPosition-1] == ' ' || input[colonPosition+1] != ' ')) //there has to be no space before hand AND a space after in order to be proper format
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

//tells you if the string has double quotes inside of it
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
//the only acceptable format is something like h1, || //comment here
bool isValidLineAboveSelector(std::string input)
{
	int commaPosition = input.find(',');
	int otherCommaPosition = input.find_last_of(',');
	if (commaPosition != std::string::npos && input[input.length()-1] == ',' && commaPosition == otherCommaPosition)
	{
		return true;
	}
	else
		return false;
}

//tells you if the line is related to a comment or not
bool isCommentRelated(std::string input)
{
	int openBlockPosition = input.find("/*");
	int closeBlockPosition = input.find("*/");
	int commentPosition = input.find("//");
	if ((openBlockPosition != std::string::npos) || (closeBlockPosition != std::string::npos) || (commentPosition != std::string::npos))
	{
		return true;
	}
	else
		return false;
}

//tells you when you find open block comment
bool foundOpenBlockComment(std::string input)
{
	int openBlockPosition = input.find("/*");
	if (openBlockPosition != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//tells you when you find close block comment
bool foundCloseBlockComment(std::string input)
{
	int openBlockPosition = input.find("*/");
	if (openBlockPosition != std::string::npos)
	{
		return true;
	}
	else
		return false;
}

//tells you if the line with */ has the correct format
bool hasCorrectCloseBlockFormat(std::string input)
{
	if (input.length() > 2)
	{
		return false;
	}
	else
		return true;
}
