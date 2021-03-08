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
        if(match(IDENTIFIER)){

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

}

_Bool body(){

}

_Bool statementList(){

}

_Bool statement(){

}

_Bool whileLoop(){

}

_Bool returnStatement(){

}

_Bool assignment(){

}

_Bool expression(){

}

_Bool term(){

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
