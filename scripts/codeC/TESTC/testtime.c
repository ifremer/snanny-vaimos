#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//  !!!!!!!!!!!!! complique malloc pour struct
struct Time{
	  char *sec;
	  char *min;
	  char *hour;
	  char *mday;       /* day of the month, range 1 to 31  */
	  char *mon;
	  char *year;
	  char *wday;
	  char *yday;   // n'utilise pas
          char *isdst;  // n'utilise pas

}Time;
/*
struct Time *newTime () {
    // Try to allocate vector structure.

    struct Time *val = malloc (sizeof (struct Time));
    if (val == NULL)
        return NULL;

    // Try to allocate vector data, free structure if fail.

    retVal->data = malloc (sz * sizeof (double));
    if (retVal->data == NULL) {
        free (retVal);
        return NULL;
    }

    // Set size and return.

    retVal->size = sz;
    return retVal;
}*/
int main(void ){

/*
      time_t rawtime;
   struct tm *info;
   char buffer[80];

   time( &rawtime );

   info = localtime( &rawtime );

   strftime(buffer,80,"%x - %I:%M%p", info);
   printf("Formatted date & time : |%s|\n", buffer );
*/
struct Time *t;
struct tm *info;
float sec;
int min,hour,mday,mon,year,wday;
time_t vt,vt2;

char buffer[80];
struct tm *time2;
struct tm *time3;


t = malloc(sizeof(struct Time));
t->sec = malloc(9*sizeof(char));
t->min = malloc(9*sizeof(char));
t->hour = malloc(9*sizeof(char));
t->mday = malloc(9*sizeof(char));
t->mon = malloc(9*sizeof(char));
t->year = malloc(9*sizeof(char));

info = malloc(sizeof(struct tm));
info->tm_sec =(int )malloc(sizeof(int));
info->tm_min =(int )malloc(sizeof(int));
info->tm_hour =(int )malloc(sizeof(int));
info->tm_mday =(int )malloc(sizeof(int));
info->tm_mon =(int )malloc(sizeof(int));
info->tm_year =(int )malloc(sizeof(int));

//t->wday = malloc(9*sizeof(char));
	t->sec = "17.865";
	t->min ="55";
	t->hour = "13";
	t->mday = "18";
	t->mon ="12";
	t->year = "2013";
	//t->wday = "jeu";
sec = (float)atof(t->sec);
min = (int)atof(t->min);
hour = (int)atof(t->hour);
mday = (int)atof(t->mday);
mon = (int)atof(t->mon);
year = (int)atof(t->year);


info->tm_sec = (int)sec;
info->tm_min = min;
info->tm_hour = hour;
info->tm_mday = mday;
info->tm_mon = mon;
info->tm_year = year-1901;
 info->tm_isdst = -1;
//printf("%d, %d ,%d ,%d ,%d,   %f,%d",year,mon,mday,hour,min,sec,(int)sec);
      strftime(buffer, sizeof(buffer), "%c", info );
      printf(buffer);
      printf("\n\n\n");
vt = mktime(info);

if( vt == -1 )
   {
       printf("Error: unable to make time using mktime\n");
   }
   else
   {
      strftime(buffer, sizeof(buffer), "%c", info );
      printf(buffer);
   }
printf("\nvt : = %d\n",vt);


vt2 = vt+10;
time2 = gmtime(&vt2);
      strftime(buffer, sizeof(buffer), "%c", time2 );
      printf(buffer);

//printf("%d, %d ,%d ,%d ,%d, %d",info->tm_year,info->tm_mon,info->tm_mday,info->tm_hour,info->tm_min,info->tm_sec);

return 0;
}
