

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "csv.h"
#include "ktab.h"

#define Max_LINE_CSV 400000
#define Max_LENGTH_CSV 1000


/********************open fichier csv ************************************/
char** opencsv( char* c){
	int ii,n;
	char** tab;
	//char* title;	

	
	//title =  (char*)malloc(200*sizeof(char));
	tab = creat_tab(Max_LINE_CSV,Max_LENGTH_CSV );
	ii =0;

printf("******************** Lecture du fichier data(.csv) et Construction tableux du donnees*******************\n");

/* ce repertoire doit etre pareil */
/*

"/home3/homedir4/perso/tloubrie/projets/sensorNanny/vaimos/vaimoskai/codeC/files_csv/lognav_Wed_Jun_12_14h57min01sec_2013.csv"
"file:///home/isi-projets/sensorNanny/data/vaimos/nav/lognav_Wed_Jun_12_14h57min01sec_2013.csv"

*/
	//title = "lognav_Wed_Jun_12_14h57min01sec_2013.csv";   
	printf("%s\n",c);
	FILE *csv=fopen(c,"r");
	while(fgets(tab[ii], Max_LENGTH_CSV, csv) != NULL){
			//printf("tab[%d] : %s ",ii,tab[ii]);
		ii++;
	}
	
	tab[ii]= "F\0";
printf("la dernier ligne est: %d , A la fin,je definis le contenu: %s\n",ii,tab[ii]);
	fclose(csv);
printf("******************* Fin de Lecture *******************\n");
//printf("tab[%d] : %s \n",0,tab[0]);

return tab;
}





/********************searche colone   ************************************/
char** search_col(char** t,int n){
						//!!!!!!! ameliorer cette partie de code, si n est sort du nb collone du t;
						//!!!!!!! pas specialiser le coupe ',', plus intelligent;
// chercher le premier element
	// test la taille du table
	int  ne,i,nc ;	 //int nl;
	char** ct; 
	//char* c;
	
	nc=30;// max de caracteres pour une colone

	ne = count_tab(t);
	ct = creat_tab(ne,nc);

	//pour premier colone
	for(i=0;i<ne;i++)
		ct[i] = s_col1(t[i] ,n,';');       // dependre des fichier csv, le separtaeur soit ; soit ,
		//printf("colone : %s\n",c);
	ct[i]="F\0";


	
/*	// print ct[]
	for(i=0;i<ne;i++){
		printf("colone %d : %s\n",i,ct[i]);
	}
*/
	return ct;
}




char* float_to_char(float f){
	char *l;
	
	l = (char*)malloc(9*sizeof(char));

	snprintf(l,9,"%f",f);
return l;
}




