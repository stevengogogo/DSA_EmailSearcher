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
#define INIT_SPURIOUS_COUNT 3
#define INIT_UNIQUE_TOKEN_SIZE 100
#define ULONG unsigned long long
#define USHORT unsigned short

/**Helper function**/
/************Dynamic Array (Int) Stack**************/
//dynamic array
typedef struct{
    int len;
    int size;
    ULONG* i;
} dymArr_ULONG;

//init and kill
void init_dymArr_ULONG(dymArr_ULONG*, ULONG size);
void kill_dymArr_ULONG(dymArr_ULONG*);
void resize_dymArr_ULONG(dymArr_ULONG*, ULONG new_max_size);

//clear
void clear_Arr_ULONG(dymArr_ULONG*);

//append
/**Append at last*/
void append_dymArr_ULONG(dymArr_ULONG*, ULONG val);
/** Get the item of arr[i]*/
int get_item_ULONG(dymArr_ULONG, ULONG i);
/** Get the last item
 * @return last element. If no item left, return `EMTY_QUE_SIG`
*/
int pop_item_ULONG(dymArr_ULONG*);


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
    ULONG* ARRAY;
    ULONG LEN;
} MEMORY_ULONG;

typedef struct TokenInfo {
    USHORT count;
    USHORT loc[INIT_SPURIOUS_COUNT];//location of the hash
} TokenInfo;

static struct MEMORY_SHORT token_hashmaps;
static struct MEMORY_ULONG existTokens_mem;


/**
 * @brief 
 * @note Each email is using the hash map with @ref Q_MODULO size, and each slot has @ref INIT_SPURIOUS_COUNT location data.
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
    TokenInfo token[Q_MODULO]; //len = Q_MODULE
    ULONG* existTokens; //Exist Token
    dymArr_ULONG* existTokens_DymArr;
    int nToken; // unique token number
    char* text; // Text
    bool synced; // Check the information is updated
    bool isExistTokens_DymArr;
} TxtSmry;


/** Intiate text summary*/
void init_TxtSmry(TxtSmry* smry, int hashMapsize);
/** Initiate array of text summary*/
void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize);
void append_hash_TxtSmry(TxtSmry* smry, ULONG hash);
void add_unique_hashlist(TxtSmry* smry, ULONG hash);
ULONG get_unique_hashlist(TxtSmry* smry, int i);
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

/**Initialte Memory for FindSimilar*/
void Init_FindSimilar(TxtSmry**, int n_mails);

/** Preprocessing: Summarize the mails*/
TxtSmry* Preprocess_FindSimilar(mail*  mails, int n_mails);

/*GC for FindSimilar problem*/
void kill_FindSimilar(TxtSmry* smrys, int n_mails);


/******************************/



/*********Hash*********/
void summarize_content(TxtSmry* smry, mail* m);
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