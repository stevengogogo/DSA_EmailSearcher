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
#define Q_RABIN 17003
#define D_RABIN 29
#define PERM_MOD 17009
#define MAX_TOKEN_LEN 1000
#define T_MINIHASH_PERM 40
#define MAX_TOKEN_NUM 10000

long PowerArray[MAX_TOKEN_LEN];
static long PrimeArray[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149};


typedef struct TxtSmry{
    Matrix SglM; //Shingle Matrix
} TxtSmry;



/*Rabin Karp Hashing*/
void init_PowerArray(long* arr, int len, long base, long mod);
long Hash_RK(char tokenStr[]);

/*Permuation*/
/** Tabulation hashing*/
long hash_tabu(long x, long a, long b);

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, long* Hash);
/* x power n*/
long power_long(long x, int n);

/*Minihashing*/
void set_Sgl_Vec(Matrix* SglM, char text[], int ID, long* a, long* b, short* hashMap);
void miniHash(Matrix* SglM, short* hashmap, long a, long b, int iperm, int ID);

/**Main API*/
void init_FindSimilar(TxtSmry* smry, int n_mails);
void kill_FindSimilar(TxtSmry* smry);
void Preprocess_FindSimilar(TxtSmry* smry, mail*  mails, int n_mails);
double similarity(Matrix* sglM, int IDbase, int IDcmp);
void answer_FindSimilar(TxtSmry* smrys, int ID, double threshold, mail* mails, int n_mails, int* SimList, int* lenSim);


#endif