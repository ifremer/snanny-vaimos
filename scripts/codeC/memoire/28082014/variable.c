

/*********************************************/	
/* Auteur : KAI PASCAL ZHANG				*/
/* this c file is for generating an file JSON for O&M	*/
/*		begin 	24/07/2014			*/
/*							*/
/*							*/
/*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <uuid/uuid.h>
#include "variable.h"

#define MAX_LENGTH_TEMP 5000
#define MAX_VARIABLE 20
#define Max_LENGTH_VAR 50
#define Max_LENGTH_PHRA 500
#define Max_LINE_CSV 1600
#define Max_LENGTH_CSV 1000
#define Max_LETTRE_FILE 200


/************************************************************/
/*lecture d'un template */
char* readtemp(char* f){
		char templatec[MAX_LENGTH_TEMP];
		char tl[Max_LETTRE_FILE];
		//char fin[1] ="\0";  
		char *templat;

		templat = (char*)malloc(MAX_LENGTH_TEMP*sizeof(char));
		
		printf("******************* Lecture d'un template*******************\n");
		FILE *tmpfile = fopen(f,"r");
		// lecture ligne par ligne ,les concaterer dans template
		while(fgets(tl, Max_LETTRE_FILE, tmpfile) != NULL){
				 strcat(templatec,tl);
				 //printf(tl);
		}
		strcat(templatec,"\0");
		fclose(tmpfile);
		printf("******************* Fin de lecture ********************\n");
		templat= templatec;
		//printf("\nTEMPLATE print in function: %s\n",templat);
		return templat;
}

/************************************************************/
/* parcour the template and find the variables       */
int* search_diez(char *template){
		char c;int i,j;
		int* d; 
		char* pt;

		i=0;j= 0;
		d =  (int*)malloc(MAX_VARIABLE*9*sizeof(int));// admettons que les nbs de diez est inférieur 200 dire que variable inferieur 
		pt = template;

		/* rechercher des diez */
		while(pt[i] !='\0'){
			c = pt[i];
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
		int *var;
		int *diez;
		//int n;

		n=0;
		var= (int*)malloc(MAX_VARIABLE*2*sizeof(int));     // deux fois de variable  !!! attention car chaque variable est signe entre deux diez

		/*rechercher des diez 3 continue*/
		diez= search_diez(template);
		j = count(diez);
		// si on trouve 3 diéz continues , enregirester le premier diez
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
		//printf("\noooooooTEMPLATE 1 : %s\n",template1);

		/* justifier if ### is pairs */
		if(n%2 == 0){
			printf("text is right ! there is %i # ,donc %i variables.",j,n/2);
		}else{
			printf("text is wrong !there is %i # .",j);
		}
		return var;
	}

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


	variable = (char**)malloc(MAX_VARIABLE * sizeof(char*));
	for (i = 0; i < MAX_VARIABLE; i++)
		variable[i] = (char*)malloc(Max_LENGTH_VAR * sizeof(char));
	va=0;


	//printf("\nTEMPLATE 1: %s\n",template1);
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
	char** phrase;//[n/2+1][500];
	
	phrase = (char**)malloc((n/2+1)*sizeof(char*));
	for(vj=0;vj<n/2+1;vj++)
		phrase[vj]=(char*)malloc(Max_LENGTH_PHRA*sizeof(char));
	va=0;
	nomv=0;
	nomj=0;

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

/********************open fichier csv ************************************/
char** opencsv(char* c){
	int i, ii;
	char** tab;
	//char tl[n];//char *tl;
	
	tab = (char**)malloc(Max_LINE_CSV * sizeof(char*));
	for (i = 0; i < Max_LINE_CSV; i++)
		tab[i] = (char*)malloc(Max_LENGTH_CSV * sizeof(char));
	ii =0;

printf("******************** Lecture du fichier data(.csv) et Construction tableux du donnees*******************\n");
	FILE *csv=fopen(c,"r");
	while(fgets(tab[ii], Max_LENGTH_CSV, csv) != NULL){
			//printf("tab[%d] : %s ",ii,tab[ii]);
		ii++;
	}
	
	tab[ii]= "F\0";
printf("la dernier ligne est: %d , je definis le contenu: %s\n",ii,tab[ii]);
	fclose(csv);
printf("******************* Fin de Lecture *******************\n");
//printf("tab[%d] : %s \n",0,tab[0]);

return tab;
}

/********************searche colone   ************************************/
char** search_col(char** t,int n){

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
	ct = (char**)malloc(ne * sizeof(char*));
	for (i = 0; i < ne; i++)
		ct[i] = (char*)malloc(nc * sizeof(char));

	//pour premier colone
	if(n==1){
		for(i=0;i<ne-1;i++){	
			for(j=0;j<nl;j++){
				if(t[i][j] == ','){goto changeline;}
				else ct[i][j]=t[i][j];
			}
			changeline:	
				ct[i][j]='\0';
		 }
		ct[i]="F\0";
	}else{
	// pour non premier colone
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

int count_tab(char **tab){
	int n;

	n =0;	

	//printf("tab line 1 : %s\n",tab[1]);
	while(tab[n][0] != 'F'){     // a reflechir
		n++;		
	}
	//printf("\nn : %d \n",n=n-1);

	return n;
}  // c'est faut, ca ne marche pas ; utilise le strlen()

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


struct Time time_demar(int jp,char* file,int* tire){
	    int i;
	    struct Time time;

	    jp =jp-4;
	    for(i=0;i<4;i++){
		time.nian[i]=file[jp++];
	    }
	    time.nian[i]='\0';
	    jp=tire[1]+1;

	    for(i=0;i<=2;i++){
		time.yue[i]=file[jp++];
	    }
	    time.yue[i]='\0';	    
	    jp=tire[2]+1;
	    for(i=0;i<2;i++){
		time.ri[i]=file[jp++];
	    }
	    time.ri[i]='\0';
	    jp=tire[3]+1;
	    for(i=0;i<2;i++){
		time.shi[i]=file[jp++];
	    }
	    time.shi[i]='\0';
	    jp=tire[3]+4;
	    for(i=0;i<2;i++){
		time.fen[i]=file[jp++];
	    }
	    time.fen[i]='\0';
	    jp=tire[3]+9;
	    for(i=0;i<2;i++){
		time.miao[i]=file[jp++];
	    }
	    time.miao[i]='\0';

	return time;
}



int time_to_int(char* time){
	int t;

	t= (int)(time[1]-'0')+(int)(time[0]-'0')*10 ;
	//printf("Miao1 int :%d\n",miao);

	return t;
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


/******************** uuid ************************************/
		int bintodec(int tab[4]){
			int res;

			res = tab[0]*8+tab[1]*4+tab[2]*2+tab[3];	
	
			return res; 
		}
		char lettre(int saisie){
			if(saisie<10) return (char)saisie+48;
			if(saisie>=10&&saisie<16) return (char)saisie+87;
		}
		char* uuidformat(char a[32]){
			char* uf;
			char* p;
			char g;
			int i;

			g='-';
			uf = (char*)malloc(36*sizeof(char));
			p=uf;
			for(i=0;i<8;i++)
				*p++= a[i];
			*p++=g;
			for(i=8;i<12;i++)
				*p++= a[i];
			*p++=g;
			for(i=12;i<16;i++)
				*p++= a[i];
			*p++=g;
			for(i=16;i<20;i++)
				*p++= a[i];
			*p++=g;
			for(i=20;i<32;i++)
				*p++= a[i];
			*p='\0';

			return uf;
		}

char* cuuid(){
		int output[16][8];
		int tab[32][4];
		unsigned char c[16];
		char* uuid;
		uuid_t p ;
		int i,j;
		int de[32];char a[32];

		uuid_generate(p);

		for(i=0;i<16;i++){
			c[i]=p[i];
			for (j = 0; j < 8; j++) {
			  output[i][j] = (c[i] >> j) & 1;
			 // printf("%d",output[i][j]);
			}
			//printf("\n" );    		
		}
		for(i=0;i<32;i++){
			for(j=0;j<4;j++){
				if(i%2==0)tab[i][j] = output[i/2][j];
				else tab[i][j] = output[(i-1)/2][j+4];
			}
		}

		printf("*******************Affichage uuid generé*******************\n");	


		for(i=0;i<32;i++){
			de[i]  = bintodec(tab[i]);
			a[i] = lettre(de[i]);
			printf("%c",a[i]);
		}
		printf("\n****************** UUID en format ***********************\n");
		uuid = uuidformat(a);
		printf(" ###UUID### = %s",uuid);

		printf("\n****************** Fin  ********************************\n");

		return uuid;
	}
/********************composte Time ************************************/
char* compositeTime(char* nian,char*ny,char* yue,char* yr,char* ri,char* rs,char* shi,char* sf,char* fen,char* fm,char* miao){
	int i;
	char *res,*p;

	res = (char*)malloc((strlen(nian) + strlen(ny)+ strlen(yue) + strlen(yr)+ strlen(ri) + strlen(rs)+ strlen(shi) + strlen(sf)+strlen(fen) + strlen(fm) + strlen(miao)) * sizeof(char));
	p = res;

	for (i = 0; i < strlen(nian); i++)
	*p++ = nian[i];
	for (i = 0; i < strlen(ny); i++)
	*p++ = ny[i];
	for (i = 0; i < strlen(yue); i++)
	*p++ = yue[i];
	for (i = 0; i < strlen(yr); i++)
	*p++ = yr[i];
	for (i = 0; i < strlen(ri); i++)
	*p++ = ri[i];
	for (i = 0; i < strlen(rs); i++)
	*p++ = rs[i];
	for (i = 0; i < strlen(shi); i++)
	*p++ = shi[i];
	for (i = 0; i < strlen(sf); i++)
	*p++ = sf[i];
	for (i = 0; i < strlen(fen); i++)
	*p++ = fen[i];
	for (i = 0; i < strlen(fm); i++)
	*p++ = fm[i];
	for (i = 0; i < strlen(miao); i++)
	*p++ = miao[i];
	*p = '\0';
	printf("Composition du temps : %s\n",res);

	return res;
};

	/************************************************************/
	/* generate le resulat, lier les phrases et le var2 */

char* generate_template(Vartab *vartab,char** phrase){
	char* resultat;
	int i, n;

	resultat = (char*)malloc(MAX_LENGTH_TEMP*2*sizeof(char));
 	n = count_Vartab(vartab);

	//resultat= ""; 
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

return resultat;
}

int count_Vartab(Vartab *vartab){
     int i;

     for (i = 0; vartab[i].var1; i++);

     return (i);
}

void writejson(char* resultat){
	FILE *f = fopen("om2.json","w");
	fprintf(f,resultat);
	fclose(f);
}
