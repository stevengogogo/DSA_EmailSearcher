#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>


/*
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
*/


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
