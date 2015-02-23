

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kjson.h"

#define MAX_LENGTH_TEMP 5000
#define Max_LENGTH_VAR 50


	/************************************************************/
	/* generate le resulat, lier les phrases et le var2 */

char* generate_template(Vartab *vartab,char** phrase){
	char* resultat;
	int i, n;

	resultat = (char*)malloc(MAX_LENGTH_TEMP*2*sizeof(char));
 	n = count_Vartab(vartab);

	//resultat= ""; 
	printf("\n****************** Generate le resulat, lier les phrases et variables ***************\n");
	printf("il y a %d variable",n);
	//printf("\ninitialize Resultat : %s\n",resultat);
	for(i=0;i<n*2+1;i++){
		if(i%2 ==1){
//printf("\nvariable %d, %s\n",(i-1)/2,vartab[(i-1)/2].var2);
			strcat(resultat,vartab[(i-1)/2].var2);

		}else{
//printf("\nphrase %d, %s\n",i/2,phrase[i/2]);
	       		strcat(resultat,phrase[i/2]);
//printf("flas11111111111\n");
		}
	}

	printf("\nResultat ===> %s\n",resultat);
	printf("\n****************** Fin de la Generate  ***************\n");

return resultat;
}

int count_Vartab(Vartab *vartab){
     int i;

     for (i = 0; vartab[i].var1; i++);

     return (i);
}

void writejson(char* resultat){
	printf("\n****************** Print and make file (.txt or .json) ***************\n");
	FILE *f = fopen("om2.json","w");
	fprintf(f,resultat);
	fclose(f);
}


Vartab* alloc_variable(int nb,char** variable,char* description,char* uuid,char *name,char *latmin,char *lonmin,char * latmax,char * lonmax,char *buffer2,char *buffer3,char *updatetime,char *procedureuri,char *fichiercsv){
	Vartab *vartab1;
	int i;

	vartab1 = (Vartab*)malloc(nb*sizeof(Vartab));
/*	for(i=0;i<nb;i++){
		vartab1[i].var1 = (char* )malloc(Max_LENGTH_VAR*sizeof(char));
		vartab1[i].var2 = (char* )malloc(120*sizeof(char));
	}
*/
	for(i=0;i<nb;i++)
		vartab1[i].var1 =variable[i]; 
	
	
	vartab1[0].var2 = description;      
	vartab1[1].var2 = uuid;
	vartab1[2].var2 = name;
	vartab1[3].var2 = latmin;
	vartab1[4].var2 = lonmin;
	vartab1[5].var2 = latmax;
	vartab1[6].var2 = lonmax;
	vartab1[7].var2 = buffer2;
	vartab1[8].var2 = buffer3;
	vartab1[9].var2 = updatetime;
	vartab1[10].var2 = procedureuri;
	vartab1[11].var2 = fichiercsv;

return vartab1;

}

