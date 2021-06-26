#ifndef GROUPANALYSIS_H
#define GROUPANALYSIS_H
#include "api.h"
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000001

typedef struct Node{
	char* name;
	int parentIdx;
	int size;
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

static void inputTable(node** set, char word[]){
	int hashed = findIdx(set, word);
	if(!set[hashed]){
		set[hashed] = (node*)malloc(sizeof(node));
		set[hashed]->name = word;
		set[hashed]->parentIdx = hashed;
		set[hashed]->size = 1;
	}
}

static int findset(node **set, int hashed){
	if(set[hashed]->parentIdx!=hashed){
		set[hashed]->parentIdx = findset(set,set[hashed]->parentIdx);
	}
	return set[hashed]->parentIdx;
}

static void link_GA(node **set, int nodex, int nodey ,int *count, int *max){

	if(set[nodex]->size>set[nodey]->size){
		set[nodey]->parentIdx = nodex;
		set[nodex]->size += set[nodey]->size;
		if(set[nodey]->size>=2){
			*count-=1;
		}
		set[nodey]->size = 0;
		if(set[nodex]->size>*max){
			*max = set[nodex]->size;
		}
	}else{
		set[nodex]->parentIdx = nodey;
		if(set[nodex]->size==set[nodey]->size&&set[nodex]->size==1){
			*count += 1;
		}
		set[nodey]->size+=set[nodex]->size;
		if(set[nodex]->size>=2){
			*count-= 1;
		}
		set[nodex]->size = 0;
		if(set[nodey]->size>*max){
			*max = set[nodey]->size;
		}
	}
}

static void setunion(node**set, char word1[],char word2[], int* count, int* max){
	inputTable(set, word1);
	inputTable(set, word2);
	int nodex = findIdx(set, word1);
	int nodey = findIdx(set, word2);
	int idxx = findset(set, nodex);
	int idxy = findset(set, nodey);
	if(idxx!=idxy){
		link_GA(set, idxx, idxy, count, max);
	}
}

static void answer_GroupAnalysis(int mid[], int len, mail* mails, int* list, int* nlist){
	node** arr = makeset();
	int count = 0;
	int max = 0;

	for(int i = 0; i < len; i++){
		setunion(arr,mails[mid[i]].from, mails[mid[i]].to, &count, &max);
	}

    //ANS
    list[0] = count;
    list[1] = max;
    *nlist = 2;
}


#endif