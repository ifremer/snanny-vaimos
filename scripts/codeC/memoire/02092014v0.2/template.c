
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "template.h"
#include "ktab.h"


#define Max_LETTRE_FILE 200
#define Max_LENGTH_VAR 50
#define Max_LENGTH_PHRA 500
#define MAX_VARIABLE 30


/************************************************************/
/*lecture d'un template */
char* readtemp(char* f){
		int i; float t;
		char tl[Max_LETTRE_FILE];
		char *templat;


		
		printf("\n\n\n******************* Lecture d'un template*******************\n");
		FILE *tp = fopen(f,"r");

		// calcule et distribuer des espace
		fseek(tp,0,SEEK_END);
		t = ftell(tp);
		i = (int)t+20;
		templat = (char*)malloc(i*sizeof(char));
		printf("max tempalte : %d caracteres\n",i);
		fclose(tp);
		// lecture ligne par ligne ,les concaterer dans template
		FILE *tmpfile = fopen(f,"r");
		while(fgets(tl, Max_LETTRE_FILE, tmpfile) != NULL){
				 strcat(templat,tl);
				 //printf(tl);
		}
		strcat(templat,"\0");
		fclose(tmpfile);
		printf("******************* Fin de lecture ********************\n");
		printf("\nTEMPLATE ===> %s\n",templat);
		//printf("\nTEMPLATE print in function: %s\n",templat);
		return templat;
}

/************************************************************/
/* parcour the template and find the variables       */
int* search_diez(char *template){
		char c;int i,j;
		int* d; 
		
		i=0;j= 0;
		d =  (int*)malloc(MAX_VARIABLE*9*sizeof(int));// admettons que les nbs de diez est inférieur 200 dire que variable inferieur 
		
		
		/* rechercher des diez */
		while(template[i] !='\0'){
			c = template[i];
			if(c=='#'){
			  d[j]= i;
			  //printf("%i\n",i);
			  j++;
			}
			i++;
		};
return d;
}


int* search_3diez(char *template){

		int i,j,n;
		int *var, *diez;

		n=0;
		var= (int*)malloc(MAX_VARIABLE*2*sizeof(int));     // deux fois de variable  !!! attention car chaque variable est signe entre deux diez

		/*rechercher des diez 3 continue*/
		diez= search_diez(template);
		j = count(diez);
		// si on trouve 3 diéz continues , enregirester le premier diez  ;
		for(i=0;i<j-2;){
			if((diez[i]+diez[i+2])/2==diez[i+1]){
				var[n]=diez[i];
				//printf("\n var[]: %i\n",var[n]);
				n++;i=i+3;
				}else
				     i++;
		}
		printf("\nnombre de variables: %i\n",n/2);
		//printf("\nssssssTEMPLATE : %s\n",template);

		/* justifier if ### is pairs */
		if(n%2 == 0){
			printf("text is right ! there is %i # ,donc %i variables.",j,n/2);
		}else{
			printf("text is wrong !there is %i # .",j);
		}

		return var;
	}

/*************************************************/
/* calculer la longueur d'un tableau int       */
int count(int *tab)
{
     int i;

     for (i = 0; tab[i]; i++);

     return (i);
}



/************************************************************/
/* return all variables in original template et afficher*/
char** findvar(char* template,int* var,int j){
	int va, i,nomv, nomj; 
	char** variable;
	char** vp;

	//printf("\nTEMPLATE 1: n");
	variable = creat_tab(MAX_VARIABLE,Max_LENGTH_VAR);	
	va=0;

	//printf("\nTEMPLATE 1: %s\n",template);
	vp = variable;
	for(i = 0; i< j/6;i++){     // nb variable = fois
	
		//printf("\nvariablfffffffffff va: %d;%d ",va,var[21]);
		for(nomj=0,nomv=var[va] ;nomv<=var[va+1]+2;nomv++,nomj++){
			//printf("%c ",template[nomv]);
			//printf("%d %d, ",i,nomj);
		    	vp[i][nomj]= template[nomv];
	
			//printf("\nddddddd %s \n",vp[i]);
		}
		//vp[i][nomj] ='\0';
		printf("variable %i = %s \n",i,vp[i]);
		va=va+2;
	}

	return variable;
}


/* couper template en n/2 +1 morceaux et return all phrase*/
char** findphr(char* template,int* var,int n){
	int vj ,va, nomv ,nomj; 
	char** phrase;
	
	phrase = creat_tab((n/2+1),Max_LENGTH_PHRA);
	va=0;

	for(vj=0;vj<n/2+1;vj++){
		nomj=0;
		if(vj==0){      // first partie
			for(nomv=0 ;nomv< var[va];nomv++,nomj++){
					phrase[vj][nomj]= template[nomv];

		//printf("first partie%i %i template[%c]",nomj,nomv,template2[nomv]);
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
		printf("phrase %i = %s \n",vj,phrase[vj]);
		va=va+2;

	}

return phrase;
}
