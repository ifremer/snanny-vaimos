
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


struct Time* newtime();

struct Time time_demar(int jp, char* file,int* tire);

struct tm* time_to_int(struct Time time);
