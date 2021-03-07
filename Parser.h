#ifndef PARSER_H
#define PARSER_H

#include "Givens.h"
#include <string.h>

//variables
int index;

//structs



//functions
_Bool parser(struct lexics *someLexics, int numberOfLexics);

_Bool function();
_Bool header();
_Bool argDecl();
_Bool body();
_Bool statementList();
_Bool statement();
_Bool whileLoop();
_Bool returnStatement();
_Bool assignment();
_Bool expression();
_Bool term();

_Bool match(enum token tok);


#endif