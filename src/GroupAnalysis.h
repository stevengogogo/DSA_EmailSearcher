
#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H
#include <limits.h>
#include <string.h>
#define SIZE 1000001

static typedef struct Node{
	char* name;
	int parentIdx;
	int rank;
}node;

static node** makeset(){
	static node* arr[SIZE];
	return arr;
}

static int hash(char word[]){
	int i = 0;
	int RK = 0;
	while(word[i]!='\0'){
		RK = (62*RK + (int)word[i])%SIZE;
		i++;
	}
	return abs(RK)%INT_MAX;
}

static int findIdx(node**set, char word[]){
	int hashed = hash(word);
	while(set[hashed]){
		if(strcmp(set[hashed]->name, word)!=0){
			hashed = hashed+1;
		}else return hashed;
	}
	return hashed;
}

static void inputTable(node** set, char word[], int countArr[]){
	int hashed = findIdx(set, word);
	if(!set[hashed]){
		set[hashed] = (node*)malloc(sizeof(node));
		set[hashed]->name = word;
		set[hashed]->parentIdx = hashed;
		set[hashed]->rank = 0;
		countArr[hashed] = 1;
	}
}

static int findset(node **set, int hashed){
	if(set[hashed]->parentIdx!=hashed){
		set[hashed]->parentIdx = findset(set,set[hashed]->parentIdx);
	}
	return set[hashed]->parentIdx;
}

static void link(node **set, int nodex, int nodey){
	if(set[nodex]->rank>set[nodey]->rank){
		set[nodey]->parentIdx = nodex;
	}else{
		set[nodex]->parentIdx = nodey;
		set[nodey]->rank +=1;
	}
}

static void setunion(node**set, char word1[],char word2[], int countArr[], int* count, int* max){
	inputTable(set, word1, countArr);
	inputTable(set, word2, countArr);
	int nodex = findIdx(set, word1);
	int nodey = findIdx(set, word2);
	int idxx = findset(set, nodex);
	int idxy = findset(set, nodey);
	if(idxx!=idxy){
		link(set, idxx, idxy);
		if(countArr[idxx]>countArr[idxy]){
			if(countArr[idxy]>=2){
				*count-=1;
			}
			countArr[idxx]+=countArr[idxy];
			countArr[idxy] = 0;
			if(countArr[idxx]>*max){
				*max = countArr[idxx];
			}
		}else{
			if(countArr[idxx]>=2){
				*count-=1;
			}
			if(countArr[idxx]==countArr[idxy]&&countArr[idxy]==1){
				*count+=1;
			}
			countArr[idxy]+=countArr[idxx];
			countArr[idxx] = 0;
			if(countArr[idxy]>*max){
				*max = countArr[idxy];
			}
		}
	}
}
//comment

static void ans(int mid[], int len, mail* mails){
	node** arr = makeset();
	int count = 0;
	int max = 0;
	int countArr[SIZE];

	for(int i = 0; i < len; i++){
		setunion(arr,mails[mid[i]].from,mailes[mid[i]].to,countArr, &count, &max);
	}
	printf("%d %d",max,count);
	int ans[] = {count,max};
	api.answer(anx);
}

#endif