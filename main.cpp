/*
This program iterates through a for loop using recursive decent programing in order to break it down using the associated EBNF rules.
<forLoop> -> for(<Assign>,<cond><assign>)'{'{<assign>;}'}'

<if> -> if (<cond>)'{'{<assign>}'}' [<else if>] <else>
<else if> -> [else if (<cond>)'{'{<assign>}'}']
<else> -> else (<cond>)'{'{<assign>}'}'
<do> -> do '{' {<assign>} '}' while (<cond>)

<assign> -> id (=<expr>|++|--)
<cond> -> <expr> (>|>=|<|<=|!=|==) <expr>
<expr> -> <term> {(+ | -) <term>}
<term> -> <factor> {(* | /) <factor>)
<factor> -> id | int_constant | ( <expr )
In order to do so Lexical analysis is preformed to break the code down into understandable tokens to be operated on.
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctype.h>
#include <cstdio>

using namespace std;
/* Global declarations */
/* Variables */
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
ifstream myFile("C:\\Users\\maste\\Desktop\\New folder\\forStmt.txt");	// Put the file location here to run the code. <- SUPER IMPORTANT

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
void elseStmt();
void doLoop();
void ifstmt();
void assign();
void cond();
void expr();
void term();
void factor();
void error();
int lex();
void ifStatement();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define GR_THAN 27
#define GR_EQ_THAN 28
#define LS_THAN 29
#define LS_EQ_THAN 30
#define EQ_TO 31
#define NT_EQ_TO 32
#define INCR_OP 31
#define DECR_OP 32
#define NEGATION 33
#define DO 34
#define SEMICOLON 35
#define LEFT_CURLY 36
#define RIGHT_CURLY 37
#define IF 38
#define ELSE 39
#define WHILE 40

/******************************************************/
/* main driver */
int main() {
	/* Open the input data file and process its contents */
	if (!myFile.is_open()) {
		printf("ERROR - cannot open front.in \n");
		return 0;
	}
	else if (myFile.eof()) {
		printf("ERROR - Nothing in file \n");
		return 0;
	}
	else { // begins the recurson decent
		getChar();
		lex();
		doLoop();
	}
	myFile.close();
	return 0;
}
/*****************************************************/
/* lookup - a function to lookup operators and parentheses
 and return the token */
int lookup(char ch) {
	switch (ch) {
	case '(':
		addChar();
		nextToken = LEFT_PAREN;
		break;
	case ')':
		addChar();
		nextToken = RIGHT_PAREN;
		break;
	case '{':
		addChar();
		nextToken = LEFT_CURLY;
		break;
	case '}':
		addChar();
		nextToken = RIGHT_CURLY;
		break;
	case ';':
		addChar();
		nextToken = SEMICOLON;
		break;
	case '+':
		addChar();
		if (myFile.peek() == '+') {
			myFile.get(nextChar);
			addChar();
			nextToken = INCR_OP;
		}
		else {
			nextToken = ADD_OP;
		}
		break;
	case '-':
		addChar();
		if (myFile.peek() == '+') {
			myFile.get(nextChar);
			addChar();
			nextToken = DECR_OP;
		}
		else {
			nextToken = SUB_OP;
		}
		break;
	case '*':
		addChar();
		nextToken = MULT_OP;
		break;
	case '/':
		addChar();
		nextToken = DIV_OP;
		break;
	case '>':
		addChar();
		if (myFile.peek() == '=') {
			myFile.get(nextChar);
			addChar();
			nextToken = GR_THAN;
		}
		else {
			nextToken = GR_EQ_THAN;
		}
		break;
	case '<':
		addChar();
		if (myFile.peek() == '=') {
			myFile.get(nextChar);
			addChar();
			nextToken = LS_THAN;
		}
		else {
			nextToken = LS_EQ_THAN;
		}
		break;
	case '!':
		addChar();
		if (myFile.peek() == '=') {
			myFile.get(nextChar);
			addChar();
			nextToken = NT_EQ_TO;
		}
		else {
			nextToken = NEGATION;
		}
		break;
	case '=':
		addChar();
		if (myFile.peek() == '=') {
			myFile.get(nextChar);
			addChar();
			nextToken = EQ_TO;
		}
		else {
			nextToken = ASSIGN_OP;
		}
		break;
	default:
		addChar();
		nextToken = EOF;
		break;
	}
	return nextToken;
}
/*****************************************************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
	if (lexLen <= 98) {
		lexeme[lexLen++] = nextChar;
		lexeme[lexLen] = 0;
	}
	else
		printf("Error - lexeme is too long \n");
}
/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */
void getChar() {
	if (myFile.peek() == EOF) {
		nextChar = EOF;
		charClass = EOF;
	}
	else {
		myFile.get(nextChar);
		if (isalpha(nextChar))
			charClass = LETTER;
		else if (isdigit(nextChar))
			charClass = DIGIT;
		else charClass = UNKNOWN;
	}
}
/*****************************************************/
/* getNonBlank - a function to call getChar until it
 returns a non-whitespace character */
void getNonBlank() {
	while (isspace(nextChar))
		getChar();
}
/*****************************************************/
/* lex - a simple lexical analyzer for arithmetic
 expressions */
int lex() {
	lexLen = 0;
	getNonBlank();
	switch (charClass) {
		/* Parse identifiers */
	case LETTER:
		addChar();
		getChar();
		while (charClass == LETTER || charClass == DIGIT) {
			addChar();
			getChar();
		}
		if (lexeme[0] == 'd' && lexeme[1] == 'o' && lexLen == 2) {	// Checks if it is a for as in a do loop
			nextToken = DO;
		}
		else if (lexeme[0] == 'i' && lexeme[1] == 'f' && lexLen == 2) {	// Checks if it is a for as in a if
			nextToken = IF;
		}
		else if (lexeme[0] == 'e' && lexeme[1] == 'l' && lexeme[2] == 's' && lexeme[3] == 'e' && lexLen == 4) {		// Checks if it is a for as in a else loop
			nextToken = ELSE;
		}
		else if (lexeme[0] == 'w' && lexeme[1] == 'h' && lexeme[2] == 'i' && lexeme[3] == 'l' && lexeme[4] == 'e' && lexLen == 5) {		// Checks if it is a for as in a while loop
			nextToken = WHILE;
		}
		else {
			nextToken = IDENT;
		}
		break;
		/* Parse integer literals */
	case DIGIT:
		addChar();
		getChar();
		while (charClass == DIGIT) {
			addChar();
			getChar();
		}
		nextToken = INT_LIT;
		break;
		/* Parentheses and operators */
	case UNKNOWN:
		lookup(nextChar);
		getChar();
		break;
		/* EOF */
	case EOF:
		nextToken = EOF;
		lexeme[0] = 'E';
		lexeme[1] = 'O';
		lexeme[2] = 'F';
		lexeme[3] = 0;
		break;
	} /* End of switch */
	printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
	return nextToken;
} /* End of function lex */


void elseIfStatement() {
	printf("enter <elseIf>\n");
	if (nextToken == ELSE) {
		lex();
		ifStatement();
	}
	else {
		cout << nextToken;
		error();
	}
}

void elseStmt() {
	printf("enter <else>\n");
	if (nextToken == ELSE) {
		lex();
		assign();
		if (nextToken == SEMICOLON) {
			lex();
		}
		else {
			error();
		}
	}
	else {
		error();
	}
}

void ifStatement() {
	printf("enter <if>\n");
	if (nextToken == IF) {
		lex();
		if (nextToken == LEFT_PAREN) {
			lex();
			cond();
			if (nextToken == RIGHT_PAREN) {
				lex();
				assign();
				if (nextToken == SEMICOLON) {
					lex();
				}
				else {
					error();
				}
			}
			else {
				error();  // must have ) after assignment
			}
		}
		else {
			error();	// Must have ; after condition
		}
	}
	else {
		error();	// Must have ; after assignment
	}

	printf("exit <if>\n");
}
/*forLoop
Parses strings in the language generated by the rule:
<forLoop> -> for(<Assign>,<cond><assign>)'{'{<assign>;}'}'
*/
void doLoop() {
	printf("enter <doLoop>\n");
	if (nextToken == DO) {
		lex();
		if (nextToken == LEFT_CURLY) {
			lex();
			ifStatement();
			elseIfStatement();
			elseStmt();
			if (nextToken == RIGHT_CURLY) {
				lex();
				if (nextToken == WHILE) {
					lex();
					if (nextToken == LEFT_PAREN) {
						lex();
						cond();
						if (nextToken == RIGHT_PAREN) {
							lex();
						}
						else {
							error();	// Must have {
						}
					}
					else {
						error();  // must have ) after assignment
					}
				}
				else {
					error();	// Must have ; after condition
				}
			}
			else {
				error();	// Must have ; after assignment
			}
		}
		else {
			error();	// Must have (
		}
	}
	else {
		error();	// No 'do' - No do loop
	}
	printf("exit <doLoop>\n");
}






/*assign
Parses strings in the language generated by the rule:
<assign> -> id (=<expr>|++|--)
*/
void assign() {
	printf("enter <assign>\n");
	if (nextToken == IDENT) {
		lex();
		if (nextToken == ASSIGN_OP) {	// If its an assignment then it will use an experesion
			lex();
			expr();
		}
		else if (nextToken == INCR_OP || nextToken == DECR_OP) {
			lex();
		}
		else {
			error();	// Must be one of the 3 operations
		}
	}
	else {
		error();	// Always has to start with an IDENT (id)
	}
	printf("exit <assign>\n");
}

/*cond
Parses strings in the language generated by the rule:
<cond> -> <expr> (>|>=|<|<=|!=|==) <expr>
*/
void cond() {
	printf("enter <expr>\n");
	expr();	//Cond can just be an exression or a comparason between expressions
	if (nextToken == GR_THAN || nextToken == GR_EQ_THAN || nextToken == LS_THAN || nextToken == LS_EQ_THAN || nextToken == NT_EQ_TO || nextToken == NT_EQ_TO) {
		lex();
		expr();
	}
	printf("Exit <cond>\n");
}

/* expr
Parses strings in the language generated by the rule:
<expr> -> <term> {(+ | -) <term>}
*/
void expr() {
	printf("Enter <expr>\n");
	/* Parse the first term */
	term();
	/* As long as the next token is + or -, get
	 the next token and parse the next term */
	while (nextToken == ADD_OP || nextToken == SUB_OP) {
		lex();
		term();
	}
	printf("Exit <expr>\n");
} /* End of function expr */

/* term
 Parses strings in the language generated by the rule:
 <term> -> <factor> {(* | /) <factor>)
 */
void term() {
	printf("Enter <term>\n");
	/* Parse the first factor */
	factor();
	/* As long as the next token is * or /, get the
	 next token and parse the next factor */
	while (nextToken == MULT_OP || nextToken == DIV_OP) {
		lex();
		factor();
	}
	printf("Exit <term>\n");
} /* End of function term */

/* factor
 Parses strings in the language generated by the rule:
 <factor> -> id | int_constant | ( <expr )
 */
void factor() {
	printf("Enter <factor>\n");
	/* Determine which RHS */
	if (nextToken == IDENT || nextToken == INT_LIT) {
		/* Get the next token */
		lex();
		/* If the RHS is ( <expr>), call lex to pass over the
		 left parenthesis, call expr, and check for the right
		 parenthesis */
	}
	else {
		if (nextToken == LEFT_PAREN) {
			lex();
			expr();
			if (nextToken == RIGHT_PAREN) {
				lex();
			}
			else {
				error();
			}
		} /* End of if (nextToken == ... */
	   /* It was not an id, an integer literal, or a left
		parenthesis */
		else
			error();
	} /* End of else */
	printf("Exit <factor>\n");;
} /* End of function factor */

void error() {
	printf("Error");
	exit(0);
}