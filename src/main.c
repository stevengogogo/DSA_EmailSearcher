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


int main(){
    int num_mail;
    mail* mails;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);

    //Problem
    int mid = 9069;
    double thd = 0.15;
    //Answer
    int ans[] = {238, 384, 696, 783, 835, 1212, 1766, 2280, 2515, 3481, 4600, 5672, 6296, 7108, 7265, 7370, 7735, 8045, 8552, 8731, 8760, 8770, 9229}; 
    int lans = 23;


    init_FS();
    proc_FS(mails, num_mail);

    //Solve
    answer_FS(mails, mid, num_mail, thd,list, &nlist);




    //GC
    free(list);
    kill_FS();
}

/*
int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    int* list = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int nlist;
    int threshold;
    int mid;

    //Initiation

    //FS//
	api.init(&n_mails, &n_queries, &mails, &queries);   
    init_FS();

    //GA//

    //Preprocessing
    //Preprocess_FindSimilar(smrys, mails, n_mails);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
           
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process
            answer_FS(mails, mid, threshold, n_mails, list, &nlist);

            //answer
            api.answer(queries[i].id, list, nlist);
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

*/