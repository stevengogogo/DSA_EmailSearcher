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
#define MAX_TOKEN_LEN 1000

static long PowArr[MAX_TOKEN_LEN];


/*Rabin Karp Hashing*/
void powerArray(long* arr, int len, long base, long mod);
void _updateHash(long hash, char c);



#endif