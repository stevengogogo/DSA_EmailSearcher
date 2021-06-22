#ifndef UTILITY_H
#define UTILITY_H

#include "api.h"
#include <string.h>
#include "acutest.h"

/**
 * @brief Get the mails object
 * 
 * @param filename use `teat/data/test.in`
 * @param mails email pointer.
 * @param num_mail number of emails.
 */
static void get_mails(char* filename, mail** mails, int* num_mail){
    FILE* fp;
    size_t len;
    ssize_t read;
    //Mail info
    int id;
    int maxnum = 1000000;
    char* line = (char *) malloc(maxnum);
    char* from= (char *) malloc(maxnum);
    char* subject= (char *) malloc(maxnum);
    char* idstr= (char *) malloc(maxnum);
    char* content= (char *) malloc(maxnum);
    char* to= (char *) malloc(maxnum);
    size_t buffer=32;
    size_t chr;
    

    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("File not found");

    chr = getline(&idstr,&buffer,fp);
    sscanf(idstr, "%d", num_mail);
    *mails = (mail*)malloc(*num_mail*sizeof(mail));
    
    for(int i=0;i<*num_mail;i++){
       
        chr = getline(&line,&buffer,fp);
        chr = getline(&idstr,&buffer,fp);
        chr = getline(&from,&buffer,fp);
        chr = getline(&content,&buffer,fp);
        chr = getline(&subject,&buffer,fp);
        chr = getline(&to,&buffer,fp);

        sscanf(idstr, "%d", &id);
        //Check content
        //Copy mail information
        (*mails)[i].id = id;
        strcpy((*mails)[i].subject, subject);
        strcpy((*mails)[i].content, content);
        strcpy((*mails)[i].from, from);
        strcpy((*mails)[i].to, to);

        TEST_CHECK(i==id);
    }

    free(line);
    free(idstr);
    free(content);
    free(subject);
    free(from);
    free(to);
}

/** Print time*/
void print_clock(char* s,clock_t str, clock_t end){
    double total_t = (double)(end - str) / CLOCKS_PER_SEC;
    printf("%s Elapsed %f", s,total_t);
}

#endif