#ifndef GIVENS_H
#define GIVENS_H

#include <regex.h>
#include <stdio.h>

#define FALSE 0
#define TRUE !FALSE

#define LEXEME_MAX 256
#define MY_CHAR_MAX 256

/* an enum is basically a variable with states. Each state has an integer value
   assigned to it. I assume that this will be used by setting a token equal to
   a char array and determining if the value is between 0 and 12 (there are 13
   tokens in the enum)
*/
enum token{ LEFT_PARENTHESIS,
			RIGHT_PARENTHESIS,
			LEFT_BRACKET,
			RIGHT_BRACKET,
			WHILE_KEYWORD,
			RETURN_KEYWORD,
			EQUAL,
			COMMA,
			EOL,
			VARTYPE,
			IDENTIFIER,
			BINOP,
			NUMBER
		   };

/* An array of these structs will be passed into the tokenizer.
*/
struct lexics{
	enum token token;
	char lexeme[LEXEME_MAX];
};

_Bool validNumber(char* aLexeme);
_Bool validIdentifier(char * aLexeme);

//Stuck on file I/O? Research fgets! 
//fgets(input, MY_CHAR_MAX, inf) != NULL

#endif