
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "find.h"



	/************************************************************/
	/* recuperer le nom sans slash dans le nom du fichier */

char* findnamess(char* file){
	int jp, i,pslash;
	char* name;

	name = (char*)malloc(100*sizeof(char));


	pslash = findslash( file);
	for(i=pslash+1,jp=0;i<strlen(file);i++,jp++){
			name[jp]=file[i];
	}
	name[jp] = '\0';
/*

name = "7lognav_Thu_Aug_23_15h27min02sec_2012.csv";*/
printf("findnamess    :%s\n",name);
	return name;
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
int findpoint( char* file){
	int p,i;

	for(i=0;i<strlen(file);i++){
		if(file[i]=='.'){
			p =i;break;
		}
	}

	return p;
}
///home/isi-projets/sensorNanny/dev/vaimos/vaimoskai/codeC/0lognav_Thu_Aug_23_15h27min02sec_2012.csv
	/* recuperer le dernier slash dans le nom du fichier */
int findslash( char* file){
	int i,j;
	int* p;
	
	p = (int*)malloc(20*sizeof(int)); // maximun 20 slash dans un fichier

	for(i=0,j=0;i<strlen(file);i++){
		if(file[i]=='/'){
			p[j] =i;
		printf("p[%d] %d ",j,p[j]);
		j++;
		}
	
	}
	j--;
printf("p[j--] %d ",p[j]);
	return p[j];
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

