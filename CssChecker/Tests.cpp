#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include "Checker Functions.h"
using namespace std;

void test()
{
	bool toRet;
	string toRet1;
	int toRet2;
	
	//toRet = hasSelector("*:before: {"); //expect 1
	//cout << toRet << "\n";
	//toRet = hasSelector("*:before: "); //expect 0
	//cout << toRet << "\n";
	//toRet = hasSelector(""); //expect 0
	//cout << toRet << "\n";

	//toRet = hasProperSelectorFormat("html {"); //expect 1
	//cout << toRet << "\n";
	//toRet = hasProperSelectorFormat("Html {"); //expect 0
	//cout << toRet << "\n";
	//toRet = hasProperSelectorFormat("htmL {"); //expect 0
	//cout << toRet << "\n";
	//toRet = hasProperSelectorFormat("html{"); //expect 0
	//cout << toRet << "\n";
	//toRet = hasProperSelectorFormat("htmL{"); //expect 0
	//cout << toRet << "\n";

	/*toRet1 = getProperty("padding: 1em;");
	cout << toRet1 << "\n";
	toRet1 = getProperty(" padding: 1em;");
	cout << toRet1 << "\n";
	toRet1 = getProperty(" padding_: 1em;");
	cout << toRet1 << "\n";

	toRet1 = getPropertyValue("padding: 1em;");
	cout << toRet1 << "\n";
	toRet1 = getPropertyValue(" padding:1em;");
	cout << toRet1 << "\n";
	toRet1 = getPropertyValue(" padding_: 1em_;");
	cout << toRet1 << "\n";*/

	//toRet2 = findIndentation("padding: 1em;"); //expect 0
	//cout << toRet2 << "\n";
	//toRet2 = findIndentation(" padding: 1em;");//expect 1
	//cout << toRet2 << "\n";
	//toRet2 = findIndentation("    padding: 1em;");//expect 4
	//cout << toRet2 << "\n";

	//toRet =  isConjunctionSelector("ul#example { … }"); //expect true
	//cout << toRet<< "\n";
	//toRet =  isConjunctionSelector("div.error { … }"); //expect true
	//cout << toRet<< "\n";
	//toRet =  isConjunctionSelector(".example { … }"); //expect false
	//cout << toRet<< "\n";

	/*toRet = canReplaceHexadecimal("border-bottom: 1px solid #ddd;");
	cout << toRet<< "\n";
	toRet = canReplaceHexadecimal("background: #4caf50;");
	cout << toRet<< "\n";
	toRet = canReplaceHexadecimal("color: #FFF;");
	cout << toRet<< "\n";
	toRet = canReplaceHexadecimal("color: #FFAADD;");
	cout << toRet<< "\n";*/

}