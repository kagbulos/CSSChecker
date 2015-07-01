// CssChecker.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include "Checker Functions.h"
#include "Tests.h"
using namespace std;


#if defined(Full)
int _tmain(int argc, _TCHAR* argv[])
{
	string line;
	ifstream CssFile(argv[1]);
	if (CssFile.is_open())
	{
		string property; //will hold the property we are looking at
		string propertyValue; //will hold the value of the property we are looking at
		int lineNumber = 1; //tells the line number so we can print the line of the error
		int expectedNumSpaces = 0; //tells the number of spaces we expect
		bool foundIndentation = false; //will tell us once we find the expected indentation
		bool nextLineShouldBeEmpty = false; //tells us if the next line should be empty or not
		bool insideASelector = false;
		set<string> setOfShorthand; //contains a list of the shorthand properties we have seen so far inside a selector
		string tempShortHand; //stores a temp value of the shorthand we are going to add

		while(getline(CssFile,line))
		{
			if (endsEmptySpace(line)) //no line should ever end with white space
			{
				cout << lineNumber << " Ends with an empty space " << "\n"; 
			}

			if (nextLineShouldBeEmpty) //if the next line should be empty, check it and then set next line should be empty to false
			{
				if (line.length() != 0)
				{
					cout << lineNumber << " should be empty because it followed a closing selector " << "\n"; 
				}
				nextLineShouldBeEmpty = false;
			}
			//send the line to this section for processing.
			//either the line is a selector line, closes the selector, inside a selector, or a line above the selector that continues to the selector line
			if (hasSelector(line)) //line looks like body {
			{
				if (insideASelector) //you are already inside a selector and shouldnt find another {
				{
					cout << "Ran into another { before found a closing } on line " << lineNumber << "\n"; 
				}

				if (isConjunctionSelector(line))
				{
					cout << "Using a conjunction of element names and IDs/classes " << lineNumber << "\n"; 
				}

				if (isIDSelector(line))
				{
					cout << "An ID selector is being used on " << lineNumber << " and a class should be used instead \n";
				}

				if (!hasProperSelectorFormat(line))
				{
					cout << "Selector formatting problem on line " << lineNumber << "\n"; 
				}

				if (incorrectSeparateDelimiters(line))
				{
					cout << "A _ was detected in the selector and a - should be used instead on line " << lineNumber << "\n"; 
				}

				if (hasMultipleSelectors(line))
				{
					cout << "There are multiple selectors on line " << lineNumber << " and each selector should have it's own line\n";
				}

				insideASelector = true; //we are inside a selector

			}
			else if (hasClosingSelector(line)) // line looks like }
			{
				if (!insideASelector)
				{
					cout << "Found a closing } but doesnt have a matching {  on line " << lineNumber << "\n"; 
				}

				if (!hasProperClosingSelectorFormat(line))
				{
					cout << "Closing selector formatting problem on line " << lineNumber << "\n"; 
				}
				
				setOfShorthand.clear();//clear the set for the next properties in the next selector

				insideASelector = false;
				nextLineShouldBeEmpty = true; //now that we found a closing selector, expect there to be a space on the next line
			}
			else if (line.length() == 0) //will catch all the blank lines so they dont go to the section for processing properties and values
			{
			}
			else if(insideASelector) //you are inside the selector
			{
				property = getProperty(line);
				propertyValue = getPropertyValue(line);

				if (missingSemicolon(line) && !isIDorClass(line)) //have to add !isIDorClass(line) in case where formatting is off and .audio-block and { are on separate lines
				{
					cout << "Missing a semicolon on line " << lineNumber << "\n"; 
				}

				if (incorrectPropertyNameStop(line))
				{
					cout << "The format of the property and value is incorrect on line " << lineNumber << ". It should be of the form a: b\n";  
				}

				if (!foundIndentation && !isIDorClass(line)) //use the first line as a baseline for every other line and indentation
				{
					expectedNumSpaces = findIndentation(line);
					foundIndentation = true;
				}

				if (findIndentation(line) != expectedNumSpaces && !isIDorClass(line))
				{
					cout << "The level of indentation/spaces is off on line " << lineNumber << "\n"; 
				}

				if (shouldAddToSet(property))
				{
					tempShortHand = shorthandToAdd(property);
					if (setOfShorthand.find(tempShortHand) != setOfShorthand.end())// we haven already seen a shorthand property of this kind
					{
						cout << "The property on line " << lineNumber << " can be written in shorthand\n";
					}
					else //havent seen this property before
					{
						tempShortHand = shorthandToAdd(property);
						setOfShorthand.insert(tempShortHand);
					}
				}

				if (!hasProperPropertyAndValueFormat(line) && !hasSingleQuotes(propertyValue) && !hasDoubleQuotes(propertyValue)) //dont count strings for upper case
				{
					cout << "Property or value has formatting problem on line " << lineNumber << "\n"; 
				}

				if (isZeroAndUnits(propertyValue)) //only need to look at property value
				{
					cout << "Property value has formatting problem on line " << lineNumber << ". Values with 0 should have no units\n"; 
				}

				if (needsLeadingZero(propertyValue))
				{
					cout << "Property value has a . and should have a 0 in front of it on line " << lineNumber << "\n"; 
				}

				if (hasHexadecimal(propertyValue) && canReplaceHexadecimal(propertyValue))
				{
					cout << "Property value has a hexadecimal value that can be rewritten as 3-characters hexadecimal notation on line " << lineNumber << "\n";
				}

				if (hasMultipleDeclarations(propertyValue))
				{
					cout << "There are multiple declarations on line " << lineNumber << " and each declaration should have its own line\n";
				}

				if (hasSingleQuotes(propertyValue))
				{
					cout << "There are single quotes on line " << lineNumber << " and double quotes should be used instead\n";
				}

			}
			else //section that handles lines above the selector { i.e. h1,h2,h3 should be spanning multiple lines
			{
				 if (!isValidLineAboveSelector(line)) //valid lines above the selector are of the form h1,
				 {
					 cout << "Not a valid line above a selector on line " << lineNumber << "\n";
				 }
			}

			lineNumber++; //after end each line, increase line number

		}
		CssFile.close();
	}
	else
		cout << "unable to open the file \n";
	return 0;
}
#else
int _tmain(int argc, _TCHAR* argv[])
{
	test();
}
#endif

