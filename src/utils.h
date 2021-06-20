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
#include <ctype.h> // tolower
#define INIT_NUM_ARRAY_ELEMENT 10 
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

/************Generic Dynamic Array************/

/** Generic copy*/
void copy_item_array(void* srcArr, int locSrc,void* dstArr, int locDst,size_t size);

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

/************Generic Stack************/

/** Equivalent to one byte*/

/**
 * @brief Universal Stack
 * @param top index of top element
 * @param len number of element stored
 * @param memory pointer to the allocated memory
 * @param eleSize size of single element. e.g. `sizeof(int)`
 * @param num_maxEle maximum number can be stored in the stack. Augemented when reaching the capacity.
*/
typedef struct uStack {
    int top;
    int len;
    byte *memory; //allocated memory
    int eleSize; // size of element
    int num_maxEle; // Number of max elements
} uStack;

/** Initiate a generic stack
 * @param uStack uninitiate struct
 * @param eleSize size of each element
 * @example init(s, sizeof(int)); //For integer storage
*/
void init_uStack(uStack *s, size_t elemSize);

bool isEmpty_uStack(uStack* s);
int size_uStack(uStack* s);
void push_uStack(uStack* s, void *item);
void* pop_uStack(uStack* s);
void* top_uStack(uStack* s);
void* len_uStack(uStack* s);
void* kill_uStack(uStack* s);




#endif