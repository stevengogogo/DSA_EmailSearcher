#include "api.h"
//#include "api.h"
#ifndef EXPRESSIONMATCH_H
#define EXPRESSIONMATCH_H
/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * @note 
 * Reference
 * 1. Universal Stack is modified from: https://github.com/igniting/generic-stack
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h> // tolower
#define INIT_NUM_ARRAY_ELEMENT 10
#define EMTY_QUE_SIG -121242
#define MAX_N_MAIL 11000
typedef unsigned char byte;

/************Math************/

/**
 * @brief Get arg max
 * 
 * @param a 
 * @param b 
 * @return int 
 */
int argmax(int a,int b);

/**
 * Check `val` is in [lower,upper]
 */
bool inDomainInt(int val, int lower, int upper);

/************Tokenize************/

/**
 * @brief Pop token from message. 
 * 
 * @param token Buffer string. Token will be saved here. `\0` if no token left
 * @param message main text
 * @param iStr reading head
 * @return int updated reading head `iStr`. -1: end of string
 */
int popToken(char message[], char token[], int iStr);

/**
 * @brief Judge a character belong to regular expression or not
 * @note Regular expression: %[a-zA-Z0-9]
 * @return true 
 * @return false 
 */
bool isRegularExpr_ASCII(int);
bool isNumber_ASCII(int);
bool isUpperCase_ASCII(int);
bool isLowerCase_ASCII(int);
/**
 * @brief [0-9] -> [0-9]; [a-z] -> [10-35]; otherwise: ASCII
 * @param c 
 * @return int 
 */
int char2num(char c);

/************Dynamic Array (Int) Stack**************/
//dynamic array
typedef struct{
    int len;
    int size;
    int* i;
} dymArr;

//init and kill
void init_dymArr(dymArr*, int size);
void kill_dymArr(dymArr*);
void resize_dymArr(dymArr*, int new_max_size);

//clear
void clear_Arr(dymArr*);

//append
/**Append at last*/
void append_dymArr(dymArr*, int val);
/** Get the item of arr[i]*/
int get_item(dymArr, int i);
/** Get the last item
 * @return last element. If no item left, return `EMTY_QUE_SIG`
*/
int pop_item(dymArr*);

/*************Queue************/
typedef struct{
    dymArr arr;
    int head;
    int tail;
} que;

que init_que(int size);
void kill_que(que*);
void enque(que*, int val);
int deque(que*);
int peek_que(que*);

/************Generic Dynamic Array************/

/** Generic copy*/
void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size);

/** Universal dynamic Array*/
typedef struct uArray{
    int len;
    size_t eleSize;
    byte* memory;
    int num_maxEle;
} uArray;

void init_uArray(uArray* arr, size_t eleSize);
int len_uArray(uArray* arr);
void get_uArray(uArray* arr, int i,void* item);
void set_uArray(uArray* arr, int i,void* item);
void remove_uArray(uArray* arr, int i);
void insert_uArray(uArray* arr, int i,void* item);
void append_uArray(uArray* arr, void* item);
void update_size_uArray(uArray* arr, int new_max_item);
void kill_uArray(uArray* arr);

/*Sorting*/
/** * QuickSort to increasing order. Reference: This function is modified from https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
void quicksort(int arr[], int left, int right);

/** * Combine fragments. This function is modifed from: https://openhome.cc/Gossip/AlgorithmGossip/QuickSort3.htm#C */
int partition(int number[], int left, int right);

/** * Switch the value store in `x` and `y`. */
void swap(int* x, int* y);

/*Matrix*/
typedef struct Matrix{
    int* m;
    int nrow;
    int ncol;
} Matrix;

void init_Matrix(Matrix* M, int nrow, int ncol);
void kill_Matrix(Matrix* M);
void set_Matrix(Matrix* M, int r, int c, int val);
int get_Matrix(Matrix*M, int r, int c);

#endif

#endif
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
//#include "api.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

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
#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H
//#include "api.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define SIZE 1000001

typedef struct Node{
	char* name;
	int parentIdx;
	int size;
}node;
/**/
static node* makeset(){
	node* arr = (node*)malloc(sizeof(node)* SIZE*10);
	assert(arr!=NULL);
	return arr;
}

static int hash(char word[]){
	int i = 0;
	int RK = 0;
	while(word[i]!='\0'){
		RK = (62*RK + (int)word[i])%SIZE;
		i++;
	}
	return abs(RK)%SIZE;
}

static int findIdx(node*set, char word[]){
	int hashed = hash(word);
	while(set[hashed].name){
		if(strcmp(set[hashed].name, word)!=0){
			hashed = (hashed+1)%SIZE;
		}else return hashed;
	}
	return hashed;
}

static void inputTable(node* set, char word[]){
	int hashed = findIdx(set, word);
	if(!set[hashed].name){
		set[hashed].name = word;
		set[hashed].parentIdx = hashed;
		set[hashed].size = 1;
	}
}

static int findset(node *set, int hashed){

	if(set[hashed].parentIdx!=hashed){
		set[hashed].parentIdx = findset(set,set[hashed].parentIdx);
	}
	return set[hashed].parentIdx;
}

static void link_GA(node *set, int nodex, int nodey ,int *count, int *max){
	if(set[nodex].size>set[nodey].size){
		set[nodey].parentIdx = nodex;
		set[nodex].size += set[nodey].size;
		if(set[nodey].size>=2){
			*count-=1;
		}
		set[nodey].size = 0;
		if(set[nodex].size>*max){
			*max = set[nodex].size;
		}
	}else{
		set[nodex].parentIdx = nodey;
		if(set[nodex].size==set[nodey].size&&set[nodex].size==1){
			*count += 1;
		}
		set[nodey].size += set[nodex].size;
		if(set[nodex].size>=2){
			*count -= 1;
		}
		set[nodex].size = 0;
		if(set[nodey].size>*max){
			*max = set[nodey].size;
		}
	}
}

static void setunion(node*set, char word1[],char word2[], int* count, int* max){
	inputTable(set, word1);
	inputTable(set, word2);
	int nodex = findIdx(set, word1);
	int nodey = findIdx(set, word2);
	int idxx = findset(set, nodex);
	int idxy = findset(set, nodey);
	if(idxx!=idxy){
		link_GA(set, idxx, idxy, count, max);
	}
}

static void answer_GroupAnalysis(int mid[], int len, mail* mails, int* list, int* nlist){
	node* arr = makeset();
	int count = 0;
	int max = 0;

	for(int i = 0; i < len; i++){
		setunion(arr,mails[mid[i]].from, mails[mid[i]].to, &count, &max);
	}
 
  //ANS
  list[0] = count;
  list[1] = max;
  *nlist = 2;

  free(arr);

}

#endif

#include <stdio.h>
#include <time.h>

int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    TxtSmry* smrys;
    int* list = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int nlist;
    int threshold;
    int mid;

    //Initiation

    //FS//
	api.init(&n_mails, &n_queries, &mails, &queries);   
    //Init_FindSimilar(&smrys, n_mails);

    //GA//

    //Preprocessing
    //Preprocess_FindSimilar(smrys, mails, n_mails);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
            /*
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process
            answer_FindSimilar(smrys, mid, threshold, n_mails, list, &nlist);

            //answer
            if(nlist>0){
                api.answer(queries[i].id, list, nlist);
            }
            else{api.answer(queries[i].id,NULL,0);}
            */
        }
        
        //Expression Match
        else if(queries[i].type == expression_match){
		    //api.answer(queries[i].id, NULL, 0);
        }

        //Group Analysis
        else {

            answer_GroupAnalysis(queries[i].data.group_analyse_data.mids, queries[i].data.group_analyse_data.len,mails, list, &nlist);
            
            api.answer(queries[i].id, list, nlist);

            
        }
    }

    //Garbage Collection
    //kill_FindSimilar(smrys, n_mails);
    free(mails);
    free(queries);
    free(list);

    return 0;
}

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

int char2num(char c){
    if(isNumber_ASCII(c)){
        return (int)c - '0';
    }
    else if(isLowerCase_ASCII(c)){
        return (int)c - 'a' + 10;
    }
    else{
        return (int)c;
    }
}

/********Dynamic Array (Int) stack*********/

void init_dymArr(dymArr* arr, int size){
    assert(size>=1);
    int* is = (int*)malloc(size*sizeof(int));
    if(is==NULL){
        fprintf(stderr, "Init Error: Insufficient Memory.\n");
        exit(1);
    }

    arr->i = is;
    arr->len = 0;
    arr->size = size;
}

void kill_dymArr(dymArr* arr){
    arr->size=0;
    arr->len=0;
    free(arr->i);
};

void resize_dymArr(dymArr* arr, int new_max_size){
    arr->size = new_max_size;
    arr->i = realloc(arr->i, sizeof(int)*new_max_size);
}

void clear_Arr(dymArr* arr){
    arr->len = 0;
}

void append_dymArr(dymArr* arr, int val){
    ++(arr->len);
    //Augement size

    if((arr->len+1) > arr->size){
      int new_size = (arr->size)*2 + 1;
      arr->i = realloc(arr->i, sizeof(int)*new_size);
      arr->size = new_size;
      if(arr==NULL){
        fprintf(stderr, "Append Error: Insufficient Memory.\n");
        exit(1);
       }
    }

    arr->i[arr->len - 1] = val;
}

int get_item(dymArr arr, int i){
    return arr.i[i];
}

int pop_item(dymArr* arr){
    if(arr->len==0)
        return EMTY_QUE_SIG;
    int val = arr->i[arr->len-1];
    --arr->len;

    return val;
}

/*************Queue************/

que init_que(int size){
    que q;
    init_dymArr(&q.arr,size);
    q.head = -1;
    q.tail = -1;
    return q;
}

void kill_que(que* q){
    kill_dymArr(&q->arr);
}

void enque(que* q, int val){
    append_dymArr(&q->arr, val);
    if(q->head == -1){ //first element
        ++(q->head);
    }
    q->tail = q->arr.len - 1;
}

int deque(que* q){
    if(q->head > q->tail || q->head==-1){
        return EMTY_QUE_SIG;
    }

    int val = get_item(q->arr, q->head);
    ++(q->head);
    return val;
}

int peek_que(que* q){
    if(q->head > q->tail || q->arr.len==0)
        return EMTY_QUE_SIG;
    else 
        return q->arr.i[q->head];
}

/************Generic Array************/

void copy_item_array(void* dstArr, int locDst,void* srcArr, int locSrc, size_t size){
    //Start point
    int start_dst = locDst*size;
    int start_src = locSrc*size;

    if (size=sizeof(int)){
        *(int*)(dstArr+start_dst) = *(int*)(srcArr+start_src);
    }
    else if (size=sizeof(long)){
        //printf("f");
        *(long*)(dstArr+start_dst) = *(long*)(srcArr+start_src);
    }
    else{
        //Copy
        memcpy((byte*)(dstArr+start_dst), (byte*)(srcArr+start_src), size);
        //*(byte*)(srcArr+j+start_src) = *(byte*)(dstArr+j+start_dst);
    }
}

void init_uArray(uArray* arr, size_t eleSize){
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
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(item, 0, arr->memory, i, arr->eleSize);
}

void set_uArray(uArray* arr, int i,void* item){
    //Check i domain
    if (i>=len_uArray(arr) || i<0){
        fprintf(stderr, "Invalid index with array length %d. Got i=%d\n", arr->len, i);
        exit(1);
    }

    //Copy item
    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void remove_uArray(uArray* arr, int I){
    
    for(int i=arr->len-1;i>I;i--){
        copy_item_array(arr->memory, i-1, arr->memory, i, arr->eleSize);
    }

    --arr->len;

    //Shrink memory
    if(arr->len < arr->num_maxEle/2-10){
        update_size_uArray(arr, arr->num_maxEle/2);
    }
}

void insert_uArray(uArray* arr, int I,void* item){

    //For empty array 
    if(arr->len == 0 && I==0){
        append_uArray(arr, item);
        return;
    }

    ++arr->len;
    //Extend memory
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }

    //Shift right
    for(int i=I;i<arr->len-1;i++){
        copy_item_array(arr->memory, i+1, arr->memory, i, arr->eleSize);
    }

}

void append_uArray(uArray* arr, void* item){
    ++arr->len;
    //Augment size
    if(arr->len == arr->num_maxEle){
        update_size_uArray(arr, arr->num_maxEle*2+1);
    }   

    copy_item_array(arr->memory, arr->len-1, item, 0, arr->eleSize);
}

void update_size_uArray(uArray* arr, int new_max_item){
    arr->num_maxEle = new_max_item;
    arr->memory = realloc(arr->memory, arr->eleSize*arr->num_maxEle);
    if(arr->memory==NULL){
        fprintf(stderr, "Update size error: Invalid Memory allocation with size %d\n", arr->num_maxEle);
        exit(1);
    }
}

void kill_uArray(uArray* arr){
    free(arr->memory);
    arr->eleSize = 0;
    arr->len = 0;
    arr->num_maxEle = 0;
}

/**Sorting**/

void quicksort(int arr[], int left, int right){
    if (left < right){
        int q = partition(arr, left, right);
        quicksort(arr, left, q-1);
        quicksort(arr, q+1, right);
    }
}

int partition(int arr[], int left, int right){
    int i = left-1;
    int j;
    for(j=left; j < right; j++){
        if(arr[j] <= arr[right]){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i+1], &arr[right]);

    return i+1;
}

void swap(int* x, int* y){
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

/*matrix*/
void init_Matrix(Matrix* M, int nrow, int ncol){
    int* m = (int*)calloc(ncol*nrow, sizeof(int));
    M->m = m;
    M->ncol = ncol;
    M->nrow = nrow;
}

void kill_Matrix(Matrix* M){
    free(M->m);
    M->ncol = 0;
    M->nrow = 0;
}

void set_Matrix(Matrix* M, int r, int c, int val){
    int offset = r*M->ncol + c;
    M->m[offset] = val;
}

int get_Matrix(Matrix*M, int r, int c){
    int offset = r*M->ncol + c;
    return M->m[offset];
}

void init_MEM_ULONG(struct MEMORY_ULONG* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (int*)calloc( mem->LEN, sizeof(int));
    assert(mem->ARRAY != NULL);
    mem->top_unused = 0;
}
void init_MEM_SHORT(struct MEMORY_SHORT* mem, ULONG len){
    mem->LEN = len;
    //mem->ARRAY = (int*)malloc(mem->LEN*sizeof(int));
    mem->ARRAY = (USHORT*)calloc( mem->LEN, sizeof(USHORT));
    assert(mem->ARRAY != NULL);
    mem->top_unused = 0;
}

void kill_MEM_ULONG(struct MEMORY_ULONG* mem){
    free(mem->ARRAY);
    mem->ARRAY = NULL;
    mem->LEN = 0;
    mem->top_unused = EMTY_QUE_SIG;
}

void kill_MEM_SHORT(struct MEMORY_SHORT* mem){
    free(mem->ARRAY);
    mem->ARRAY = NULL;
    mem->LEN = 0;
    mem->top_unused = EMTY_QUE_SIG;
}

/*******HASH*******/
int popTokenHash(char message[], char token[], int iStr, int* Hash){
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
            *Hash = updateHash(c, *Hash);
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

    return iStr;
}

int updateHash(char c, int Hash_cur){
    int HashUPD;
    HashUPD = Hash_cur * D_RABIN + char2num(c);
    HashUPD = HashUPD % Q_RABIN;
    return HashUPD;
}

/*******Main API****/
void Init_FindSimilar(TxtSmry** smrys, int n_mails){
    ULONG nmail = (ULONG)n_mails;
    //Occupied hash index
    init_MEM_ULONG(&existTokens_mem, nmail*INIT_UNIQUE_TOKEN_SIZE);
    init_TxtSmry_arr(smrys, nmail, Q_RABIN);

}

void init_TxtSmry(TxtSmry* smry, int hashMapsize){
    //Check memory is enough
    assert(existTokens_mem.top_unused+INIT_UNIQUE_TOKEN_SIZE <= existTokens_mem.LEN);

    smry->existTokens = &existTokens_mem.ARRAY[existTokens_mem.top_unused];

    existTokens_mem.top_unused += INIT_UNIQUE_TOKEN_SIZE;

    smry->nToken = 0;
    smry->existTokens_DymArr = NULL;
    smry->text = NULL;
    smry->synced = false;
    smry->isExistTokens_DymArr = false;
    smry->maxSpurious = 0;
}

void init_TxtSmry_arr(TxtSmry** smry, int len, int hashmapSize){
    int pin_memToken = 0;
    *smry = (TxtSmry*)calloc(len, sizeof(TxtSmry));
    assert(*smry !=NULL);
    for(int i=0;i<len;i++){
        init_TxtSmry(&(*smry)[i], hashmapSize);
    }
}

void append_hash_TxtSmry(TxtSmry* smry, int hash){
    if(smry->token[hash].count==0){
        _add_unique_hashlist(smry, hash);
    }
    //Count is update here
    ++smry->token[hash].count;
}

void _add_unique_hashlist(TxtSmry* smry, int hash){
    //Augment array
    if(smry->nToken==INIT_UNIQUE_TOKEN_SIZE){
        smry->existTokens_DymArr = (dymArr*)malloc(sizeof(dymArr));
        init_dymArr(smry->existTokens_DymArr, 2*INIT_UNIQUE_TOKEN_SIZE);

        //Set flag    
        assert(smry->isExistTokens_DymArr == false); //only do this once
        smry->isExistTokens_DymArr = true;
    }

    //Data [INIT...]
    if(smry->isExistTokens_DymArr){
        append_dymArr(smry->existTokens_DymArr, hash);
    }
    else{//Data [0,..INIT-1]
        smry->existTokens[smry->nToken] = hash;
    }
    ++smry->nToken;
}

int get_unique_hashlist(TxtSmry* smry, int i){
    int uniHash;
    if (i<INIT_UNIQUE_TOKEN_SIZE){
        uniHash = smry->existTokens[i];
    }
    else{
        int len = smry->existTokens_DymArr->len;
        assert(i-INIT_UNIQUE_TOKEN_SIZE < len);
        uniHash = smry->existTokens_DymArr->i[i-INIT_UNIQUE_TOKEN_SIZE];
    }
    return uniHash;
}

void kill_TxtSmry_arr(TxtSmry* smry, int len){
    for(int i=0;i<len;i++){
        if(smry[i].isExistTokens_DymArr){
            kill_dymArr(smry[i].existTokens_DymArr);
            free(smry[i].existTokens_DymArr);
        }
    }
    free(smry);
}

void Preprocess_FindSimilar(TxtSmry* smrys, mail*  mails, int n_mails){

    for(int i=0;i<n_mails;i++){
        summarize_content(&smrys[i], &mails[i]);
    }
}

void kill_FindSimilar(TxtSmry* smrys, int len){
    kill_TxtSmry_arr(smrys, len);
    kill_MEM_ULONG(&existTokens_mem);
}

void summarize_content(TxtSmry* smry, mail* m){
    smry->id = m->id;
    summarize_hash(smry, m->content);
    smry->synced = true;
}

void summarize_hash(TxtSmry* smry, char* text){
    //Record original text
    smry->text = text;
    //Retrieving Tokens
    char token[TOKEN_STRING_LENGTH];
    char tkH[TOKEN_STRING_LENGTH]; //history token
    int iloc;
    int iStrH = 0;
    int iStr = 0; //Current pin
    int iNxt; //Next pin
    int hash;
    bool next = false;

    while(1){
        next = false;
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt == -1){//no token left
            break;
        }

        //Check new token is duplicate
        for(int i=0;i<INIT_SPURIOUS_COUNT;i++){
            if(i<smry->token[hash].count){
                iStrH = smry->token[hash].loc[i];
                iStrH = popToken(text, tkH, iStrH);
                if(strncmp(tkH, token, strlen(token))==0){
                    next = true;
                    break;
                }
            }
            else{
                break;
            }
        }

        if (next){
            //Next token
            iStr = iNxt;
            continue;
        }
   

        //Append New Hash Until FULL
        if(smry->token[hash].count<INIT_SPURIOUS_COUNT){
            iloc = smry->token[hash].count;
            smry->token[hash].loc[iloc] = iStr;
        }

        //Append unique hash 
        //if(smry->token[hash].count==0){//unique token
        append_hash_TxtSmry(smry, hash);
        //}

        //Next token
        iStr = iNxt;

        //Check spurious overflow
        if(smry->maxSpurious<smry->token[hash].count && smry->token[hash].count>1){
            smry->maxSpurious = smry->token[hash].count - 1;
        }
    }

}

//Similarity
void answer_FindSimilar(TxtSmry* smrys, int ID, double threshold, int n_mails, int* SimList, int* lenSim){
    double sim;
    *lenSim = 0;

    //Retrieve Base Summary 
    TxtSmry* SmryBase = &smrys[ID];
    assert(SmryBase->id == ID);

    // Increasing order
    for(int i=0;i<n_mails;i++){
        if(i==ID){continue;}

        sim = similarity_val(SmryBase, &smrys[i]);

        if(sim>threshold){
            SimList[*lenSim] = i;
            ++(*lenSim);
        }
    }

}

double similarity_val(TxtSmry* smry1, TxtSmry* smry2){
    double inter = 0;
    int hash;
    double sim;

    for(int i=0;i<smry1->nToken;i++){
        hash = get_unique_hashlist(smry1, i);
        if(smry2->token[hash].count>0){
            inter+=1;
        }
    }

        //Jaccob Similarity
        sim = inter / ((double)smry1->nToken + (double)smry2->nToken - inter);

        return sim;
}
