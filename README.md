Documentation for Css Checker
---------------------------

Contact
-------
Email:kagbulos1@gmail.com

Date
----
6/30/15

Description
-----------
This is a a win32 console application written in C++ that checks if a CSS file adheres to the Udacity style guidelines (http://udacity.github.io/frontend-nanodegree-styleguide/css.html). When the application finds an error, the error and corresponding line number are printed to the console. A comprehensive sample file (test1.css) is provided in the repository and can be used with the .exe to see what errors are found as well as the format of the output.

How to use
-----------
To run the application, open up console and type in: location-to-exe css-file-to-test
Ex. C:\Users\Kendall\Projects\CssChecker\Release\CssChecker.exe C:\Users\Kendall\Desktop\test1.css

Installion
----------
Pull the project from github and find the .exe within the release folder

Additional Notes
----------------
There are some cases which I cannot solve within the style guide because of the time it would take to implement. For instance, there is a case where a selector (such as .demoimage {) is suppose to be seperated by a hyphen. To solve this problem it would either take natural language processing or a trie to find where a word ends and insert a hyphen. However, even a trie couldn't solve the problem completely in the event that people make up their own words that don't exist in a dictionary.

Prospective Changes
-------------------
-Adding a UI
-Writing the output to a text document instead of console