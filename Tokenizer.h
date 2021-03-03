#ifndef TOKENIZER_H
#define TOKENIZER_H

#include "Givens.h"

//variables


//structs



//functions
_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf);

_Bool generateLexemes(struct lexics *lexArray, int *numLexemes, FILE *inputFile);

int isDelimiter(char c);

#endif
