/**
 * @file GroupAnalysis.h
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
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include "utils.h"
#include "api.h"

/**********Constant Variable***********/
#define Q_MODULO 100000
#define D 252
#define INIT_SPURIOUS_COUNT 10
#define INIT_NONZERO_SIZE 100



/**
 * @brief Information for global memory storage.
 * @note This structure is to provide public memory, and minimize the use of @ref malloc
 * @param LOC_top_unused index of unused memory
 * @param LOC_ARRAY array for store location data
 * @param LEN capacity of the memory
 */
static struct MEMORY {
    int top_unused;
    int* ARRAY;
    int LEN;
} MEMORY;

static struct MEMORY loc_mem;
static struct MEMORY nonZero_mem;

/**
 * @brief 
 * @note Each email is using the hash map with @ref Q_MODULO size, and each slot has @ref INIT_SPURIOUS_COUNT location data.
 * @param loc_mem global struct for memory storage
 * @param num_mail number of email
 */
void init_MEM(struct MEMORY* mem, int num_mail);

/** Recycle the memory of @ref LOC_MEM*/
void kill_MEM(struct MEMORY* mem);


/******Token and Structure*******/
/** Token Information*/
typedef struct TokenInfo{
    int occur;
    int loc[1];//locations
} TokenInfo;

/** Text Summary*/
typedef struct TxtSmry{
    TokenInfo token[Q_MODULO];
    dymArr nonZero; //Token start points
    int nToken; // unique token number
    char* text; // Text
    bool synced; // Check the information is updated
} TxtSmry;


void init_TokenInfo(TokenInfo* tkf);
void init_TokenInfo_arr(TokenInfo* tkf, int len);
void kill_TokenInfo(TokenInfo* tkf);
void kill_TokenInfo_arr(TokenInfo* tkf, int len);

/** Intiate text summary*/
void init_TxtSmry(TxtSmry* smry);
/** Initiate array of text summary*/
void init_TxtSmry_arr(TxtSmry** smry, int len);
/** Recycle TxtSmry*/
void kill_TxtSmry(TxtSmry* smry);
/** Kill array of TxtSmry.*/
void kill_TxtSmry_arr(TxtSmry* smry, int len);

/******Hash*******/
/** Get token hash
 * @param iStr Pin for reading the string
 * @return iEnd. the end of the token
*/
int popTokenHash(char message[], char token[], int iStr, int* Hash);
/** Update the hash value with new character.*/
int updateHash(char c, int Hash_cur, int q_cur, int d);

/**********Main API************/
/** Preprocessing: Summarize the mails*/
TxtSmry* Preprocess_GroupAnalysis(mail*  mails, int n_mails);

/**
 * @brief Check the similarity of two messages is exceeding threshold.
 * 
 * @param smry1 Message 1.
 * @param smry2 Message 2.
 * @param threshold the threshold of similarity `[0,1]`
 * @note swich `smry1` and `smry2` will not affect the result.
 * @return true The jaccob's similarity of `smry1` and `smry2` is beyond the threshold
 * @return false otherwise
 */
bool is_similar(TxtSmry* smry1, TxtSmry* smry2, int threshold);

/************Helper Functions*****************/
/**
 * @brief Get Jaccob's similarity from two summaries ( @ref TxtSmry). with `O(min(num_token))`
 * 
 * @note The inputs can be switched and get the same result. See https://github.com/stevengogogo/DSA_EmailSearcher/discussions/42 for Jaccob similarity 
 * @return int The jaccob similarity `[0,1]`
 */
int similarity_val(TxtSmry* smry1, TxtSmry* smry2);

/** Maximum Jaccob's similarity with `O(1)` speed.
 * @note This function uses:  MaxSimlarity = min(nToken1, nToken2) / (nToken1 + nToken2 - min(nToken1, nToken2) ). To accquire the maximum similarity.
*/
int max_similarity_val(TxtSmry* smry1, TxtSmry* smry2);


#endif