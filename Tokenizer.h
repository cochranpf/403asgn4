#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"
#include <string.h>

//variables


//structs



//functions
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

_Bool generateLexemes(struct lexics *lexArray, int *numLexics, FILE *inputFile);

int isDelimiter(char c);

_Bool tokenizeLexemes(struct lexics *lexArray, int *numLexics);

#endif
