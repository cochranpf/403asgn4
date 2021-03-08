#include "Parser.h"

_Bool parser(struct lexics *someLexics, int numberOfLexics){
    index = 0;
    if (function()){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

_Bool function(){
    if ((header())&&(body())){
        return TRUE;
    }
    else{
        return FALSE;
    }
}

_Bool header(){
    if (match(VARTYPE)){
        if (match(IDENTIFIER)){
            if (match(LEFT_PARENTHESIS)){
                if (someLexics[index].token == VARTYPE){
                    if (argDecl()){
                        if (match(RIGHT_PARENTHESIS)){
                            return TRUE;
                        }
                        else{
                            return FALSE;
                        }
                    }
                    else{
                        return FALSE;
                    }
                }
                else if (someLexics[index].token == RIGHT_PARENTHESIS){
                    if (match(RIGHT_PARENTHESIS)){
                        return TRUE;
                    }
                    else{
                        return FALSE;
                    }
                }
                else{
                    return FALSE;
                }
            }
            else{
                return FALSE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool argDecl(){
    if (match(VARTYPE)){
        if (match(IDENTIFIER)){
            if (someLexics[index].token == COMMA){
                if (match(COMMA)){
                    if (argDecl()){
                        return TRUE;
                    }
                    else{
                        return FALSE;
                    }
                }
            }
            else{
                return TRUE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool body(){
    if (match(LEFT_BRACKET)){
        if (someLexics[index].token == WHILE_KEYWORD){
            if (statementList()){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        else if (someLexics[index].token == RETURN_KEYWORD){
            if (statementList()){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        else if (someLexics[index].token == IDENTIFIER){
            if (statementList()){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        else if (someLexics[index].token == LEFT_BRACKET){
            if (statementList()){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        else if (someLexics[index].token == RIGHT_BRACKET){
            if (match(RIGHT_BRACKET)){
                return TRUE;
            }
            else{
                return FALSE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool statementList(){
    while ((someLexics[index].token == WHILE_KEYWORD)||
            (someLexics[index].token == RETURN_KEYWORD)||
            (someLexics[index].token == IDENTIFIER)||
            (someLexics[index].token == LEFT_BRACKET)) {
        if (someLexics[index].token == WHILE_KEYWORD) {
            if (statement()) {
                return TRUE;
            } else {
                return FALSE;
            }
        } else if (someLexics[index].token == RETURN_KEYWORD) {
            if (statement()) {
                return TRUE;
            } else {
                return FALSE;
            }
        } else if (someLexics[index].token == IDENTIFIER) {
            if (statement()) {
                return TRUE;
            } else {
                return FALSE;
            }
        } else if (someLexics[index].token == LEFT_BRACKET) {
            if (statement()) {
                return TRUE;
            } else {
                return FALSE;
            }
        }
        else {
            return FALSE;
        }
    }
    return TRUE;
}

_Bool statement(){
    if (someLexics[index].token == WHILE_KEYWORD) {
        if (whileLoop()) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if (someLexics[index].token == RETURN_KEYWORD) {
        if (returnStatement()) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if (someLexics[index].token == IDENTIFIER) {
        if (assignment()) {
            return TRUE;
        } else {
            return FALSE;
        }
    } else if (someLexics[index].token == LEFT_BRACKET) {
        if (body()) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    else {
        return FALSE;
    }
}

_Bool whileLoop(){
    if (match(RETURN_KEYWORD)){
        if (match(LEFT_PARENTHESIS)){
            if((someLexics[index].token == LEFT_PARENTHESIS)||
            (someLexics[index].token == IDENTIFIER)||
            (someLexics[index].token == NUMBER)){
                if (expression()){
                    if (match(RIGHT_PARENTHESIS)){
                        if ((someLexics[index].token == WHILE_KEYWORD)||
                        (someLexics[index].token == RETURN_KEYWORD)||
                        (someLexics[index].token == IDENTIFIER)||
                        (someLexics[index].token == LEFT_BRACKET)){
                            if (statement()){
                                return TRUE;
                            }
                            else{
                                return FALSE;
                            }
                        }
                        else{
                            return FALSE;
                        }
                    }
                    else{
                        return FALSE;
                    }
                }
                else{
                    return FALSE;
                }
            }
            else{
                return FALSE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool returnStatement(){
    if (match(RETURN_KEYWORD)){
        if ((someLexics[index].token == WHILE_KEYWORD)||
            (someLexics[index].token == RETURN_KEYWORD)||
            (someLexics[index].token == IDENTIFIER)||
            (someLexics[index].token == LEFT_BRACKET)){
            if (expression()){
                if (match(EOL)){
                    return TRUE;
                }
                else{
                    return FALSE;
                }
            }
            else{
                return FALSE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool assignment(){
    if (match(IDENTIFIER)){
        if (match(EQUAL)){
            if ((someLexics[index].token == WHILE_KEYWORD)||
                (someLexics[index].token == RETURN_KEYWORD)||
                (someLexics[index].token == IDENTIFIER)||
                (someLexics[index].token == LEFT_BRACKET)){
                if (expression()){
                    if (match(EOL)){
                        return TRUE;
                    }
                    else{
                        return FALSE;
                    }
                }
                else{
                    return FALSE;
                }
            }
            else{
                return FALSE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool expression(){
    if ((someLexics[index].token == IDENTIFIER)||
    (someLexics[index].token == NUMBER)){
        if (term()){
            while (someLexics[index].token == BINOP){
                if (match(BINOP)){
                    if (term()){
                        return TRUE;
                    }
                    else{
                        return FALSE;
                    }
                }
                else{
                    return FALSE;
                }
            }
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    else if (someLexics[index].token == LEFT_PARENTHESIS){
        if (match(LEFT_PARENTHESIS)){
            if ((someLexics[index].token == WHILE_KEYWORD)||
                (someLexics[index].token == RETURN_KEYWORD)||
                (someLexics[index].token == IDENTIFIER)||
                (someLexics[index].token == LEFT_BRACKET)){
                if (expression()){
                    if (match(RIGHT_PARENTHESIS)){
                        return TRUE;
                    }
                    else{
                        return FALSE;
                    }
                }
                else{
                    return FALSE;
                }
            }
            else{
                return FALSE;
            }
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool term(){
    if (someLexics[index].token == IDENTIFIER){
        if (match(IDENTIFIER)){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    else if (someLexics[index].token == NUMBER){
        if (match(NUMBER)){
            return TRUE;
        }
        else{
            return FALSE;
        }
    }
    else{
        return FALSE;
    }
}

_Bool match(enum token tok){
    if (someLexics[index].token == tok){
        index++;
        return TRUE;
    }
    else{
        return FALSE;
    }
}
