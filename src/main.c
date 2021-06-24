#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>


// The testdata only contains the first 100 mails (mail1 ~ mail100)
// and 2000 queries for you to debug.

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
    }

    fclose(fp);
    free(line);
    free(idstr);
    free(content);
    free(subject);
    free(from);
    free(to);
}

static int power_int(int x, int n){
    int p = 1;
    for(int i=0;i<n;i++){
        p *= x;
    }
    return p;
};

static int HashString(char s[], int D, int Q){
    int len = strlen(s);
    int hash = 0;
    
    for(int i=0;i<len;i++){
        hash += c*power_int(D, len-i-1);
    }
    return hash% Q;
};


int main(void) {
int h = HashString("87\0", D_RABIN, Q_RABIN);

  return 0;
}
