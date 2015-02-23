

/*********************************************/	
/* Auteur : KAI PASCAL ZHANG				*/
/* this c file is for generating an file JSON for O&M	*/
/*	Date debut :    17/07/2014			*/
/*	Date derniere : 18/09/2014 			*/
/*							*/
/*********************************************/



#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <time.h>

#include "template.h"
#include "csv.h"
#include "kuuid.h"
#include "kjson.h"

#define nb_descrip 200



/************************FUNCTION Main **************************************************************************/

int main(int argv, char** argc){
/*******************************************************************/
/*    declaration du variable    */		//   il depense total: oct 
	// variables pour gerer du template
	char* template;
	int* diez;	// diez: position dans le template
	int* var;	// var : position du premier diez dans les trois diez
	int n,j; 	//n: 2 fois de nb variable; j : nb de diez
	char** variable ;// enregistre des variables dans un tableau ligne par ligne
	char** phrase;	// enregistre les restes parties du template ligne par ligne

	// variables pour lire des tableau et choisir le vecteur dans csv
	char* file1;	//char* file;
	char** tab;	// tab : recupere le tableau du csv
	int ntab;	// ntab: la nb du ligne du tab
	char** col2;	// col2 :  deuxieme collone du tab en separant par ","
	char** col15;	// col15:  quinzieme collone du tab
	char** col16;	
	float freq , latminf, latmaxf, lonminf,lonmaxf; // pour la frequence d'echantillon; lattitude ; longitude;

	char* name;	// name : nom du csv
	int* tire;	// tire : la position du "_" dans name
	int jp ; 	// jp : la postion du point dans name

	struct Time time1;	// time1 :  extraire des temps dans name
	struct tm *timeinfo, *int_time1,*int_time2,*int_time3; // timeinfo : localtime; int_time1: temps indique dans le name; int_time2: temps 1er value int_time3 : temps dernier value
	char buffer1[30];char buffer2[30];char buffer3[30];// buffer123 corresponds int_time123;
	time_t rawtime, vt1,vt2,vt3;   // time_t : time en seconde; rawtime :  temps local;vt123 correspond int_time123

	char* description;
	char* uuid;	//char *uuid = "c6fad940-5413-4c59-a98d-7ff4855301b4";
	char* latmin;
	char* latmax;
	char* lonmin;
	char* lonmax;
	char* updatetime;
	char* procedureuri;
 	char* fichiercsv;
	char* timebegin;char *timeend;

	Vartab *vartab1;
	char* resultat;

/*    declaration du fonction            */   /// ??????????????pas la peine ?????
	//char** search_col(char**,int);	
	//char* cuuid();
	//char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao);

/*******************************************************************/
printf("\n**********************    <<  PROGRAMME C : makejson  >>    ********************** \
	\n***** Auteur : kai pascal ZHANG    Version : 0.1       			********** \
	\n***** Date debut :    17/07/2014   					********** \
	\n***** Date derniere : 18/09/2014   			 		********** \
	\n***** Intro :  read an template and find the variables; analyse		********** \
	\n***** fichier donnees(.csv) en tableau, calcule some variables  	********** \
	\n***** that we need; make a new file(.json);			 	********** \
	\n**********************************************************************************");
/*******************************************************************/

	/************************************************************/
	/** cette partie a utilise depend la taille du fichier ici 1440 caracters  **/  //   il depense total: oct 
	/*lecture d'un template */
	template = readtemp("templateOMracourci.json");               

	//printf("\nTEMPLATE 1 : %s\n",template1);

	/************************************************************/
	/** cette partie a utilise ???      espace**/
	/* parcour the template and find the variables       */
	printf("\n******************** Parcour the template ***********************\n");
	diez= search_diez(template);
	var = search_3diez(template);
	j = count(diez);
	n = count(var);

	free(diez);
	/************************************************************/
	/** cette partie a utilise ???      espace**/
	/* return all variables in original template */
	printf("\n******************* Return tous les variables et coupe le template en plusieur phrases**********\n");

	variable = findvar(template,var,j);

	/* couper template en n/2 +1 morceaux et return all phrase*/
	phrase = findphr(template,var,n);

	free(template);free(var);
	/************************************************************/
	/* Definitions des variables cachées dan le fichier .csv*/
	/** cette partie a utilise ???      espace**/

	file1 = (char*)malloc(50*sizeof(char));
	file1 = "lognav_Wed_Jun_12_10h10min02sec_2013.csv";	  //kailognav_Wed_Jun_12_14h57min01sec_2013.csv
	//file = "mycsv.csv";	

	/* recuperer le nom */ 
	name = findname(file1);

	/* ouvrir le fichier .csv et creer un tableau pour enregiestrer tous les donnees*/
	printf("\n****************** Ouvrir le fichier data (.csv)*********************\n");
	tab  = opencsv(file1);
	ntab = count_tab(tab);
	printf("largeur du csv :%d \n",ntab);    // je ne peut pas test le length du tab ave **tab

	/* choisissons une colone que nous interesse ;
	 pour eviter de faire un type*** , nous ferons un type** */
	col2 = search_col(tab,2);

		/*//printf(" col 2:%s \n",col2[5]);  
		int ntab2;
		ntab2 =count_tab(col2);
		printf("largeur du col2 :%d \n",ntab2);  */

	/* recuperer la position de tire "-"*/
	tire = findtire(file1);
	//printf("tirer :%d %d %d %d\n",tire[0],tire[1],tire[2],tire[3]);
		
	/* recuperer la position du point "."*/
	jp = findpoint(file1);

	/* recuperer le temps de demarage */	
	time1 = time_demar(jp,file1,tire);
/*
	printf("year :%s\n",time1.year);
	printf("mon :%s\n",time1.mon);printf("mday :%s\n",time1.mday);printf("hour :%s\n",time1.hour);printf("min :%s\n",time1.min);printf("sec :%s\n",time1.sec);
*/
	/* convertir de char* en int          */
	int_time1 = time_to_int(time1);

	vt1 = mktime(int_time1);
	vt2 = vt1 +  (int)atof(col2[1]);
	vt3 = vt1 +  (int)atof(col2[ntab-1]);
	//printf("\n vt  =%d , %d %d",vt,vt2,vt3);

	/* convertir de int a char */
	int_time1= gmtime(&vt1);
      	strftime(buffer1, sizeof(buffer1), "%c", int_time1 );
      	printf("\nTime demarage :");printf(buffer1); 

    	/* recuperer le temps de debute */
	int_time2 = gmtime(&vt2);
      	strftime(buffer2, sizeof(buffer2), "%c", int_time2 );
      	printf("\nTime begin    :");printf(buffer2);

	/* recuperer le temps de termine */	
	int_time3 = gmtime(&vt3);
    	strftime(buffer3, sizeof(buffer3), "%c", int_time3 );
      	printf("\nTime end      :");printf(buffer3);

	/* calculer la frequence d'echantillion */
	freq = ntab/(vt3-vt2); 
	printf("\n###frequence d'echantillion### = %f (Hz)\n",freq);

	
	/* calculer lattitude maximum et le minimum  */
	col15 = search_col(tab,15);
	//printf("flashhhhhhhhh\n");
	latminf = find_minlat(col15);
	latmaxf = find_maxlat(col15);
	//printf("###lattitude maximum### = %f,###lattitude minimum### = %f \n",latmaxf,latminf);

	/* calculer la longitude maximum et le minimum  */
	col16 = search_col(tab,16);
	lonminf = find_minlon(col16);
	lonmaxf = find_maxlon(col16);
	//printf("###longitude maximum### = %f,###longitude minimum### = %f \n",lonmaxf,lonminf);

	/* transformer en char */
	latmin = float_to_char(latminf);    
	latmax = float_to_char(latmaxf); 
	lonmin = float_to_char(lonminf); 
	lonmax = float_to_char(lonmaxf); 


	/************************************************************/
	/* Definitions des variables vennant de machine             */
	uuid = cuuid();

	time(&rawtime);
  	timeinfo = localtime (&rawtime);
	updatetime =  asctime(timeinfo);		//"2013-06-12T15:13:02.0";

	/*************************************************************/
	/** Configuration tous les variables qui est fait a la main **/
	description  = (char*)malloc(nb_descrip*sizeof(char));
	procedureuri = (char*)malloc(120*sizeof(char));
	fichiercsv   = (char*)malloc(120*sizeof(char));

	description  = "one time test";
	procedureuri = "http://www.flakey.org/register/process/scales34.xml#platform_number";
	fichiercsv   = "file:///home/isi-projets/sensorNanny/data/vaimos/nav/kailognav_Wed_Jun_12_14h57min01sec_2013.csv";

	/**************** affichage de tous les variables ***************/

	printf(" ###description### = %s\n",description);
	printf(" ###name### = %s \n",name);
	printf(" ###lattitude maximum### = %s, ###lattitude minimum### = %s \n",latmax,latmin);
	printf(" ###longitude maximum### = %s, ###longitude minimum### = %s \n",lonmax,lonmin);
	printf(" ###timebegin###         = %s\n",buffer2);
	printf(" ###timeend###   	 = %s\n",buffer3);
	printf(" ###updatetime### 	 = %s",updatetime);
	printf(" ###procedureuri### 	 = %s\n",procedureuri);
	printf(" ###fichiercsv### 	 = %s\n",fichiercsv);

	printf("\n***************** Definition des variable detminée ********************\n");

	/************************************************************/
	/* creat les variables que nous allons utiliser appelé "var2" tableau  */

	vartab1 = alloc_variable(n/2,variable,description,uuid,name,latmin,lonmin,latmax,lonmax,buffer2,buffer3,updatetime,procedureuri,fichiercsv);
    	
	//printf("\nnew variable table var1 = %s \n",vartab1[0].var1);
						//?????????????, si je doit for(i=0;i<; i++ )free(); ??
	freetab(variable,n/2);
	/************************************************************/
	/* generate le resulat, lier les phrases et le var2 */
	resultat = generate_template(vartab1,phrase);

	/************************************************************/
	/* print and make file .txt or .json  */
	writejson(resultat);
	printf("\n*******************    Fin du programme    *************** \
		\n******************* A la prochaine fois :) ***************\n\n\n\n");

	/* :::::::::::::::::::)liberation tous les variables:::::::::::::::::::::::::::)*/
										//?????? free tous les variable en meme temps ??
	//freetab(tab,ntab-10);
	freetab(phrase,n/2+1);
	freetab(col2,ntab);
	freetab(col15,ntab);
	freetab(col16,ntab);

	//free(file1);			on ne peut pas le free ????
	//printf("%s",fichiercsv);
	//free(description);
	free(name);free(tire);
	free(latmax);free(latmin);free(lonmax);free(lonmin);
	//free(updatetime);
//	free(procedureuri);
//	free(fichiercsv);


	return EXIT_SUCCESS;

}
