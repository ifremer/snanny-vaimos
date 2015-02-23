

/*********************************************/	
/* Auteur : KAI PASCAL ZHANG				*/
/* this c file is for generating an file JSON for O&M	*/
/*		begin 	17/07/2014			*/
/*							*/
/*							*/
/*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include "variable.h"

#define MAX_VARIABLE 20


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
	int i, jp ,fen; 
	struct Time time1;
	float fmiao1,fmiao2,fmiao3;
	char* miao2;
	char* miao3;
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
	char** var2;//[n/2][100];
	Vartab *vartab1;//[MAX_VARIABLE];
	char* resultat;
/*    declaration du fonction            */
	//char** search_col(char**,int);	
	//char* cuuid();
	//char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao);
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

	printf("###lattitude maximum### = %f,###lattitude minimum### = %f \n",latmaxf,latminf);

	/* calculer la longitude maximum et le minimum  */

	lonminf = find_minlon(col16);
	lonmaxf = find_maxlon(col16);
	
	printf("###longitude maximum### = %f,###longitude minimum### = %f \n",lonmaxf,lonminf);
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
	printf("Nian :%s\n",time1.nian);printf("Yue :%s\n",time1.yue);printf("Ri :%s\n",time1.ri);printf("Shi :%s\n",time1.shi);printf("Fen :%s\n",time1.fen);printf("Miao :%s\n",time1.miao);
*/
	/* convertir en entier          */
	fen  = time_to_int(time1.fen);
	fmiao1 = time_to_int(time1.miao);
	//fmiao1= miao_to_int(time1);


	/* recuperer le temps de debute */
	
	fmiao2 = fmiao1 + (float)atof(col2[1]);
	//printf("Miao2 float: %f \n",fmiao2);
	miao2 = (char*)malloc(10*sizeof(char));
	snprintf(miao2,9,"%f",fmiao2);
	//printf("Miao2 string :%s\n",miao2);

	/* recuperer le temps de termine */	

	fmiao3 = fmiao1 + (float)atof(col2[ntab-1]);
	//printf("Miao3 float: %f \n",fmiao3);
	miao3 = (char*)malloc(10*sizeof(char));
	snprintf(miao3,9,"%f",fmiao3);
	//printf("Miao3 string :%s\n",miao3);		


	/* calculer la frequence d'echantillion */
	freq = 1/(fmiao3-fmiao2)*ntab; 
	printf("###frequence d'echantillion### = %f \n",freq);

	


	/**************** definition tous les variables ***************/
	description= "one time test";
	printf(" ###description### = %s\n",description);
	uuid = cuuid();
//printf("flashhhhhhhhh\n");
	//latmin = float_to_char(latminf);      a faire
	latmin = (char*)malloc(9*sizeof(char));
	latmax = (char*)malloc(9*sizeof(char));
	lonmin = (char*)malloc(9*sizeof(char));
	lonmax = (char*)malloc(9*sizeof(char));
	snprintf(latmin,9,"%f",latminf);
	snprintf(latmax,9,"%f",latmaxf);
	snprintf(lonmin,9,"%f",lonminf);
	snprintf(lonmax,9,"%f",lonmaxf);
	
	ny="-";yr="-";rs="T";sf=":"; fm=":";
	timebegin =compositeTime(time1.nian,ny,time1.yue,yr,time1.ri,rs,time1.shi,sf,time1.fen,fm,miao2); 
	printf(" ###timebegin### = %s\n",timebegin);
	timeend =compositeTime(time1.nian,ny,time1.yue,yr,time1.ri,rs,time1.shi,sf,time1.fen,fm,miao3); 
	printf(" ###timeend### = %s\n",timeend);
	updatetime = "2013-06-12T15:13:02.0";
	printf(" ###updatetime### = %s\n",updatetime);
	procedureuri = "http://www.flakey.org/register/process/scales34.xml#platform_number";
	printf(" ###procedureuri### = %s\n",procedureuri);
	fichiercsv = "file:///home/isi-projets/sensorNanny/data/vaimos/nav/kailognav_Wed_Jun_12_14h57min01sec_2013.csv";
	printf(" ###fichiercsv### = %s\n",fichiercsv);

	printf("\n***************** Definition des variable detminée ********************\n");

	/************************************************************/
	/* creat les variables que nous allons utiliser appelé "var2" tableau  */

		//= {{var[0],description},{var[1],description}};		
		//printf("\nvar[0] %s \n",var[0]);
	vartab1[0].var1 = variable[0];vartab1[0].var2 = description;      // totot a faire    boocle
	vartab1[1].var1 = variable[1];vartab1[1].var2 = uuid;
	vartab1[2].var1 = variable[2];vartab1[2].var2 = name;
	vartab1[3].var1 = variable[3];vartab1[3].var2 = latmin;
	vartab1[4].var1 = variable[4];vartab1[4].var2 = lonmin;
	vartab1[5].var1 = variable[5];vartab1[5].var2 = latmax;
	vartab1[6].var1 = variable[6];vartab1[6].var2 = lonmax;
	vartab1[7].var1 = variable[7];vartab1[7].var2 = timebegin;
	vartab1[8].var1 = variable[8];vartab1[8].var2 = timeend;
	vartab1[9].var1 = variable[9];vartab1[9].var2 = updatetime;
	vartab1[10].var1 =variable[10];vartab1[10].var2 = procedureuri;
	vartab1[11].var1 =variable[11];vartab1[11].var2 = fichiercsv;
	//printf("\nnew variable table var1 = %s \n",vartab1[0].var1);

	/************************************************************/
	/* generate le resulat, lier les phrases et le var2 */
	printf("\n****************** Generate le resulat, lier les phrases et variables ***************\n");
	resultat = generate_template(vartab1,phrase);

	/************************************************************/
	/* print and make file .txt or .json  */
	printf("\n****************** Print and make file (.txt or .json) ***************\n");
	writejson(resultat);
	printf("\n******************* Fin du programme ***************\n");

/* :::::::::::::::::::)liberation tous les variables:::::::::::::::::::::::::::)*/
	free(tab);

	return 1;
}
