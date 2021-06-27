#ifndef TEST_FS_SPURIOUS_HIT_H
#define TEST_FS_SPURIOUS_HIT_H
#include "utils.h"
#include "FindSimilar.h"
#include <string.h>
#include <stdlib.h>
/*
https://design215.com/toolbox/wordlist.php
https://convert.town/column-to-comma-separated-list
*/

void test_check_spurious(void){
    char* hashmap[Q_RABIN];
    for(int i=0;i<Q_RABIN;i++){
        hashmap[i] = (char*)malloc(1000*sizeof(char));
    }

    char token6286[10000] = "a,and,antbird,antbirds,are,backed,bird,bolivia,brazil,colombia,ecuador,family,forests,found,french,guiana,guyana,habitats,http,hylophylax,i,in,is,it,its,lowland,moist,naevia,naevius,natural,of,on,or,org,paragraph,peru,read,species,spot,subtropical,suriname,swamps,thamnophilidae,the,tropical,venezuela,wikipedia\0";
    double tk6286 = 226;

    char token676[10000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,appear,are,around,arrested,as,ashore,at,battling,be,beak,beak,because,been,being,black,book,buccaneers,buried,bursts,but,by,called,can,can,captain,captures,caribbean,cartoon,celebrate,century,chest,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,eight,end,endings,ends,england,eyes,film,find,finds,first,fish,for,found,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guys,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,i,if,in,interludes,is,island,it,just,later,lease,leg,lifted,location,long,loot,losing,lost,man,map,men,mickey,morgan,morgan,mouse,named,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,stormy,story,take,taking,tales,tattoo,tattooed,tavern,tell,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,treasure,trio,tropical,true,trying,two,unreleased,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";
    double tk676 = 47;

    char tokenUnion[100000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,antbird,antbirds,appear,are,around,arrested,as,ashore,at,backed,battling,be,beak,because,been,being,bird,black,bolivia,book,brazil,buccaneers,buried,bursts,but,by,called,can,captain,captures,caribbean,cartoon,celebrate,century,chest,colombia,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,ecuador,eight,end,endings,ends,england,eyes,family,film,find,finds,first,fish,for,forests,found,french,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guiana,guyana,guys,habitats,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,hylophylax,i,if,in,interludes,is,island,it,its,just,later,lease,leg,lifted,location,long,loot,losing,lost,lowland,man,map,men,mickey,moist,morgan,mouse,naevia,naevius,named,natural,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,or,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,peru,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,species,spot,stormy,story,subtropical,suriname,swamps,take,taking,tales,tattoo,tattooed,tavern,tell,thamnophilidae,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,trio,tropical,true,trying,two,unreleased,venezuela,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";
    double tkInter = 256;



    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    while(1){
        iNxt = popTokenHash(tokenUnion, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        if(strncmp(hashmap[hash], tokenB, strlen(tokenB)) != 0 && hashmap[hash][0]!='\0'){
            printf("Spurious Hit: %s / %s with ID=%d\n", hashmap[hash], tokenB, hash);
        };
        strncpy(hashmap[hash], tokenB, strlen(tokenB)+1);
    }


    //Free
    for(int i=0;i<Q_RABIN;i++){
        free(hashmap[i]);
    }
}


void test_check_spurious2(void){
    char* hashmap[Q_RABIN];
    for(int i=0;i<Q_RABIN;i++){
        hashmap[i] = (char*)malloc(1000*sizeof(char));
    }

    char token1099[10000] = "a,about,according,adjacent,african,age,all,alone,also,american,an,and,annual,any,are,area,as,asian,at,average,baseball,being,below,boys,bureau,capita,carolina,census,championships,children,columbia,com,counties,country,county,couples,cross,density,district,elementary,every,families,family,famous,female,females,festival,for,from,gilbert,girls,had,has,held,here,high,hispanic,household,householder,households,housing,http,husband,i,in,including,income,indian,individuals,is,it,its,km,land,latino,lexington,lexingtoncountypeachfestival,line,living,located,location,made,makeup,males,married,mascot,median,metropolitan,middle,mile,miles,more,native,no,non,of,older,on,or,org,other,out,over,paragraph,part,peach,people,per,place,populated,population,portions,poverty,present,primary,race,races,racial,read,residing,rugby,school,schools,size,someone,south,spread,square,state,states,statistical,th,the,them,there,this,those,to,together,total,town,track,two,under,united,units,up,versus,volleyball,was,water,were,which,white,who,wikipedia,with,www,years\0";
    double tk1099 = 160;

    char token6286[10000] = "a,and,antbird,antbirds,are,backed,bird,bolivia,brazil,colombia,ecuador,family,forests,found,french,guiana,guyana,habitats,http,hylophylax,i,in,is,it,its,lowland,moist,naevia,naevius,natural,of,on,or,org,paragraph,peru,read,species,spot,subtropical,suriname,swamps,thamnophilidae,the,tropical,venezuela,wikipedia\0";
    double tk6286 = 48;

    char tokenUnion[100000] = "a,about,according,adjacent,african,age,all,alone,also,american,an,and,annual,antbird,antbirds,any,are,area,as,asian,at,average,backed,baseball,being,below,bird,bolivia,boys,brazil,bureau,capita,carolina,census,championships,children,colombia,columbia,com,counties,country,county,couples,cross,density,district,ecuador,elementary,every,families,family,famous,female,females,festival,for,forests,found,french,from,gilbert,girls,guiana,guyana,habitats,had,has,held,here,high,hispanic,household,householder,households,housing,http,husband,hylophylax,i,in,including,income,indian,individuals,is,it,its,km,land,latino,lexington,lexingtoncountypeachfestival,line,living,located,location,lowland,made,makeup,males,married,mascot,median,metropolitan,middle,mile,miles,moist,more,naevia,naevius,native,natural,no,non,of,older,on,or,org,other,out,over,paragraph,part,peach,people,per,peru,place,populated,population,portions,poverty,present,primary,race,races,racial,read,residing,rugby,school,schools,size,someone,south,species,spot,spread,square,state,states,statistical,subtropical,suriname,swamps,th,thamnophilidae,the,them,there,this,those,to,together,total,town,track,tropical,two,under,united,units,up,venezuela,versus,volleyball,was,water,were,which,white,who,wikipedia,with,www,years\0";
    double tkUnion = 189;

    

    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    printf("\nSimilarity: %f (Threshold in PB %d: %f) Between Email: %d vs %d\n", (tk1099+tk6286 - tkUnion)/ tkUnion,91,0.070000, 6286, 1099);
    while(1){
        iNxt = popTokenHash(tokenUnion, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        if(strncmp(hashmap[hash], tokenB, strlen(tokenB)) != 0 && hashmap[hash][0]!='\0'){
            printf("Spurious Hit: %s / %s with ID=%d\n", hashmap[hash], tokenB, hash);
        };
        strncpy(hashmap[hash], tokenB, strlen(tokenB)+1);
    }


    //Free
    for(int i=0;i<Q_RABIN;i++){
        free(hashmap[i]);
    }
}


#endif 