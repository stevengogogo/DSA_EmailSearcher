#include "stringParse.h"


int popToken(char message[], char token[], int iStr){
    char c;
    int asc; //ascii number
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number
        ++iStr;

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
        }
        else{
            if (i==0)
                continue;
            else 
                break;
        }
    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token

    return iStr;
}

bool isRegularExpr_ASCII(int asc){
    if(isNumber_ASCII(asc))
        return true;
    else if(isUpperCase_ASCII(asc))
        return true;
    else if(isLowerCase_ASCII(asc))
        return true;
    else
        return false;
}

bool isNumber_ASCII(int asc){
    return inDomainInt(asc, 48, 57);
}

bool isUpperCase_ASCII(int asc){
    return inDomainInt(asc, 65, 90);
}

bool isLowerCase_ASCII(int asc){
    return inDomainInt(asc, 97, 122);
}