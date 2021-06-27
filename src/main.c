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
    int* list = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int nlist;
    int threshold;
    int mid;

    //Initiation

    //FS//
	api.init(&n_mails, &n_queries, &mails, &queries);   
    //Init_FindSimilar(&smrys, n_mails);

    //GA//

    //Preprocessing
    //Preprocess_FindSimilar(smrys, mails, n_mails);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
            /*
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process
            answer_FindSimilar(smrys, mid, threshold, n_mails, list, &nlist);

            //answer
            if(nlist>0){
                api.answer(queries[i].id, list, nlist);
            }
            else{api.answer(queries[i].id,NULL,0);}
            */
        }
        
        //Expression Match
        else if(queries[i].type == expression_match){
			answer_ExpressionMatch(queries[i].data.expression_match_data.expression,mails,list,&nlist);
		    api.answer(queries[i].id, list, nlist);
        }

        //Group Analysis
        else {

            answer_GroupAnalysis(queries[i].data.group_analyse_data.mids, queries[i].data.group_analyse_data.len,mails, list, &nlist);

            /*
            printf("data ID:%d (len): %d\n", queries[i].id,queries[i].data.group_analyse_data.len);
            for(int a=0;a<queries[i].data.group_analyse_data.len;a++){
                printf("%d,", queries[i].data.group_analyse_data.mids[a]);
            }
            printf("\nEST\n");
            for(int i=0;i<nlist;i++){
                printf("%d, ", list[i]);
            }
            printf("\n");
            */


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
