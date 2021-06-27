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

/**********Constant Variable***********/
#define Q_RABIN 17388807
#define D_RABIN 86
#define TOKEN_STRING_LENGTH 4000
#define C1 1
#define C2 1
//#define INIT_UNIQUE_TOKEN_NUM 
#define ULONG  long
#define UINT  int
#define USHORT unsigned short
#define ushort int

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "api.h"

/**Linked list**/
typedef struct ndl {
    ushort id;
    struct ndl* nxt;
} ndl;

typedef struct lklist {
    ndl* str;
    ndl* end;
    char token[400];
} lklist;

typedef struct lkmem {
    ndl* node;
    int used;
    int max;
} lkmem;

void init_lkmem(lkmem* lkm, int size);
void kill_lkmem(lkmem* lkm);
ndl* get_ndl_mem(lkmem*lkm);
void append_lk(lklist* list, ushort val, lkmem* lkm);




typedef struct Matrix_ushort {
    lklist* map;
    int nrow;
} Matrix_ushort;

void init_Matrix_ushort(Matrix_ushort* M, int nrow);
void kill_Matrix_ushort(Matrix_ushort* M);



typedef struct infoFS{
    Matrix_ushort hstack;
    double* num_unique;
    double* SimList;
    bool* isVis;
    lkmem lkm;//nodes memory
    int* resetID;
    Matrix_ushort tokenID;
} infoFs;


void init_FS(infoFs* info);
void kill_FS(infoFs* info);

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash);
void append_mHash(infoFs* info,mail* mails, int ID);

void proc_FS(infoFs* info, mail* mails, int n_mail);


int Hash_RK(char s[]);

void answer_FS(infoFs*info, mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist);
void register_hash(infoFs* info, int ID, int* hash, char token[], int i);


#endif