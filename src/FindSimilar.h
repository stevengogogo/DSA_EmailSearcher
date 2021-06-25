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
#define Q_RABIN 170001
#define D_RABIN 36
#define INIT_SPURIOUS_COUNT 3
#define INIT_UNIQUE_TOKEN_SIZE 10
#define TOKEN_STRING_LENGTH 1000
#define ULONG  long
#define UINT  int
#define USHORT unsigned short

/**Helper function**/
/************Dynamic Array (Int) Stack**************/


/**
 * @brief Information for global memory storage.
 * @note This structure is to provide public memory, and minimize the use of @ref malloc
 * @param LOC_top_unused index of unused memory
 * @param LOC_ARRAY array for store location data
 * @param LEN capacity of the memory
 */
typedef struct MEMORY_SHORT {
    ULONG top_unused;
    USHORT* ARRAY;
    ULONG LEN;
} MEMORY_SHORT;

typedef struct MEMORY_ULONG {
    ULONG top_unused;
    int* ARRAY;
    ULONG LEN;
} MEMORY_ULONG;

typedef struct TokenInfo {
    USHORT count;
    USHORT loc[INIT_SPURIOUS_COUNT];//location of the hash on string
} TokenInfo;


static struct MEMORY_ULONG existTokens_mem;


/**
 * @brief 
 * @note Each email is using the hash map with @ref Q_RABIN size, and each slot has @ref INIT_SPURIOUS_COUNT location data.
 * @param loc_mem global struct for memory storage
 * @param num_mail number of email
 */
void init_MEM_ULONG(struct MEMORY_ULONG* mem, ULONG len);
void init_MEM_SHORT(struct MEMORY_SHORT* mem, ULONG len);

/** Recycle the memory of @ref LOC_MEM*/
void kill_MEM_ULONG(struct MEMORY_ULONG* mem);
void kill_MEM_SHORT(struct MEMORY_SHORT* mem);


/******Token and Structure*******/


/** Text Summary*/
typedef struct TxtSmry{
    int id;
    TokenInfo token[Q_RABIN]; //len = Q_MODULE
    int* existTokens; //Exist Token
    dymArr* existTokens_DymArr;
    int nToken; // unique token number
    char* text; // Text
    bool synced; // Check the information is updated
    bool isExistTokens_DymArr;
    int maxSpurious;
} TxtSmry;


/** Intiate text summary*/
void init_TxtSmry(TxtSmry* smry, int hashMapsize);
/** Initiate array of text summary*/
void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize);
void append_hash_TxtSmry(TxtSmry* smry, int hash);
void _add_unique_hashlist(TxtSmry* smry, int hash);
int get_unique_hashlist(TxtSmry* smry, int i);
/** Kill array of TxtSmry.*/
void kill_TxtSmry_arr(TxtSmry* smry, int len);


/******Hash*******/
/** Get token hash
 * @param iStr Pin for reading the string
 * @note Modified from @ref popToken.
 * @return iEnd. the end of the token
*/
int popTokenHash(char message[], char token[], int iStr, int* Hash);
/**
 * @brief Update the hash value with new character.
 * @param c character to append
 * @param Hash_cur current hash value
 * @return int updated hash value.
 */
int updateHash(char c, int Hash_cur);

/**********Main API************/

/**Initialte Memory for FindSimilar*/
void Init_FindSimilar(TxtSmry**, int n_mails);

/** Preprocessing: Summarize the mails*/
void Preprocess_FindSimilar(TxtSmry*, mail*  mails, int n_mails);

/*GC for FindSimilar problem*/
void kill_FindSimilar(TxtSmry* smrys, int n_mails);


/******************************/



/*********Hash*********/
/** Summarize a mail*/
void summarize_content(TxtSmry* smry, mail* m);
/** Add text and hashing*/
void summarize_hash(TxtSmry* smry, char* text);



/******Jaccob Similarity*****/

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
void answer_FindSimilar(TxtSmry* smrys, int ID, double threshold, int n_mails, int* SimList, int* lenSim);


/************Helper Functions*****************/
/**
 * @brief Get Jaccob's similarity from two summaries ( @ref TxtSmry). with `O(min(num_token))`
 * 
 * @note The inputs can be switched and get the same result. See https://github.com/stevengogogo/DSA_EmailSearcher/discussions/42 for Jaccob similarity 
 * @return int The jaccob similarity `[0,1]`
 */
double similarity_val(TxtSmry* smry1, TxtSmry* smry2);

/** Maximum Jaccob's similarity with `O(1)` speed.
 * @note This function uses:  MaxSimlarity = min(nToken1, nToken2) / (nToken1 + nToken2 - min(nToken1, nToken2) ). To accquire the maximum similarity.
*/
int max_similarity_val(TxtSmry* smry1, TxtSmry* smry2);



#endif