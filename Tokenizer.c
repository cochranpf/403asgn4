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
    _Bool genResult;
    _Bool tokResult;


    //function that scans through the entire file and creates un-tokenized lexics structs
    printf("Generating lexemes...\n");
    genResult = generateLexemes(aLex, numLex, inf);
    printf("Lexemes generated.\n");

    printf("Tokenizing lexemes...\n");
    tokResult = tokenizeLexemes(aLex, numLex);
    printf("Lexemes tokenized.\n");

    if ((genResult == TRUE)&&(tokResult == TRUE)){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

_Bool generateLexemes(struct lexics *lexArray, int *numLexics, FILE *inputFile){
    char c;  //current char
    int prevDelim = 3;
    int builderIndex = 0;
    char lexemeBuilder[LEXEME_MAX];

    while ((c=fgetc(inputFile)) != EOF) {
        if (prevDelim == 0){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
            }
            else if (isDelimiter(c) == 1){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                lexArray[*numLexics].lexeme[0] = c;
                lexArray[*numLexics].lexeme[1] = '\0';
                *numLexics = *numLexics + 1;
                prevDelim = 1;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 2;
            }
            else if (isDelimiter(c) == 3){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                prevDelim = 3;
            }
        }
        else if (prevDelim == 1){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
            }
            else if (isDelimiter(c) == 1){
                lexArray[*numLexics].lexeme[0] = c;
                lexArray[*numLexics].lexeme[1] = '\0';
                *numLexics = *numLexics + 1;
                prevDelim = 1;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 2;
            }
            else if (isDelimiter(c) == 3){
                prevDelim = 3;
            }
        }
        else if (prevDelim == 2){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
            }
            else if (isDelimiter(c) == 1){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                lexArray[*numLexics].lexeme[0] = c;
                lexArray[*numLexics].lexeme[1] = '\0';
                *numLexics = *numLexics + 1;
                prevDelim = 1;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                prevDelim = 1; //this is to account for a case like == derp
            }
            else if (isDelimiter(c) == 3){
                lexemeBuilder[builderIndex] = '\0';
                memcpy(lexArray[*numLexics].lexeme, lexemeBuilder, LEXEME_MAX);
                *numLexics = *numLexics + 1;
                builderIndex = 0;
                prevDelim = 3;
            }
        }
        else if (prevDelim == 3){
            if (isDelimiter(c) == 0){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 0;
            }
            else if (isDelimiter(c) == 1){
                lexArray[*numLexics].lexeme[0] = c;
                lexArray[*numLexics].lexeme[1] = '\0';
                *numLexics = *numLexics + 1;
                prevDelim = 1;
            }
            else if (isDelimiter(c) == 2){
                lexemeBuilder[builderIndex] = c;
                builderIndex++;
                prevDelim = 2;
            }
            else if (isDelimiter(c) == 3){
                prevDelim = 3;
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

/* enum token{ LEFT_PARENTHESIS, RIGHT_PARENTHESIS, LEFT_BRACKET, RIGHT_BRACKET,
                WHILE_KEYWORD, RETURN_KEYWORD, EQUAL, COMMA, EOL, VARTYPE,
			    IDENTIFIER, BINOP, NUMBER };
*/

_Bool tokenizeLexemes(struct lexics *lexArray, int *numLexics){
    _Bool errors = FALSE;
    for(int i = 0; i < *numLexics; i++){
        if (strcmp(lexArray[i].lexeme, "(") == 0){
            lexArray[i].token = LEFT_PARENTHESIS;
        }
        else if (strcmp(lexArray[i].lexeme, ")") == 0){
            lexArray[i].token = RIGHT_PARENTHESIS;
        }
        else if (strcmp(lexArray[i].lexeme, "{") == 0){
            lexArray[i].token = LEFT_BRACKET;
        }
        else if (strcmp(lexArray[i].lexeme, "}") == 0){
            lexArray[i].token = RIGHT_BRACKET;
        }
        else if (strcmp(lexArray[i].lexeme, "while") == 0){
            lexArray[i].token = WHILE_KEYWORD;
        }
        else if (strcmp(lexArray[i].lexeme, "return") == 0){
            lexArray[i].token = RETURN_KEYWORD;
        }
        else if (strcmp(lexArray[i].lexeme, "=") == 0){
            lexArray[i].token = EQUAL;
        }
        else if (strcmp(lexArray[i].lexeme, ",") == 0){
            lexArray[i].token = COMMA;
        }
        else if (strcmp(lexArray[i].lexeme, ";") == 0){
            lexArray[i].token = EOL;
        }
        else if ((strcmp(lexArray[i].lexeme, "int") == 0)||
        (strcmp(lexArray[i].lexeme, "void")) == 0){
            lexArray[i].token = VARTYPE;
        }
        else if ((strcmp(lexArray[i].lexeme, "+") == 0)||
        (strcmp(lexArray[i].lexeme, "*") == 0)||
        (strcmp(lexArray[i].lexeme, "!=") == 0)||
        (strcmp(lexArray[i].lexeme, "==") == 0)||
        (strcmp(lexArray[i].lexeme, "%") == 0)){
            lexArray[i].token = BINOP;
        }
        else if (validNumber(lexArray[i].lexeme) == TRUE){
            lexArray[i].token = NUMBER;
        }
        else if (validIdentifier(lexArray[i].lexeme) == TRUE){
            lexArray[i].token = IDENTIFIER;
        }
        else{
            printf("Lexeme \'%s\' could not be tokenized :(\n", lexArray[i].lexeme);
            errors = TRUE;
        }
    }
    if (errors == FALSE){
        return TRUE;
    }
    else{
        return FALSE;
    }
}