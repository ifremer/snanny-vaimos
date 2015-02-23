

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



/************************FUNCTION Main **************************************************************************/

int main(int argv, char** argc){
/*******************************************************************/
/*    declaration du variable    */
	char* template;
	int* diez;
	int* var;
	int n,j;
	char** variable ;
	char** phrase;
	char* file1;char* file;
	char** tab;
	char** col2;
	char** col15;
	char** col16;
	int ntab;
	char* name;
	int* tire;
	int i, jp ; 
	struct Time time1;
	struct tm *timeinfo, *int_time1,*int_time2,*int_time3;
	char buffer1[80];char buffer2[80];char buffer3[80];
	time_t rawtime, vt1,vt2,vt3;
	float freq , latminf, latmaxf, lonminf,lonmaxf;
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
	char* ny;char* yr;char* rs;char* sf;char* fm;
	char** var2;
	Vartab *vartab1;
	char* resultat;

/*    declaration du fonction            */   /// ??????????????pas la peine ?????
	//char** search_col(char**,int);	
	//char* cuuid();
	//char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao);

/*******************************************************************/
printf("\n**********************	PROGRAMME C : makejson 	   	    ********************** .\
	\n***** Auteur : kai pascal ZHANG    Version : 0.1       			********** .\
	\n***** Date debut :    17/07/2014   					********** .\
	\n***** Date derniere : 18/09/2014   			 		********** .\
	\n***** Intro :  read an template and find the variables; analyse		********** .\
	\n***** fichier donnees(.csv) en tableau, calcule some variables  	********** .\
	\n***** that we need; make a new file(.json);			 	********** .\
	\n********************************************************************************** .\
	\n**********************				    	    ********************** .\
	\n***** 								        ********** .\
\n");
/*******************************************************************/

	/************************************************************/
	/** cette partie a utilise ???      espace**/
	/*lecture d'un template */
	template = readtemp("templateOMracourci.json");

	/* test for an template exemple  */
	/*const char template[1500] = "[\"om:OM_Observationfe\",\
	{###date###},\
	[\"gml:descri###name###fzffdzzf\",\"fdafd###uuid###ff\"]\
	]\
	";   */
	/*const char template1[1500] =  "[\"om:OM_Observationfe\",\
	{###date###},\
	[\"gml:descri###name###fzffdzzf\",\"fdafd###uuid###ff\"]\
	]\
	";      */                      
	printf("\nTEMPLATE ===> %s\n",template);
	//printf("\nTEMPLATE 1 : %s\n",template1);

	/************************************************************/
	/** cette partie a utilise ???      espace**/
	/* parcour the template and find the variables       */
	printf("\n******************** Parcour the template ***********************\n");
	diez= search_diez(template);
	var = search_3diez(template);
	j = count(diez);
	n = count(var);

	/************************************************************/
	/** cette partie a utilise ???      espace**/
	/* return all variables in original template */
	printf("\n******************* Return tous les variables et coupe le template en plusieur phrase **********\n");

	variable = findvar(template,var,j);

	/* couper template en n/2 +1 morceaux et return all phrase*/
	phrase = findphr(template,var,n);


	/************************************************************/
	/** cette partie a utilise ???      espace**/
	/* Extraction des donnes dan le fichier .csv*/
	/* ouvrir le fichier .csv et creer un tableau pour enregiestrer tous les donnees*/
	printf("\n****************** Ouvrir le fichier data (.csv)*********************\n");
	file1 = "lognav_Wed_Jun_12_10h10min02sec_2013.csv";	  //kailognav_Wed_Jun_12_14h57min01sec_2013.csv
	//file = "mycsv.csv";	
	tab = opencsv(file1);
	ntab =count_tab(tab);
	printf("largeur du csv :%d \n",ntab);    // je ne peut pas test le length du tab ave **tab

	/* choisissons une colone que nous interesse ;
	 pour eviter de faire un type*** , nous ferons un type** */
	col2 = search_col(tab,2);
	col15 = search_col(tab,15);
	col16 = search_col(tab,16);

		/*//printf(" col 2:%s \n",col2[5]);  
		int ntab2;
		ntab2 =count_tab(col2);
		printf("largeur du col2 :%d \n",ntab2);  */

	/* calculer lattitude maximum et le minimum  */
	//printf("flashhhhhhhhh\n");
	latminf = find_minlat(col15);
	//printf("flashhhhhhhhh\n");
	latmaxf = find_maxlat(col15);

	//printf("###lattitude maximum### = %f,###lattitude minimum### = %f \n",latmaxf,latminf);

	/* calculer la longitude maximum et le minimum  */

	lonminf = find_minlon(col16);
	lonmaxf = find_maxlon(col16);
	
	//printf("###longitude maximum### = %f,###longitude minimum### = %f \n",lonmaxf,lonminf);

	/************************************************************/
	/* recuperer le nom */ 
	name = findname(file1);
	printf("\n###name### = %s \n",name);
	
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
	printf("###frequence d'echantillion### = %f \n",freq);

	


	/**************** definition tous les variables ***************/
	description= "one time test";
	printf(" ###description### = %s\n",description);

	uuid = cuuid();
	//printf("flashhhhhhhhh\n");
	latmin = float_to_char(latminf);    
	latmax = float_to_char(latmaxf); 
	lonmin = float_to_char(lonminf); 
	lonmax = float_to_char(lonmaxf); 

	time(&rawtime);
  	timeinfo = localtime (&rawtime);
	updatetime =  asctime(timeinfo);		//"2013-06-12T15:13:02.0";
	procedureuri = "http://www.flakey.org/register/process/scales34.xml#platform_number";
	fichiercsv = "file:///home/isi-projets/sensorNanny/data/vaimos/nav/kailognav_Wed_Jun_12_14h57min01sec_2013.csv";

	printf(" ###lattitude maximum### = %s,###lattitude minimum### = %s \n",latmax,latmin);
	printf(" ###longitude maximum### = %s,###longitude minimum### = %s \n",lonmax,lonmin);
	printf(" ###timebegin###         = %s\n",buffer2);
	printf(" ###timeend###   	 = %s\n",buffer3);
	printf(" ###updatetime### 	 = %s\n",updatetime);
	printf(" ###procedureuri### 	 = %s\n",procedureuri);
	printf(" ###fichiercsv### 	 = %s\n",fichiercsv);

	printf("\n***************** Definition des variable detminée ********************\n");

	/************************************************************/
	/* creat les variables que nous allons utiliser appelé "var2" tableau  */

	vartab1 = alloc_variable(n/2,variable,description,uuid,name,latmin,lonmin,latmax,lonmax,buffer2,buffer3,updatetime,procedureuri,fichiercsv);
    	
	//printf("\nnew variable table var1 = %s \n",vartab1[0].var1);

	/************************************************************/
	/* generate le resulat, lier les phrases et le var2 */
	printf("\n****************** Generate le resulat, lier les phrases et variables ***************\n");
	resultat = generate_template(vartab1,phrase);
	printf("\n****************** Fin de la Generate  ***************\n");

	/************************************************************/
	/* print and make file .txt or .json  */
	printf("\n****************** Print and make file (.txt or .json) ***************\n");
	writejson(resultat);
	printf("\n******************* Fin du programme ***************");
	printf("\n******************* A la prochaine fois :) ***************\n\n\n\n");

	/* :::::::::::::::::::)liberation tous les variables:::::::::::::::::::::::::::)*/
	//free(tab);

	/* ???????? pourquoi il dit segmentation fault  */

	return EXIT_SUCCESS;

}
