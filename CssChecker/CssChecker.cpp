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

#if defined(Full) //Full is defined in stdafx.h. When it is defined, the full module runs. When it is off, the the testing section in tests.cpp runs
int _tmain(int argc, _TCHAR* argv[])
{
	string line;
	ifstream CssFile(argv[1]);
	if (CssFile.is_open())
	{
		bool foundIndentation = false; //will tell us once we find the expected indentation
		bool insideASelector = false; //tells you if you are inside a selector or not
		bool nextLineShouldBeEmpty = false; //tells us if the next line should be empty or not
		bool insideABlockComment = false; //tells you if you are in a block comment or not
		int expectedNumSpaces = 0; //tells the number of spaces we expect
		int lineNumber = 1; //tells the line number so we can print the line of the error
		int lastBlockOpen = 0; //temp value that holds the line number for the last block comment open
		set<string> setOfShorthand; //contains a list of the shorthand properties we have seen so far inside a selector
		string property; //will hold the property we are looking at
		string propertyValue; //will hold the value of the property we are looking at
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

			//send the line to this section for further processing.
			//either the line is a selector line, closes the selector, inside a selector, or a line above the selector that continues to the selector line
			if (hasSelector(line)) //line looks like body {
			{
				if (insideASelector) //you are already inside a selector and shouldnt find another {
				{
					cout << "Ran into another { before found a closing } on line " << lineNumber << "\n"; 
				}

				if (isConjunctionSelector(line)) //error if you find something like ul#example
				{
					cout << "Using a conjunction of element names and IDs/classes " << lineNumber << "\n"; 
				}

				if (isIDSelector(line)) //classes should be used over IDs
				{
					cout << "An ID selector is being used on " << lineNumber << " and a class should be used instead \n";
				}

				if (!hasProperSelectorFormat(line)) //must contain correct format .demo-image {
				{
					cout << "Selector formatting problem on line " << lineNumber << "\n"; 
				}

				if (incorrectSeparateDelimiters(line)) //must use - instead of _
				{
					cout << "A _ was detected in the selector and a - should be used instead on line " << lineNumber << "\n"; 
				}

				if (hasMultipleSelectors(line)) //h1, h2, h3 { should span multiple lines
				{
					cout << "There are multiple selectors on line " << lineNumber << " and each selector should have it's own line\n";
				}

				insideASelector = true; //we are inside a selector
			}
			else if (hasClosingSelector(line)) //line looks like }
			{
				if (!insideASelector) //shouldn't run into a } before we cound a {
				{
					cout << "Found a closing } but doesnt have a matching {  on line " << lineNumber << "\n"; 
				}

				if (!hasProperClosingSelectorFormat(line)) //should only be a } in the line
				{
					cout << "Closing selector formatting problem on line " << lineNumber << "\n"; 
				}
				
				setOfShorthand.clear(); //clear the set for the next properties in the next selector
				insideASelector = false; //now that we are found a closing selector, we are no longer inside a selector
				nextLineShouldBeEmpty = true; //now that we found a closing selector, expect there to be a space on the next line
			}
			else if (line.length() == 0) //will catch all the blank lines so they don't go to the section for processing properties and values
			{
			}
			else if(insideASelector) //you are inside the selector i.e. background: #fff;
			{
				property = getProperty(line);
				propertyValue = getPropertyValue(line);

				if (missingSemicolon(line) && !isIDorClass(line) && !isCommentRelated(line)) //have to add !isIDorClass(line) in case where formatting is off and .audio-block and { are on separate lines
				{
					cout << "Missing a semicolon on line " << lineNumber << "\n"; 
				}

				if (incorrectPropertyNameStop(line)) //case where have incorrect form of property name stop i.e. a:b
				{
					cout << "The format of the property and value is incorrect on line " << lineNumber << ". It should be of the form a: b\n";  
				}

				if (!foundIndentation && !isIDorClass(line)) //use the first line as a baseline for every other line and indentation
				{
					expectedNumSpaces = findIndentation(line);
					foundIndentation = true;
				}

				if (findIndentation(line) != expectedNumSpaces && !isIDorClass(line)) //if the line doesn't match the same number of spaces as the first line, then indentation error
				{
					cout << "The level of indentation/spaces is off on line " << lineNumber << "\n"; 
				}

				if (shouldAddToSet(property)) //section of code that will determine if a line can be written in shorthand or not
				{
					tempShortHand = shorthandToAdd(property); //tells you which property to add to set (given that only a couple can be written in shorthand)
					if (setOfShorthand.find(tempShortHand) != setOfShorthand.end()) //we have already seen a shorthand property of this kind
					{
						cout << "The property on line " << lineNumber << " can be written in shorthand\n";
					}
					else //haven't seen this property before
					{
						setOfShorthand.insert(tempShortHand);
					}
				}

				if (!hasProperPropertyAndValueFormat(line) && !hasSingleQuotes(propertyValue) && !hasDoubleQuotes(propertyValue)) //check if it has the proper format but don't count strings for upper case
				{
					cout << "Property or value has formatting problem on line " << lineNumber << "\n"; 
				}

				if (isZeroAndUnits(propertyValue)) // 0em; should be 0;
				{
					cout << "Property value has formatting problem on line " << lineNumber << ". Values with 0 should have no units\n"; 
				}

				if (needsLeadingZero(propertyValue)) //if anything other than 0-9 in front of the . then error
				{
					cout << "Property value has a . and should have a 0 in front of it on line " << lineNumber << "\n"; 
				}

				if (hasHexadecimal(propertyValue) && canReplaceHexadecimal(propertyValue)) //color: #eebbcc; is an error and should be color: #ebc;
				{
					cout << "Property value has a hexadecimal value that can be rewritten as 3-characters hexadecimal notation on line " << lineNumber << "\n";
				}

				if (hasMultipleDeclarations(propertyValue)) //cases like font-weight: normal; line-height: 1.2; should span multiple lines
				{
					cout << "There are multiple declarations on line " << lineNumber << " and each declaration should have its own line\n";
				}

				if (hasSingleQuotes(propertyValue)) //font-family: 'Open Sans' should be font-family: "Open Sans"
				{
					cout << "There are single quotes on line " << lineNumber << " and double quotes should be used instead\n";
				}

			}
			else //section that handles lines above the selector { i.e. h1,h2,h3 should be spanning multiple lines
			{
				// [/*] [*/] [ *] [string] are all valid ways to be related to a comment
				if (isCommentRelated(line) || insideABlockComment)
				{
					if (startsEmptySpace(line)) //comment lines should never start with a space
					{
						cout << "Comment related line shouldn't start with a space found on line " << lineNumber << "\n";
					}

					if (foundOpenBlockComment(line)) //marking that you are inside a block comment
					{
						insideABlockComment = true;
						lastBlockOpen = lineNumber;
					}

					if (foundCloseBlockComment(line)) //marking that you are ending a block comment
					{
						if (!insideABlockComment)
						{
							cout << "found a closing block comment before an open block comment on line " << lineNumber << "\n";
						}

						if (!hasCorrectCloseBlockFormat(line) && !foundOpenBlockComment(line)) //if you dont find a /* on same line as */ then then line should be empty
						{
							cout << "There shouldn't be anything more on the line with a */ on line " << lineNumber << "\n";
						}
						insideABlockComment = false;
					}
				}
				else
				{
					if (!isValidLineAboveSelector(line)) //valid lines above the selector are of the form h1, 
					{
						cout << "Not a valid line above a selector on line " << lineNumber << "\n";
					}
				}
			}

			lineNumber++; //after end each line, increase line number
		}

		if (insideABlockComment) //if you are still inside a comment by the end, you are midding a closing comment block
		{
			cout << "There was a block comment on line " << lastBlockOpen << " that was never closed\n";
		}

		CssFile.close(); //close the file after we open it
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

