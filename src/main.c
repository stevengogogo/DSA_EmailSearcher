#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>


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

/** Print time*/
void print_clock(char* s,clock_t str, clock_t end){
    double total_t = (double)(end - str) / CLOCKS_PER_SEC;
    printf("%s Time %f", s,total_t);
}


int main(void) {
    int num_mail;
    mail* mails;
    TxtSmry* smrys;
    

    get_mails("test/data/test.in", &mails, &num_mail);

    Init_FindSimilar(&smrys, num_mail);

    Preprocess_FindSimilar(smrys, mails, 30);

    kill_FindSimilar(smrys, num_mail);
    free(mails);

  return 0;
}


/*
int main(void) {
    int n_mails, n_queries;
    mail *mails;
    query *queries;
    TxtSmry* smrys;

	api.init(&n_mails, &n_queries, &mails, &queries);

    Init_FindSimilar(&smrys, n_mails);
    Preprocess_FindSimilar(smrys, mails, n_mails);

	//for(int i = 0; i < n_queries; i++)
		//if(queries[i].type == expression_match)
		  //api.answer(queries[i].id, NULL, 0);

    kill_FindSimilar(smrys, n_mails);
    free(mails);
  return 0;
}
*/