/**
 * @file FindSimilar.h
 * @author Steven Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief Group Analysis. Use Jaccob's similarity with hash table to identify similar strings.
 * @version 0.1
 * @date 2021-06-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FINDSIMILAR_H
#define FINDSIMILAR_H
#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "GroupAnalysis.h"

/**********Constant Variable***********/
#define Q_RABIN 170001
#define D_RABIN 36
#define INIT_SPURIOUS_COUNT 3
#define INIT_UNIQUE_TOKEN_SIZE 10
#define TOKEN_STRING_LENGTH 1000
#define ULONG  long
#define UINT  int
#define USHORT unsigned short
#define ushort unsigned short

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "api.h"

typedef struct HashStack {
    ushort m[Q_RABIN][MAX_N_MAIL];
    ushort len[Q_RABIN];
} HashStack;

static HashStack* hstack;
static int num_unique[MAX_N_MAIL];

static void init_FS(void){
    hstack = (HashStack*)calloc(1, sizeof(HashStack));
    for(int i=0;i<MAX_N_MAIL;i++){
        num_unique[i] = 0;
    }
};

static void kill_FS(void){
    free(hstack);
};

static void proc_FS(mail* mails, int n_mail){
    int ID;
    for(int i=0;i<n_mail;i++){
        ID = mails[i].id;
        append_mHash(mails, ID);
    }
}

static void append_mHash(mail* mails, int ID){
    char* text = mails[ID].content;

}

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, long* Hash){
    char c;
    int asc; //ascii number
    *Hash = 0; //reset hash value
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }

    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token
    *Hash = Hash_RK(token);

    return iStr;
}



#endif