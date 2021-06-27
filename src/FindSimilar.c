#include "FindSimilar.h"


void init_lkmem(lkmem* lkm, int size){
    lkm->node = (ndl*)malloc(size*sizeof(ndl));
    lkm->used = 0;
    lkm->max = size;
}
void kill_lkmem(lkmem* lkm){
    free(lkm->node);
    lkm->max = 0;
};


ndl* get_ndl_mem(lkmem*lkm){
    if(lkm->used == lkm->max){
        lkm->node = (ndl*)realloc(lkm->node, (lkm->max*2)*sizeof(ndl));
        lkm->max = lkm->max*2;
    }
    ndl* hold = &lkm->node[lkm->used];
    hold->nxt = NULL;
    ++lkm->used;
    return hold;
}

void append_lk(lklist* list, short val, lkmem* lkm){
    ndl* new = get_ndl_mem(lkm);
    new->id = val;
    if(list->str==NULL){
        list->str = new;
        list->end = new;
    }
    else{
        list->end->nxt = new;
        list->end = new;
    }
}



void init_Matrix_ushort(Matrix_ushort* M, int nrow){
   M->map = (lklist*)calloc(nrow,sizeof(lklist));
   M->nrow = nrow;
}

void kill_Matrix_ushort(Matrix_ushort* M){
    free(M->map);
    M->nrow = 0;
}



void init_FS(infoFs* info){
    init_Matrix_ushort(&info->hstack, Q_RABIN);
    init_lkmem(&info->lkm, INIT_UNIQUE_TOKEN_NUM);
    info->num_unique = (double*)calloc(MAX_N_MAIL,sizeof(double));
    info->SimList = (double*)calloc(MAX_N_MAIL, sizeof(double));
    info->isVis = (bool*)calloc(Q_RABIN, sizeof(bool));
};

void kill_FS(infoFs* info){
    free(info->num_unique);
    free(info->SimList);
    free(info->isVis);
    kill_Matrix_ushort(&info->hstack);
    kill_lkmem(&info->lkm);
};

void register_hash(infoFs* info, int ID, int hash){
    lklist* row = &info->hstack.map[hash];
    if(row->end != NULL){//check duplicate
        int end = row->end->id;
        if(end == ID){//already appended
            return;
        }
    }

    //Add hash
    append_lk(&info->hstack.map[hash], ID, &info->lkm);

    //Register unique count
    info->num_unique[ID] += 1;
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


void append_mHash(infoFs* info, mail* mails, int ID){
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
        register_hash(info, ID, hash);
    }

    //Subject
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        register_hash(info,ID, hash);
    }
}

void proc_FS(infoFs* info, mail* mails, int n_mail){
    int ID;
    for(int i=0;i<n_mail;i++){
        ID = mails[i].id;
        append_mHash(info,mails, ID);
    }
}






int Hash_RK(char s[]){
	int i = 0;
	int RK = 0;
	while(s[i]!='\0'){
		RK = (D_RABIN*RK + (int)s[i])%Q_RABIN;
		i++;
	}
	return abs(RK)%Q_RABIN;
}




void answer_FS(infoFs*info, mail* mails, int ID, int n_mail, double threshold, int* list, int* nlist){
    bool* isVis = info->isVis;
    memset(isVis, 0, Q_RABIN*sizeof(bool));
    double Overlap[MAX_N_MAIL]={0};
    char* text = mails[ID].content;//Remember to add subject
    int iNxt;
    int iStr=0;
    int hash;
    double sim;
    char token[TOKEN_STRING_LENGTH];
    ushort id = (ushort)ID;
    ushort interID;
    *nlist = 0;

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
        ndl* inode = info->hstack.map[hash].str;
        while(inode != NULL){
            interID = inode->id;
            ++Overlap[(int)interID];
            inode = inode->nxt;
        }
        isVis[hash] = true;
    }

    char* subject = mails[ID].subject; 
    iStr = 0;
    while(1){
        iNxt = popTokenHash(subject, token, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;

        if(isVis[hash]){
            continue;
        }
        
       //Find similar
        ndl* inode = info->hstack.map[hash].str;
        while(inode != NULL){
            interID = inode->id;
            ++Overlap[(int)interID];
            inode = inode->nxt;
        }
        isVis[hash] = true;
    }
    
    // Similarity
    for(int i=0;i<n_mail;i++){
        sim = Overlap[i] / (info->num_unique[i] + info->num_unique[ID]  - Overlap[i]);
        if(sim>threshold && i!=ID){
            list[*nlist]=i;
            ++(*nlist);
        }
    }

}
