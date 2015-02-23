
/*********************************************/	
/* Auteur : KAI PASCAL ZHANG				*/
/* this c file is for cut an csv in many		*/
/*	Date debut :    09/09/2014			*/
/*	Date derniere : 18/09/2014 			*/
/*							*/
/*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>




#define Max_LINE_CSV 400000
#define Max_LENGTH_CSV 1000
#define line_max 3600 

char** creat_tab(int chang,int kuan){
	int i;
	char** variable;
	variable = (char**)malloc(chang * sizeof(char*));       
	for (i = 0; i < chang; i++)
		variable[i] = (char*)malloc( kuan* sizeof(char));

return variable;
}


void cut(char** tab){
	int ntab,i,tagf,j,n,h;
	char** nomnb;
	char** nom;
	char** z;
	char dig;
	char* d;


	tagf =0;




	z = creat_tab(line_max,Max_LENGTH_CSV);

	ntab = count_tab(tab);
	i = ntab/line_max+1;
	nomnb =  creat_tab(i,4);
	nom =  creat_tab(i,50);
	for(j=0;j<i;j++){
		sprintf(nomnb[j], "%d", j);
		//for(n=0;n<5;n++){
		//nomnb[j][n] = (char)(((int)'0')+j);
		//}
		//nomnb[j][n]='\0';
	printf("nomnb : %s  \n",nomnb[j]);
	}


	// creat the names csv
	for(j=0;j<i;j++){
		strcat(nom[j],nomnb[j]);
		strcat(nom[j],"lognav_Wed_Jun_12_15h17min01sec_2013");   // "lognav_Thu_Aug_23_15h27min02sec_2012"        // RECORD 2.1
	
		//strcat(nom1[j],nom[j]);
		strcat(nom[j],".csv");
	printf("nom[%d ]: %s \n",j,nom[j]);
	}


	h = 1;
	for(j=0;j<i;j++){

		printf("\n****************** Print and make file (.txt or .json) ***************\n");
		FILE *f = fopen(nom[j],"w");
		fprintf(f,tab[0]);
		for(;h<(j+1)*line_max+1;h++)
		{	//z[n] = tab[h];
			//printf("%s \n",tab[h]);
			fprintf(f,tab[h]);
		}
		fclose(f);
	}

		
	

}
int count_tab(char **tab){
	int n;

	n =0;	

	while(tab[n][0] != 'F'){     // a reflechir
		n++;		
	}
	//printf("\nn : %d \n",n=n-1);

	return n;
} 


/********************open fichier csv ************************************/
char** opencsv( char* c){
	int ii,n;
	char** tab;

	tab = creat_tab(Max_LINE_CSV,Max_LENGTH_CSV );
	ii =0;

printf("******************** Lecture du fichier data(.csv) et Construction tableux du donnees*******************\n");

	printf("%s\n",c);
	FILE *csv=fopen(c,"r");
	while(fgets(tab[ii], Max_LENGTH_CSV, csv) != NULL){
		ii++;
	}
	
	tab[ii]= "F\0";
printf("la dernier ligne est: %d , A la fin,je definis le contenu: %s\n",ii,tab[ii]);
	fclose(csv);
printf("******************* Fin de Lecture *******************\n");

return tab;
}



int main(void){
/* variable */
	char** tab;
	char* file;
	int ntab;
/*******************************************************************/
printf("\n**********************    <<  PROGRAMME C : makejson  >>    ********************** \
	\n***** Auteur : kai pascal ZHANG    Version : 0.1       			********** \
	\n***** Date debut :    09/09/2014   					********** \
	\n***** Date derniere : 18/09/2014   			 		********** \
	\n***** Intro :  read an long file csv and cut it in many files csv	********** \
	\n*****   	you can define the max lines				********** \
	\n**********************************************************************************");
/*******************************************************************/



/* generation un tableau qui contient tous les donnees du fichier csv*/
	/************************************************************/
	/* Definitions des variables cachées dan le fichier .csv*/
	/** cette partie a utilise ???      espace**/

	file = (char*)malloc(300*sizeof(char));
	file = "lognav_Wed_Jun_12_15h17min01sec_2013.csv";//"lognav_Thu_Aug_23_15h27min02sec_2012.csv";		 // RECORD 2.2

	printf("\n****************** Ouvrir le fichier data (.csv)*********************\n");
	tab  = opencsv(file);
	ntab = count_tab(tab);
	printf("largeur du csv :%d \n",ntab);  

	cut(tab);

	printf("\n*******************    Fin du programme    *************** \
		\n******************* A la prochaine fois :) ***************\n\n\n\n");

return 1;


}
