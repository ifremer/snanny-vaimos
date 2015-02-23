typedef struct{
	  char *var1;
	  char *var2;
}Vartab;




char* generate_template(Vartab *vartab,char** phrase);

int count_Vartab(Vartab *vartab);

void writejson(char* resultat);

Vartab* alloc_variable(int nb,char** variable,char* description,char* uuid,char *name,char *latmin,char *lonmin,char * latmax,char * lonmax,char *buffer2,char *buffer3,char *updatetime,char *procedureuri,char *fichiercsv);
