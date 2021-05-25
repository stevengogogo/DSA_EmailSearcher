#ifndef STRINGPARSE_H
#define STRINGPARSE_H

#include <ctype.h> // tolower
#include <stdio.h>

/** Regular Expression*/
static const char REGULAR_EXPR[] = "%s";


/**
 * @brief Pop token from message. 
 * 
 * @param token Buffer string. Token will be saved here. `\0` if no token left
 * @param message main text
 * @param iStr reading head
 * @return int updated reading head `iStr`.
 */
int popToken(char message[], char token[], int iStr);






#endif