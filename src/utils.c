#include "utils.h"

/************Math************/

//Choose the bigger one
int argmax(int a, int b)
{
   if (a>b){
       return 0;
   }
   else{
       return 1;
   }
}

bool inDomainInt(int val, int lower, int upper){
    if(val<=upper && val>=lower)
        return true;
    else
        return false;
}

/************Tokenize************/

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

/************Generic Array************/
void init_uArray(uArray* arr, int eleSize){
    byte* mem = (byte*)malloc(eleSize*INIT_NUM_ARRAY_ELEMENT);
    
    //Check memory is allocated
    if(mem==NULL){
        fprintf(stderr, "Stack Init Error: Insufficient Memory.\n");
        exit(1);
    }

    //Initiation
    arr->eleSize = eleSize;
    arr->len = 0;
    arr->memory = mem;
    arr->num_maxEle=INIT_NUM_ARRAY_ELEMENT;
}

int len_uArray(uArray* arr){
    return arr->len;
}

void get_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length $d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    
    int start = (i-1)*arr->eleSize;
    for(int j=0;j<arr->eleSize;j++){
        *(byte*)(item+i) = *(arr->memory+start+i);
    }
}

void remove_uArray(uArray* arr, int i){

}

void insert_uArray(uArray* arr, void* item){

}

void append_uArray(uArray* arr, void* item){

}

void kill_uArray(uArray* arr){

}

/************Generic Stack************/

void init_uStack(uStack *s, int eleSize){
    byte * memory = (byte*)malloc(eleSize*INIT_NUM_ARRAY_ELEMENT);
    if(memory == NULL){
        fprintf(stderr, "Stack Init Error: Insufficient Memory.\n");
        exit(1);
    }

    /*Initialize*/
    s->eleSize = eleSize;
    s->top = 0; //index
    s->len = 0;
    s->memory = memory;
    s->num_maxEle = INIT_NUM_ARRAY_ELEMENT;
}

