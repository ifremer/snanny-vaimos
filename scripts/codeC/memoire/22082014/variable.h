

/*********************************************/	
/* Auteur : KAI PASCAL ZHANG				*/
/* this c file is for generating an file JSON for O&M	*/
/*		begin 	24/07/2014			*/
/*							*/
/*							*/
/*********************************************/
//#include "variable.c"
//#include <uuid/uuid.h>

typedef struct{
	  char *var1;
	  char *var2;
}Vartab;


struct Time{
	  char nian[5];
	  char yue[3];
	  char ri[3];
	  char xinqi[4];
	  char shi[3];
	  char fen[3];
	  char miao[9];
}Time;

/************************************************************/
/*lecture d'un template */
char* readtemp(char* f);
//void readtemp(char* f,char* t);






char* cuuid();

char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao);

char** search_col(char** t,int n);

char** opencsv(char* c);

