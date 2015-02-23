

/*********************************************/	
/* Auteur : KAI PASCAL ZHANG				*/
/* this c file is for generating an file JSON for O&M	*/
/*		begin 	24/07/2014			*/
/*							*/
/*							*/
/*********************************************/


typedef struct{
	  char *var1;
	  char *var2;
}Vartab;


struct Time{
	  char nian[5];
	  char yue[4];
	  char ri[3];
	  char xinqi[4];
	  char shi[3];
	  char fen[3];
	  char miao[9];
}Time;

/************************************************************/
/*lecture d'un template */
char* readtemp(char* f);

int* search_diez(char *templat);

int* search_3diez(char *templat);

int count(int *tab);

char** findvar(char* templat,int* var,int j);

char** findphr(char* templat,int* var,int n);

char** opencsv(char* c);

char** search_col(char** t,int n);

int count_tab(char **tab);

char* findname(char* file);
int* findtire(char *file);
int findpoint(char* file);

struct Time time_demar(int jp,char* file,int* tire);


int time_to_int(char* time);

float find_minlat(char** col);
float find_maxlat(char** col);
float find_minlon(char** col);
float find_maxlon(char** col);

char* cuuid();

char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao);


char* generate_template(Vartab *vartab,char** phrase);

int count_Vartab(Vartab *vartab);

void writejson(char* resultat);

