#include "Tokenizer.h"

/* LEXEME_MAX 256
   MY_CHAR_MAX 256
*/

_Bool tokenizer(struct lexics *aLex, int *numLex, FILE *inf){
    /* 'aLex' is a pointer to the first element of an array of lexics structs
       'numLex' is a global pointer to the number of lexics found
            -this will be used to keep positioning and needs to be incremented
       'inf' is a pointer to the input FILE from the user
            -need to research how this works in terms of file manipulation
    */

    //variables
    _Bool lexResult;


    //function that scans through the entire file and creates un-tokenized lexics structs
    printf("Generating lexemes...\n");
    lexResult = generateLexemes(aLex, numLex, inf);
    printf("Lexemes generated.\n");

    if (lexResult == TRUE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

_Bool generateLexemes(struct lexics *lexArray, int *numLexemes, FILE *inputFile){
    char c;  //current char
    char pc; //previous char
    int prevDelim = 3;
    int builderIndex = 0;
    char lexemeBuilder[LEXEME_MAX];

    while ((c=fgetc(inputFile)) != EOF) {
        if (prevDelim == 0){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
                pc = c;
            }
            else if (isDelimiter(c) == 1){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                lexArray[*numLexemes].lexeme[0] = c;
                lexArray[*numLexemes].lexeme[1] = '\0';
                *numLexemes = *numLexemes + 1;
                prevDelim = 1;
                pc = c;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                lexemeBuilder[builderIndex] = 'c';
                builderIndex++;
                prevDelim = 2;
                pc = c;
            }
            else if (isDelimiter(c) == 3){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                prevDelim = 3;
                pc = c;
            }
        }
        else if (prevDelim == 1){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
                pc = c;
            }
            else if (isDelimiter(c) == 1){
                lexArray[*numLexemes].lexeme[0] = c;
                lexArray[*numLexemes].lexeme[1] = '\0';
                *numLexemes = *numLexemes + 1;
                prevDelim = 1;
                pc = c;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = 'c';
                builderIndex++;
                prevDelim = 2;
                pc = c;
            }
            else if (isDelimiter(c) == 3){
                prevDelim = 3;
                pc = c;
            }
        }
        else if (prevDelim == 2){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
                pc = c;
            }
            else if (isDelimiter(c) == 1){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                lexArray[*numLexemes].lexeme[0] = c;
                lexArray[*numLexemes].lexeme[1] = '\0';
                *numLexemes = *numLexemes + 1;
                prevDelim = 1;
                pc = c;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                prevDelim = 2;
                pc = c;
            }
            else if (isDelimiter(c) == 3){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexemes].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexemes = *numLexemes + 1;
                builderIndex = 0;
                prevDelim = 3;
                pc = c;
            }
        }
        else if (prevDelim == 3){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
                pc = c;
            }
            else if (isDelimiter(c) == 1){
                lexArray[*numLexemes].lexeme[0] = c;
                lexArray[*numLexemes].lexeme[1] = '\0';
                *numLexemes = *numLexemes + 1;
                prevDelim = 1;
                pc = c;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = 'c';
                builderIndex++;
                prevDelim = 2;
                pc = c;
            }
            else if (isDelimiter(c) == 3){
                prevDelim = 3;
                pc = c;
            }
        }
    }
    return TRUE;
}

/* checks for delimiter, returns an integer value meaning the following:
   0, not a delimiter
   1, is a guaranteed stand-alone delimiter lexeme (like a comma)
        -nothing will ever come after a ','
   2, is a delimiter that could be the start of another lexeme (equals sign)
        -could be '=' or '=='
   3, ignorable whitespace such as a tab or space
*/
int isDelimiter(char c){
    if ((c == '(')||(c == ')')||(c == '{')||(c == '}')||(c == ';')
    ||(c == ',')||(c == '+')||(c == '*')||(c == '%')){
        return 1;
    }
    else if ((c == '=')||(c == '!')){
        return 2;
    }
    else if ((c == ' ')||(c == '\t')||(c == '\n')){
        return 3;
    }
    else {
        return 0;
    }
}