#include "FindSimilar.h"

void init_Matrix_ushort(Matrix_ushort* M, int nrow, int ncol){
    ushort **array = malloc(nrow * sizeof *array + (nrow * (ncol * sizeof **array)));
    size_t i;
    ushort * const data = array + nrow;
    for(i = 0; i < nrow; i++){
        array[i] = data + i * ncol;
    }

    M->m = array;
    M->ncol = ncol;
    M->nrow = nrow;
    M->len = (ushort*)calloc(nrow, sizeof(ushort));
}

void kill_Matrix_ushort(Matrix_ushort* M){
    for(int i=0;i<M->nrow;i++){
        free(M->m[i]);
    }
    free(M->len);
}






void init_FS(void){
    init_Matrix_ushort(&hstack, Q_RABIN, MAX_N_MAIL);
    num_unique = (double*)calloc(MAX_N_MAIL,sizeof(double));
    SimList = (double*)calloc(MAX_N_MAIL, sizeof(double));
    memset(num_unique, 0, sizeof(num_unique));
};

void kill_FS(void){
    free(num_unique);
    free(SimList);
    kill_Matrix_ushort(&hstack);
};

void register_hash(int ID, int hash){
    if(hstack.len[hash] != 0){//check duplicate
        int end = hstack.m[hash][hstack.len[hash]-1];
        if(end == ID){//already appended
            return;
        }
    }

    //Add hash
    hstack.m[hash][hstack.len[hash]] = ID;
    ++hstack.len[hash];

    //Register unique count
    num_unique[ID] += 1;
};

/** Return location*/
int popTokenHash(char message[], char token[], int iStr, int* Hash){
    char c;
    int asc; //ascii number
    *Hash = 0; //reset hash value
    //No string left
    if (iStr < 0){
        token[0] = '\0';
        return -1;
    }

    int i = 0; //token[i]
    while(message[iStr] != '\0' ){
        c = message[iStr];
        asc = (int)c; //ascii number

        if (isRegularExpr_ASCII(asc)){
            if (isUpperCase_ASCII(c))
                c = tolower(c);
            token[i] = c;
            ++i;
            ++iStr;
        }
        else{
            if (i==0){
                ++iStr;
                continue;
            }
            else 
                break;
        }

    }

    if (message[iStr] == '\0'){ // EOF
        iStr= -1;
    }

    token[i] = '\0'; //end of token
    *Hash = Hash_RK(token);

    return iStr;
}


void append_mHash(mail* mails, int ID){
    char* text = mails[ID].content;
    char* subject = mails[ID].subject;
    int hash;
    int iNxt;
    int iStr = 0;
    char token[TOKEN_STRING_LENGTH];

    // Content
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(ID, hash);
    }

    //Subject
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(ID, hash);
    }
}

void proc_FS(mail* mails, int n_mail){
    int ID;
    for(int i=0;i<n_mail;i++){
        ID = mails[i].id;
        append_mHash(mails, ID);
    }
}






void similarity(mail* mails, int ID,int n_mail){
    bool isVis[Q_RABIN];
    double Overlap[MAX_N_MAIL];
    char* text = mails[ID].content;//Remember to add subject
    int iNxt;
    int iStr=0;
    int hash;
    double sim;
    char token[TOKEN_STRING_LENGTH];
    ushort id = (ushort)ID;
    ushort interID;

    // Content
    while(1){
        iNxt = popTokenHash(text, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;

        if(isVis[hash]){
            continue;
        }
        
        //Find similar
        for(int i=0;i<hstack.len[hash];i++){
            interID = hstack.m[hash][i];
            if(id==interID){
                continue;
            }
            ++Overlap[(int)interID];
        }
        isVis[hash] = true;
    }
    
    // Similarity
    for(int i=0;i<n_mail;i++){
        sim = Overlap[i] / (num_unique[i] + num_unique[ID] - Overlap[i]);
        SimList[i] = sim;
    }
}


int Hash_RK(char s[]){
	int i = 0;
	int RK = 0;
	while(s[i]!='\0'){
		RK = (62*RK + (int)s[i])%Q_RABIN;
		i++;
	}
	return abs(RK)%Q_RABIN;
}




void answer_FS(mail* mails, int ID, int n_mail, int threshold, int* list, int* nlist){
    similarity(mails, ID, n_mail);
    *nlist = 0;

    //Find Sim > threshold
    for(int i=0;i<n_mail;i++){
        if(SimList[i] > threshold){
            list[*nlist] = i;
            ++(*nlist);
        }
    }
}
