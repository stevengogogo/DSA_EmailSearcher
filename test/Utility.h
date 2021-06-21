#ifndef UTILITY_H
#define UTILITY_H

#include "api.h"
#include <string.h>
#include "acutest.h"


static void get_mails(char* filename, mail** mails, int* num_mail){
    FILE* fp;
    size_t len;
    ssize_t read;
    //Mail info
    int id;
    int maxnum = 1000000;
    char line[maxnum];
    char subject[maxnum];
    char idstr[maxnum];
    char content[maxnum];
    char from[maxnum];
    char to[maxnum];
    size_t buffer=32;
    size_t chr;
    

    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("File not found");

    fscanf(fp, "%d", num_mail);
    *mails = (mail*)malloc(*num_mail*sizeof(mail));
    
    for(int i=0;i<*num_mail;i++){
        //Read file
        /*
        fscanf(fp, "%[^\n]\n", line);
        fscanf(fp, "%d", &id);
        fscanf(fp, "%s[^\n]\n", subject);
        fscanf(fp, "%s[^\n]\n", content);
        fscanf(fp, "%s[^\n]\n", from);
        fscanf(fp, "%s[^\n]\n", to);
        */

        /*
        fgets(line,maxnum,fp);
        fgets(idstr, maxnum, fp);
        fgets(subject,maxnum,fp);
        fgets(content,maxnum,fp);
        fgets(from,maxnum,fp);
        fgets(to,maxnum,fp);
        */

        chr = getline(&line,&buffer,fp);
        chr = getline(&idstr,&buffer,fp);
        chr = getline(&subject,&buffer,fp);
        chr = getline(&content,&buffer,fp);
        chr = getline(&from,&buffer,fp);
        chr = getline(&to,&buffer,fp);

        sscanf(idstr, "%d", &id);
        //Check content
        //Copy mail information
        (*mails)->id = id;
        strcpy((*mails)[i].subject, subject);
        strcpy((*mails)[i].content, content);
        strcpy((*mails)[i].from, from);
        strcpy((*mails)[i].to, to);
    }
}



#endif