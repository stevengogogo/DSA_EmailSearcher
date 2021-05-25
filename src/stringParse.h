#ifndef STRINGPARSE_H
#define STRINGPARSE_H

#include <ctype.h> // tolower
#include <stdbool.h>
#include "utils.h"



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



#endif