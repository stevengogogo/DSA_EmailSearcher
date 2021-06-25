#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    TxtSmry* smrys;
    int* list_FS = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int len_FS;
    int threshold;
    int mid;

    //Initiation
	api.init(&n_mails, &n_queries, &mails, &queries);   
    Init_FindSimilar(&smrys, n_mails);

    //Preprocessing
    Preprocess_FindSimilar(smrys, mails, n_mails);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process
            answer_FindSimilar(smrys, mid, threshold, n_mails, list_FS, &len_FS);

            //answer
            if(len_FS>0){
                api.answer(queries[i].id, list_FS, len_FS);
            }
            else{api.answer(queries[i].id,NULL,0);}
        }
        
        //Expression Match
        else if(queries[i].type == expression_match){
		  api.answer(queries[i].id, NULL, 0);
        }

        //Group Analysis
        else {
            api.answer(queries[i].id, NULL, 0);
        }
    }

    //Garbage Collection
    kill_FindSimilar(smrys, n_mails);
    free(mails);
    free(queries);
    free(list_FS);

    return 0;
}
