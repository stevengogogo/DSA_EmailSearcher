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

typedef struct Matrix_ushort {
    ushort** m;
    ushort* len;
    int nrow;
    int ncol;
} Matrix_ushort;

void init_Matrix_ushort(Matrix_ushort* M, int nrow, int ncol);
void kill_Matrix_ushort(Matrix_ushort* M);

static Matrix_ushort hstack;
static double* num_unique;
static double* SimList;



void init_FS(void);
void kill_FS(void);

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash);
void append_mHash(mail* mails, int ID);

void proc_FS(mail* mails, int n_mail);

void similarity(mail* mails, int ID,int n_mail);
int Hash_RK(char s[]);

void answer_FS(mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist);


#endif