/**
 * @file utils.h
 * @author Shao-Ting Chiu (r07945001@ntu.edu.tw)
 * @brief General Utilities for C language
 * @version 0.1
 * @date 2021-03-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef UTILS_H
#define UTILS_H

#include <stdbool.h>
#include <ctype.h> // tolower

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

/************Generic Stack************/

/** Equivalent to one byte*/
typedef unsigned  char byte;

/**
 * @brief Universal Stack
*/
typedef struct Stack {
    int top;
    byte *memory; //allocated memory
    int EleSize; // size of element
    int num_maxEle; //
} Stack;


#endif