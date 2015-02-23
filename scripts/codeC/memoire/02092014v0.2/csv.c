

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "csv.h"
#include "ktab.h"

#define Max_LINE_CSV 1600
#define Max_LENGTH_CSV 1000


/********************open fichier csv ************************************/
char** opencsv(char* c){
	int ii;
	char** tab;
	//char tl[n];//char *tl;
	
	tab = creat_tab(Max_LINE_CSV,Max_LENGTH_CSV );
	ii =0;

printf("******************** Lecture du fichier data(.csv) et Construction tableux du donnees*******************\n");
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



/* sous fonction du search_col(char** t,int n)       */
void s_col1(char** t,char** ct ,int i,int j){
	if(t[i][j] == ',');
	else ct[i][j]=t[i][j];
}

/********************searche colone   ************************************/
char** search_col(char** t,int n){
						//!!!!!!! ameliorer cette partie de code, si n est sort du nb collone du t;
						//!!!!!!! pas specialiser le coupe ',', plus intelligent;
// chercher le premier element
	// test la taille du table
	int nl, ne,i,nc,m,j,compte ;	
	char** ct; 
	
	nc=30;// max de caracteres pour une colone
	m=0;
	compte=0;

	ne = count_tab(t);
 	//printf("\nline du tableau  : %d\n",ne);

	nl = strlen(*t);
 	//printf("\nla longeur du tableau : %d\n",nl);
	// allocation d'espace pour ct
	ct = creat_tab(ne,nc);

	//pour premier colone
	if(n==1){				//!!!!!!! faire une fonction 
		for(i=0;i<ne-1;i++){	
			for(j=0;j<nl;j++){
				s_col1(t,ct,i,j);
				//if(t[i][j] == ',') break;//{goto changeline;}		// !!!!!!!! changer 
				//else ct[i][j]=t[i][j];
			}
			//changeline:	
				ct[i][j]='\0';
		 }
		ct[i]="F\0";
	}else{
	// pour non premier colone			//!!!!!!! faire une fonction 
		for(i=0;i<ne;i++){	
			for(j=0;j<nl;){
				if(t[i][j]!=','){ j++;}
				else{
					if(++compte==n-1){
						j++;					
						while(t[i][j]!=','){ct[i][m]=t[i][j];m++;j++;}
						ct[i][m]='\0';
					}else j++;
				    }
				m=0;
			
			}	
			compte=0;
		}
		ct[i]="F\0";

	}
/*	// print ct[]
	for(i=0;i<ne;i++){
		printf("colone %d : %s\n",i,ct[i]);
	}
*/
	return ct;
}



	/************************************************************/
	/* recuperer le nom dans le nom du fichier */

char* findname(char* file){
	int jp, i;
	char* name;

	name = (char*)malloc(100*sizeof(char));

	for(i=0;i<strlen(file);i++){
		if(file[i]!='.'){
			name[i]=file[i];
			//printf("%s\n",name);
		}else {jp =i;break;}
	}
	name[i] = '\0';
	return name;
}
	/* recuperer le point dans le nom du fichier */
int findpoint(char* file){
	int p,i;

	for(i=0;i<strlen(file);i++){
		if(file[i]=='.'){
			p =i;break;
		}
	}

	return p;
}

	/* recuperer le tire dans le nom du fichier */
int* findtire(char *file){
	int i,j;
	int* tire;

	tire = (int*)malloc(10*sizeof(int));  //nombre de tire dans le nom du fichier

	for(i=0,j=0;i<strlen(file);i++){
		if(file[i]=='_') tire[j++]=i;
	}

return tire;
}

struct Time* newtime(){
	struct Time *t;
	t = malloc(sizeof(struct Time));
	t->sec = malloc(9*sizeof(char));
	t->min = malloc(9*sizeof(char));
	t->hour = malloc(9*sizeof(char));
	t->mday = malloc(9*sizeof(char));
	t->mon = malloc(9*sizeof(char));
	t->year = malloc(9*sizeof(char));

return t;
}

struct Time time_demar(int jp,char* file,int* tire){			
	    int i;
	    struct Time *time;
		
	   time = newtime();
	    jp =jp-4;
	    for(i=0;i<4;i++){
		time->year[i]=file[jp++];
	    }
	    time->year[i]='\0';
	    jp=tire[1]+1;

	    for(i=0;i<=2;i++){
		time->mon[i]=file[jp++];
	    }
	    time->mon[i]='\0';	    
	    jp=tire[2]+1;
	    for(i=0;i<2;i++){
		time->mday[i]=file[jp++];
	    }
	    time->mday[i]='\0';
	    jp=tire[3]+1;
	    for(i=0;i<2;i++){
		time->hour[i]=file[jp++];
	    }
	    time->hour[i]='\0';
	    jp=tire[3]+4;
	    for(i=0;i<2;i++){
		time->min[i]=file[jp++];
	    }
	    time->min[i]='\0';
	    jp=tire[3]+9;
	    for(i=0;i<2;i++){
		time->sec[i]=file[jp++];
	    }
	    time->sec[i]='\0';

	//printf("abc\n");
	return *time;
}


struct tm* time_to_int(struct Time time){
	struct tm *info;

	int sec,min,hour,mday,mon,year;
	info = (struct tm*)malloc(sizeof(struct tm));

	sec = (float)atof(time.sec);
	min = (int)atof(time.min);
	hour = (int)atof(time.hour);
	mday = (int)atof(time.mday);
	mon = (int)atof(time.mon);
	year = (int)atof(time.year);

	info->tm_sec = (int)sec;
	info->tm_min = min;
	info->tm_hour = hour+1;
	info->tm_mday = mday;
	info->tm_mon = mon;
	info->tm_year = year-1900;
 	info->tm_isdst = -1;
	
	return info;
}


float find_minlat(char** col){
	int i,n;
	float collat, latminf;

	latminf = (float)(atof(col[10]));
	//printf("flasfffffhhhhhhhhh\n");
	n = count_tab(col);

	for(i=1;i<n-1;i++){
		collat = (float)(atof(col[i]));
		if(collat<latminf&&(latminf-collat)<2){
			latminf= collat;//printf("latminf collone:%d value= %f\n",i,latminf);
		}		
	}

	return latminf;
}

float find_maxlat(char** col){
	int i,n;
	float collat, latmaxf;

	latmaxf = (float)(atof(col[10]));
	n = count_tab(col);
	for(i=1;i<n-1;i++){
		collat = (float)(atof(col[i]));
		if(collat>latmaxf&&(collat-latmaxf)<2){      // corrige des erreur
			latmaxf= collat;//printf("latmaxf collone:%d value= %f\n",i,latmaxf);
		}	
	}

	return latmaxf;
}

float find_minlon(char** col){
	float lonminf, collat;;
	int i,n;	

	lonminf = (float)(atof(col[10]));
	n = count_tab(col);
	for(i=1;i<n-1;i++){
		collat = (float)(atof(col[i]));
		if(collat<lonminf&&(lonminf-collat)<2){
			lonminf= collat;//printf("lonminf collone:%d value= %f\n",i,lonminf);
		}	
	
	}

	return lonminf;
}

float find_maxlon(char** col){
	float lonmaxf,collat;
	int i,ne1;

	lonmaxf = (float)(atof(col[10]));
	//printf("lonmaxf value commence a ligne 10 = %f\n",i,lonmaxf);
	ne1 = count_tab(col);
	for(i=1;i<ne1-1;i++){
		collat = (float)(atof(col[i]));
		if(collat>lonmaxf&&(collat-lonmaxf)<2){
			lonmaxf= collat;//printf("lonmaxf collone:%d value= %f\n",i,lonmaxf);
		}
	}

	return lonmaxf;
}

char* float_to_char(float f){
	char *l;
	
	l = (char*)malloc(9*sizeof(char));

	snprintf(l,9,"%f",f);
return l;
}




