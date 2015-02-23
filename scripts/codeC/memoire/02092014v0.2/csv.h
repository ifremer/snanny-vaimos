








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


char** opencsv(char* c);

char** search_col(char** t,int n);



char* findname(char* file);

int findpoint(char* file);

int* findtire(char *file);

struct Time* newtime();

struct Time time_demar(int jp,char* file,int* tire);

struct tm* time_to_int(struct Time time);

float find_minlat(char** col);
float find_maxlat(char** col);
float find_minlon(char** col);
float find_maxlon(char** col);

char* float_to_char(float f);

