#pragma once
#include <string>

bool hasSelector (std::string input);
bool hasProperSelectorFormat(std::string input);
bool endsEmptySpace(std::string input);
bool startsEmptySpace(std::string input);
bool hasClosingSelector (std::string input);
bool hasProperClosingSelectorFormat(std::string input);
std::string getProperty(std::string input);
std::string getPropertyValue(std::string input);
bool hasProperPropertyAndValueFormat(std::string input);
int findIndentation(std::string input);
bool isConjunctionSelector(std::string input);
bool isIDSelector (std::string input);
bool shouldAddToSet(std::string input);
std::string shorthandToAdd (std::string input);
bool isZeroAndUnits(std::string propertyValue);
bool needsLeadingZero(std::string propertyValue);
bool hasHexadecimal (std::string input);
bool canReplaceHexadecimal (std::string input);
bool incorrectSeparateDelimiters(std::string input);
bool missingSemicolon(std::string input);
bool incorrectPropertyNameStop (std::string input);
bool isIDorClass (std::string input);
bool hasMultipleSelectors (std::string input);
bool hasMultipleDeclarations(std::string input);
bool hasSingleQuotes(std::string input);
bool hasDoubleQuotes(std::string input);
bool isValidLineAboveSelector(std::string input);