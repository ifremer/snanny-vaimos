


#include <stdlib.h>
#include <time.h>
#include "ktime.h"

struct Time* newtime(){
	struct Time *t;
	t = malloc(sizeof(struct Time));
	t->sec = malloc(9*sizeof(char));
	t->min = malloc(9*sizeof(char));
	t->hour = malloc(9*sizeof(char));
	t->mday = malloc(9*sizeof(char));
	t->mon = malloc(9*sizeof(char));
	t->year = malloc(9*sizeof(char));

return t;
}

struct Time time_demar(int jp,char* file,int* tire){			
	    int i;
	    struct Time *time;
		
	   time = newtime();
	    jp =jp-4;
	    for(i=0;i<4;i++){
		time->year[i]=file[jp++];
	    }
	    time->year[i]='\0';
	    jp=tire[1]+1;

	    for(i=0;i<=2;i++){
		time->mon[i]=file[jp++];
	    }
	    time->mon[i]='\0';	    
	    jp=tire[2]+1;
	    for(i=0;i<2;i++){
		time->mday[i]=file[jp++];
	    }
	    time->mday[i]='\0';
	    jp=tire[3]+1;
	    for(i=0;i<2;i++){
		time->hour[i]=file[jp++];
	    }
	    time->hour[i]='\0';
	    jp=tire[3]+4;
	    for(i=0;i<2;i++){
		time->min[i]=file[jp++];
	    }
	    time->min[i]='\0';
	    jp=tire[3]+9;
	    for(i=0;i<2;i++){
		time->sec[i]=file[jp++];
	    }
	    time->sec[i]='\0';

	//printf("abc\n");
	return *time;
}


struct tm* time_to_int(struct Time time){
	struct tm *info;

	int sec,min,hour,mday,mon,year;
	info = (struct tm*)malloc(sizeof(struct tm));

	sec = (float)atof(time.sec);
	min = (int)atof(time.min);
	hour = (int)atof(time.hour);
	mday = (int)atof(time.mday);
	mon = (int)atof(time.mon);
	year = (int)atof(time.year);

	info->tm_sec = (int)sec;
	info->tm_min = min;
	info->tm_hour = hour+1;
	info->tm_mday = mday;
	info->tm_mon = mon;
	info->tm_year = year-1900;
 	info->tm_isdst = -1;
	
	return info;
}
