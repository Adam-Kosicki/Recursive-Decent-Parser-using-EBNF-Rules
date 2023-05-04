# Recursive-Decent-Parser-using-EBNF-Rules
C++ | Lexical Analysis

This is a C++ program that implements recursive descent parsing in order to parse a for loop using the associated EBNF rules. The program first performs lexical analysis to break down the input code into tokens that can be processed. The supported tokens include identifiers, integer literals, operators (+, -, *, /, =, ==, !=, >, >=, <, <=, ++, --), parentheses, semicolons, curly braces, and keywords (if, else, do, while).

The program implements functions to handle the different non-terminal symbols in the EBNF rules, including for loops, if statements, do-while loops, assignments, conditions, expressions, terms, and factors. The program also includes a function to handle errors in case an invalid token is encountered.

To run the program, input code must be saved in a text file and the file path should be specified in the program using the "myFile" variable. The program reads the input file, processes its contents, and outputs the result of parsing the for loop using the associated EBNF rules.

[Example]
Input: 
![image](https://user-images.githubusercontent.com/100010326/236336975-ccf94859-4a4c-4db9-a8ce-451858d33c05.png)

Output:
![image](https://user-images.githubusercontent.com/100010326/236337080-ab9ba465-491e-4dce-bfd6-803891c2eb62.png)
![image](https://user-images.githubusercontent.com/100010326/236337090-432ada2b-b509-4e17-bc8b-4133c20950e3.png)
