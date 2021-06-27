#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

/*
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
    
    //Get mails
    int num_mail;
    mail* mails;
    int* list = (int*)malloc(sizeof(int)*MAX_N_MAIL);
    int nlist;
    get_mails("test/data/test.in", &mails, &num_mail);
  
    //data
    int mid30 = 4189;
    int mid5=9451;
    double thd30 = 0.180000;
    double thd5 = 0.170000;
    int ans30[] = {790, 1843, 1952, 8550 }; 
    int ans5[] = {1597, 4026, 4122, 5123, 7033, 7176, 7802, 7845};
    
    int len30 = sizeof(ans30)/sizeof(ans30[0]);
    int len5 = sizeof(ans5)/sizeof(ans5[0]);



    infoFs infs;

    init_FS(&infs);
    proc_FS(&infs, mails, num_mail);

    answer_FS(&infs, mails, mid5, num_mail, thd5, list, &nlist);

    answer_FS(&infs, mails, mid30, num_mail, thd30, list, &nlist);




    //GC
    free(list);
    kill_FS(&infs);
}
*/




int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    int* list = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int nlist;
    double threshold;
    int mid;
    infoFs infs;

    //Initiation

    //FS//
	api.init(&n_mails, &n_queries, &mails, &queries);   
    init_FS(&infs);

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
            answer_FS(&infs, mails, mid,n_mails, threshold, list, &nlist);

            /*
            printf("QID: %d\n", queries[i].id);
            printf("MID: %d\n",queries[i].data.find_similar_data.mid);
            printf("Threshold: %f\n", queries[i].data.find_similar_data.threshold);
            */

            //answer
            if(queries[i].data.find_similar_data.threshold<0.19){
                continue;
            }
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
