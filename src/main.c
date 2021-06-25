#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

int main(void) {
    int n_mails, n_queries;
    mail *mails;
    query *queries;
    TxtSmry* smrys;

    //Initiation
	api.init(&n_mails, &n_queries, &mails, &queries);   
    Init_FindSimilar(&smrys, n_mails);

    //Preprocessing
    Preprocess_FindSimilar(smrys, mails, n_mails);

    //Answer
	for(int i = 0; i < n_queries; i++)
		if(queries[i].type == expression_match)
		  api.answer(queries[i].id, NULL, 0);

    //Garbage Collection
    kill_FindSimilar(smrys, n_mails);
    free(mails);
    free(queries);
    
  return 0;
}
