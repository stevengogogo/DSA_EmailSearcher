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

static void PrintAllToken(char message[]){
    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    printf("\n");
    while(1){
        iNxt = popTokenHash(message, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        printf("%s ", tokenB);
    }
}

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
    char text1099[100000] = "Gilbert is a town in Lexington County, South Carolina, United States. The population was 500 at the 2000 census. It is part of the Columbia, South Carolina Metropolitan Statistical Area. Gilbert is located at 335532N 812340W / 33.92556N 81.39444W / 33.92556; -81.39444 (33.925492, -81.394531)[3]. According to the United States Census Bureau, the town has a total area of 2.3 square miles (6.0km2), of which, 2.3 square miles (6.0km2) of it is land and 0.1 square miles (0.26km2) of it (2.58%) is water. Its high school mascot is the Indian. Gilbert High School has 3 state championships in baseball (1988, 2006, 2008), 3 in rugby (2007, 2009, 2010), 1 in boys cross country (2004), 2 in girls volleyball (1996, 1997), and 1 in girls track (1986)[1]. The town is famous for being the location of the annual Lexington County Peach Festival (http://www.lexingtoncountypeachfestival.com). In 2008, the 50th festival was held. Gilbert has 4 schools: Gilbert Primary School, Gilbert Elementary School, Gilbert Middle School, and Gilbert High School. All schools here are a part of Lexington School District 1. As of the census[1] of 2000, there were 500 people, 181 households, and 148 families residing in the town. The population density was 220.7 people per square mile (85.0/km). There were 195 housing units at an average density of 86.1 per square mile (33.2/km). The racial makeup of the town was 94.60% White, 3.60% African American, 0.20% Native American, 0.20% Asian, 0.20% from other races, and 1.20% from two or more races. Hispanic or Latino of any race were 1.60% of the population. There were 181 households out of which 53.0% had children under the age of 18 living with them, 56.4% were married couples living together, 16.6% had a female householder with no husband present, and 18.2% were non-families. 16.0% of all households were made up of individuals and 6.6% had someone living alone who was 65 years of age or older. The average household size was 2.76 and the average family size was 3.05. In the town the population was spread out with 33.2% under the age of 18, 7.0% from 18 to 24, 32.4% from 25 to 44, 19.6% from 45 to 64, and 7.8% who were 65 years of age or older. The median age was 32 years. For every 100 females there were 93.8 males. For every 100 females age 18 and over, there were 96.5 males. The median income for a household in the town was $46,563, and the median income for a family was $52,500. Males had a median income of $35,707 versus $25,000 for females. The per capita income for the town was $19,909. About 8.9% of families and 8.6% of the population were below the poverty line, including 11.3% of those under age 18 and 15.6% of those age 65 or over. This populated place also has portions in an adjacent county or counties I read the paragraph on http://wikipedia.org Gilbert, South Carolina\0";

    char text1648[100000] = "The depiction of disability in the media plays a major role in forming public perception of disability. Perceptions created by the media informs the way people with disabilities are treated in society. \"The media have been cited as a key site for the reinforcement of negative images and ideas in regard to people with disabilities.\"[1] In response, there have been increasing examples worldwide of people with disabilities pursuing their own media projects, such as film series centered on disability issues, radio programs and podcasts designed around and marketed towards those with disabilities, and so on. This is seen by many disability rights activists as a way to, as some in these circles term it, \"piss on pity\". The media generally depict people with disabilities according to common stereotypes such as pity and heroism.[2] Disability advocates often call this type of societal situation the \"pity/heroism trap\" or \"pity/heroism dichotomy\"[2] and call instead for its supporters to \"Piss On Pity\" and push forward with inclusion instead.[3] When reports are about the \"plight of the disabled\" they rely on the pity or medical model of disability. Telethons are an example of this, such as the Jerry Lewis MDA Telethon which has been heavily criticised and sometimes even physically protested by disability rights advocates.[4] Negative day-to-day reporting may occur chiefly by depicting a given person or people with a disability as a burden or drain on society.[5] The \"super-crip\" model, in which subjects are portrayed as heroically overcoming their afflictions, is also often used when reporting on sport.[1] The social model tends to be used for reporting on the activities of disability rights activists if the report is positive.[6] Ouch![1] by the British Broadcasting Corporation, The Largest Minority[2] broadcast in New York City, and a show presented in sign language on SABC television in South Africa, Dtv[3], are examples of programming produced for, and usually also by, disabled people. Radio reading services are radio stations that broadcast readings from newspapers, magazines and books to mainly blind or partially sighted audiences. Many activist and charitable organisations have websites and publish their own magazines or newsletters. Various organisations and programmes have been established to try to positively influence the frequency and quality of reporting on disability issues.[7][8][9][10] I read the paragraph on http://wikipedia.org Disability in the media\0";

    char token1099[100000] = "0, 000, 05, 0km2, 1, 100, 11, 148, 15, 16, 18, 181, 19, 195, 1986, 1988, 1996, 1997, 2, 20, 2000, 2004, 2006, 2007, 2008, 2009, 2010, 220, 24, 25, 26km2, 3, 32, 33, 335532n, 35, 39444, 39444w, 394531, 4, 44, 45, 46, 5, 500, 50th, 52, 53, 56, 563, 58, 6, 60, 64, 65, 7, 707, 76, 8, 81, 812340w, 85, 86, 9, 909, 925492, 92556, 92556n, 93, 94, 96, a, about, according, adjacent, african, age, all, alone, also, american, an, and, annual, any, are, area, as, asian, at, average, baseball, being, below, boys, bureau, capita, carolina, census, championships, children, columbia, com, counties, country, county, couples, cross, density, district, elementary, every, families, family, famous, female, females, festival, for, from, gilbert, girls, had, has, held, here, high, hispanic, household, householder, households, housing, http, husband, i, in, including, income, indian, individuals, is, it, its, km, land, latino, lexington, lexingtoncountypeachfestival, line, living, located, location, made, makeup, males, married, mascot, median, metropolitan, middle, mile, miles, more, native, no, non, of, older, on, or, org, other, out, over, paragraph, part, peach, people, per, place, populated, population, portions, poverty, present, primary, race, races, racial, read, residing, rugby, school, schools, size, someone, south, spread, square, state, states, statistical, the, them, there, this, those, to, together, total, town, track, two, under, united, units, up, versus, volleyball, was, water, were, which, white, who, wikipedia, with, www, years\0";
    double tk1099 = 229;

    char token1648[100000] = "1, 10, 2, 3, 4, 5, 6, 7, 8, 9, a, about, according, activist, activists, activities, advocates, afflictions, africa, also, an, and, are, around, as, audiences, be, been, blind, books, british, broadcast, broadcasting, burden, by, call, centered, charitable, chiefly, circles, cited, city, common, corporation, created, crip, criticised, day, depict, depicting, depiction, designed, dichotomy, disabilities, disability, disabled, drain, dtv, established, even, example, examples, film, for, forming, forward, frequency, from, generally, given, has, have, heavily, heroically, heroism, http, i, ideas, if, images, in, inclusion, increasing, influence, informs, instead, is, issues, it, its, jerry, key, language, largest, lewis, magazines, mainly, major, many, marketed, may, mda, media, medical, minority, model, negative, new, newsletters, newspapers, occur, of, often, on, or, org, organisations, ouch, overcoming, own, paragraph, partially, people, perception, perceptions, person, physically, piss, pity, plays, plight, podcasts, portrayed, positive, positively, presented, produced, programmes, programming, programs, projects, protested, public, publish, pursuing, push, quality, radio, read, reading, readings, regard, reinforcement, rely, report, reporting, reports, response, rights, role, sabc, seen, series, services, show, sighted, sign, site, situation, so, social, societal, society, some, sometimes, south, sport, stations, stereotypes, subjects, such, super, supporters, telethon, telethons, television, tends, term, that, the, their, there, these, they, this, those, to, towards, trap, treated, try, type, used, usually, various, way, websites, when, which, wikipedia, with, worldwide, york\0";
    double tk1648 = 213;

    char tokenUnion[1000000] = "0, 000, 05, 0km2, 1, 10, 100, 11, 148, 15, 16, 18, 181, 19, 195, 1986, 1988, 1996, 1997, 2, 20, 2000, 2004, 2006, 2007, 2008, 2009, 2010, 220, 24, 25, 26km2, 3, 32, 33, 335532n, 35, 39444, 39444w, 394531, 4, 44, 45, 46, 5, 500, 50th, 52, 53, 56, 563, 58, 6, 60, 64, 65, 7, 707, 76, 8, 81, 812340w, 85, 86, 9, 909, 925492, 92556, 92556n, 93, 94, 96, a, about, according, activist, activists, activities, adjacent, advocates, afflictions, africa, african, age, all, alone, also, american, an, and, annual, any, are, area, around, as, asian, at, audiences, average, baseball, be, been, being, below, blind, books, boys, british, broadcast, broadcasting, burden, bureau, by, call, capita, carolina, census, centered, championships, charitable, chiefly, children, circles, cited, city, columbia, com, common, corporation, counties, country, county, couples, created, crip, criticised, cross, day, density, depict, depicting, depiction, designed, dichotomy, disabilities, disability, disabled, district, drain, dtv, elementary, established, even, every, example, examples, families, family, famous, female, females, festival, film, for, forming, forward, frequency, from, generally, gilbert, girls, given, had, has, have, heavily, held, here, heroically, heroism, high, hispanic, household, householder, households, housing, http, husband, i, ideas, if, images, in, including, inclusion, income, increasing, indian, individuals, influence, informs, instead, is, issues, it, its, jerry, key, km, land, language, largest, latino, lewis, lexington, lexingtoncountypeachfestival, line, living, located, location, made, magazines, mainly, major, makeup, males, many, marketed, married, mascot, may, mda, media, median, medical, metropolitan, middle, mile, miles, minority, model, more, native, negative, new, newsletters, newspapers, no, non, occur, of, often, older, on, or, org, organisations, other, ouch, out, over, overcoming, own, paragraph, part, partially, peach, people, per, perception, perceptions, person, physically, piss, pity, place, plays, plight, podcasts, populated, population, portions, portrayed, positive, positively, poverty, present, presented, primary, produced, programmes, programming, programs, projects, protested, public, publish, pursuing, push, quality, race, races, racial, radio, read, reading, readings, regard, reinforcement, rely, report, reporting, reports, residing, response, rights, role, rugby, sabc, school, schools, seen, series, services, show, sighted, sign, site, situation, size, so, social, societal, society, some, someone, sometimes, south, sport, spread, square, state, states, stations, statistical, stereotypes, subjects, such, super, supporters, telethon, telethons, television, tends, term, that, the, their, them, there, these, they, this, those, to, together, total, towards, town, track, trap, treated, try, two, type, under, united, units, up, used, usually, various, versus, volleyball, was, water, way, websites, were, when, which, white, who, wikipedia, with, worldwide, www, years, york\0";
    double tkUnion = 400;

    //PrintAllToken(text1648);
    printf("\n");

    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    printf("\nSimilarity: %f (Threshold in PB %d: %f) Between Email: %d vs %d\n", (tk1099+tk1648 - tkUnion)/ tkUnion,91,0.070000, 1648, 1099);
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