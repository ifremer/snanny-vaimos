

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
//#include "variable.h"
#include "variable.c"


/************************FUNCTION Main **************************************************************************/

int main(int argv, char** argc){

	/************************************************************/
	/*lecture d'un template */
	char* template;
	template = readtemp("templateOMracourci.json");



	/************************************************************/
	/* write an template which contains all the OMjson context  */
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
	printf("\nTEMPLATE : %s\n",template);
	//printf("\nTEMPLATE 1 : %s\n",template1);

	/************************************************************/
	/* parcour the template and find the variables       */
	printf("\n************************parcour the template ***********************\n");
	//int* diez = search3diez(template);

	char c='a';int i=0; int j= 0;
	int diez[100]; // admettons que les nbs de diez est inférieur 100;
	char* pt = template;

	/* rechercher des diez */
	while(pt[i] !='\0'){
		c = pt[i];
		if(c=='#'){
		  diez[j]= i;
		  printf("%i\n",i);
		  j++;
		}
		i++;

	};
	
	/*rechercher des diez 3 continue*/
	int var[15];//admettons que les nbs de variables est inférieur 15;
	int n=0;
	// si on trouve 3 diéz continues , enregirester le premier diez
	for(i=0;i<j-2;){
		if((diez[i]+diez[i+2])/2==diez[i+1]){
			var[n]=diez[i];
			//printf("\n var[]: %i\n",var[n]);
			n++;i=i+3;
			}else
			     i++;
	}
	printf("\nlengths of variables: %i\n",n);
	//printf("\nssssssTEMPLATE : %s\n",template);
	//printf("\noooooooTEMPLATE 1 : %s\n",template1);

	/* justifier if ### is pairs */
	if(n%2 == 0){
		printf("text is right ! there is %i # ,donc %i variables.",j,n/2);
	}else{
		printf("text is wrong !there is %i # .",j);
	}


	/************************************************************/
	/* return all variables in original template */
	printf("\n***********return all variables in original template**********\n");
	int vj ; int va=0;
	int nomv=0;int nomj=0; char variable[n/2][20];
	char* template1= template;

	for(vj = 0; vj< j/6;vj++){

		nomj=0;
		for(nomv=var[va] ;nomv<=var[va+1]+2;nomv++,nomj++){
			variable[vj][nomj]= template1[nomv];
				
		}
		
		variable[vj][nomj] ='\0';
		printf("\nvariable %i = %s \n",vj,variable[vj]);
		va=va+2;
	}
	/* couper template en n/2 +1 morceaux et return all phrase*/
	char phrase[n/2+1][500];
	va =0;
	for(vj=0;vj<n/2+1;vj++){
		nomj=0;
		if(vj==0){      // first partie
			for(nomv=0 ;nomv< var[va];nomv++,nomj++){
					phrase[vj][nomj]= template[nomv];

		//printf("first partie%i %i template[%c]",nomj,nomv,template[nomv]);
		   	  }
		}
		else if(vj==n/2){   // last partie
			for(nomv=var[va-1]+3;nomv<=strlen(template);nomv++,nomj++){
					phrase[vj][nomj]= template[nomv];
		   	  }
		}
		else {      	//  milieu partie
			for(nomv=var[va-1]+3;nomv<=var[va]-1;nomv++,nomj++){
					phrase[vj][nomj]= template[nomv];
			      }
		}

	phrase[vj][nomj] ='\0';
	printf("\nphrase %i = %s \n",vj,phrase[vj]);
	va=va+2;

	}

	/************************************************************/
	/* Extraction des donnes dan le fichier .csv*/
	/*ouvrir le fichier .csv et creer un tableau pour enregiestrer tous les donnees*/
	printf("\n********ouvrir le fichier .csv*********************\n");
	char* file1 = "lognav_Wed_Jun_12_10h10min02sec_2013.csv";	  //kailognav_Wed_Jun_12_14h57min01sec_2013.csv
	char* file = "mycsv.csv";	
	char** tab = opencsv(file1);
	printf("largeur du csv :%d \n",strlen(*tab));    // je ne peut pas test le length du tab ave **tab
	/* choisissons une colone que nous interesse ;
	 pour eviter de faire un type*** , nous ferons un type** */
	char** search_col(char**,int);	// declaration du fonction
	char** col2;
	char** col15;
	char** col16;
	col2 = search_col(tab,2);
	col15 = search_col(tab,15);
	col16 = search_col(tab,16);
	int ne1 =0;	
	while(tab[ne1][1] !='\0'){
		ne1++;		
	}printf("nel : %d \n",ne1=ne1-1);

	/************************************************************/
	/* recuperer le nom */
	
	char name[70];int jp;int tire[4];
	j=0;
	for(i=0;i<strlen(file1);i++){
		if(file1[i]=='_') tire[j++]=i;
	}
	for(i=0;i<strlen(file1);i++){
		if(file1[i]!='.'){
			name[i]=file1[i];
			//printf("%s\n",name);
		}else {jp =i;break;}
	}//  
	
	printf("\nname : %s \n",name);
	//printf("tirer :%d %d %d %d\n",tire[0],tire[1],tire[2],tire[3]);
	

	/* recuperer le temps de demarage */
	jp =jp-4;
	struct Time time1;
	//void constrtime(Time,int jp,char * file);
	//constrtime(time1,jp,file1);
	    for(i=0;i<4;i++){
		time1.nian[i]=file1[jp++];
	    }
	    jp=tire[1]+1;
	    for(i=0;i<=2;i++){
		time1.yue[i]=file1[jp++];
	    }
	    
	    jp=tire[2]+1;
	    for(i=0;i<2;i++){
		time1.ri[i]=file1[jp++];
	    }
	    jp=tire[3]+1;
	    for(i=0;i<2;i++){
		time1.shi[i]=file1[jp++];
	    }
	    jp=tire[3]+4;
	    for(i=0;i<2;i++){
		time1.fen[i]=file1[jp++];
	    }
	    jp=tire[3]+9;
	    for(i=0;i<2;i++){
		time1.miao[i]=file1[jp++];
	    }
	printf("Nian :%s\n",time1.nian);
	printf("Yue :%s\n",time1.yue);
	printf("Ri :%s\n",time1.ri);
	printf("Shi :%s\n",time1.shi);
	int fen;float miao1;
	   fen= (int)(time1.fen[0]-'0')*10+(int)(time1.fen[1]-'0');
	printf("Fen :%d\n",fen);
	   miao1= (int)(time1.miao[0]-'0')*10+(int)(time1.miao[1]-'0');
	printf("Miao :%f\n",miao1);

	/* recuperer le temps de debute */
	struct Time time2;
	float miao2;	
	miao2 = miao1 + (float)atof(col2[1]);
	printf("Miao2 : %f \n",miao2);
	snprintf(time2.miao,9,"%f",miao2);
	printf("time2Miao :%s\n",time2.miao);
	/* recuperer le temps de termine */

	
	struct Time time3;
	float miao3;
	miao3 = miao1 + (float)atof(col2[ne1]);
	printf("Miao3 : %f \n",miao3);
	snprintf(time3.miao,9,"%f",miao3);
	printf("time3Miao :%s\n",time3.miao);		


	/* calculer la frequence d'echantillion */
	float freq = 1/(miao3-miao2)*ne1; 
	printf("frequence d'echantillion : %f \n",freq);

	/* calcule UUID */
	//char* getappelsys(char*);
	//char* uuid = getappelsys("uuidgen");

	/* calculer lattitude maximum et le minimum  */
	float latminf = (float)(atof(col15[1]));
	float latmaxf =latmaxf;
	float collat;
	for(i=1;i<ne1;i++){
		collat = (float)(atof(col15[i]));
		if(collat>latmaxf){
			latmaxf= collat;
		}else if(collat<latminf){
			latminf= collat;
		}	
	
	}
	printf("lattitude maximum : %f,lattitude minimum : %f \n",latmaxf,latminf);

	/* calculer la longitude maximum et le minimum  */
	
	float lonminf = (float)(atof(col16[1]));
	float lonmaxf =lonminf;
	for(i=1;i<ne1;i++){
		collat = (float)(atof(col16[i]));
		if(collat>lonmaxf){
			lonmaxf= collat;//printf("lonmaxf %d : %f\n",i,lonmaxf);
		}
		if(collat<lonminf){
			lonminf= collat;//printf("lonminf %d : %f\n",i,lonmaxf);
		}	
	
	}
	printf("longitude maximum : %f,longitude minimum : %f \n",lonmaxf,lonminf);

	/**************** definition those variables ***************/
	char description[100] = "one time test";
	//char* uuid = cuuid();
	char uuid[50] = "c6fad940-5413-4c59-a98d-7ff4855301b4";
	//char name[70] = namey;//"kailognav_Wed_Jun_12_14h57min01sec_2013";
	char latmin[20] ;//= "47.454";
	char lonmin[20] ;//= "-0.587";
	char latmax[20] ;//= "47.460";
	char lonmax[20] ;
	//char timebegin[50] = "2013-06-12T14:57:01.0";
	//char timeend[50] = "2013-06-12T15:13:02.0";
	char updatetime[50] = "2013-06-12T15:13:02.0";
	char procedureuri[100] = "http://www.flakey.org/register/process/scales34.xml#platform_number";
	char fichiercsv[150] = "file:///home/isi-projets/sensorNanny/data/vaimos/nav/kailognav_Wed_Jun_12_14h57min01sec_2013.csv";
	snprintf(latmin,9,"%f",latminf);
	snprintf(latmax,9,"%f",latmaxf);
	snprintf(lonmin,9,"%f",lonminf);
	snprintf(lonmax,9,"%f",lonmaxf);
	
	char* timebegin;char *timeend;
	char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao);
	char* ny="-";char* yr="-";char* rs="T";char* sf=":";char* fm=":";
	timebegin =compositeTime(time1.nian,ny,time1.yue,yr,time1.ri,rs,time1.shi,sf,time1.fen,fm,time2.miao); 
	timeend =compositeTime(time1.nian,ny,time1.yue,yr,time1.ri,rs,time1.shi,sf,time1.fen,fm,time3.miao); 

	printf("\n******** Definition des variable detminee ********************\n");

	/************************************************************/
	/* creat les variables que nous allons utiliser appelé "var2" tableau  */

	char var2[n/2][100];

	Vartab vartab1[15];	//= {{var[0],description},{var[1],description}};
				//printf("\nvar[0] %s \n",var[0]);
	vartab1[0].var1 = variable[0];vartab1[0].var2 = description;
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
	printf("\n*******generate le resulat, lier les phrases et le var2***************\n");
	char resultat[2000]= "";
	printf("\ninitialize Resultat : %s\n",resultat);
	for(vj=0;vj<n+1;vj++){
		if(vj%2 ==1){
			strcat(resultat,vartab1[(vj-1)/2].var2);
		}else{
	       		strcat(resultat,phrase[vj/2]);
		}
	}

	printf("\nResultat : %s\n",resultat);



	/************************************************************/
	/* print and make file .txt or .json  */
	printf("\n*******print and make file .txt or .json***************\n");
	FILE *f = fopen("om2.json","w");
	fprintf(f,resultat);

	fclose(f);
	printf("\n*******Fin du programme***************\n");
	return 1;
}
