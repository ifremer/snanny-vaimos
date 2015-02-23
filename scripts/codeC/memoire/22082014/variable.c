

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


/************************************************************/
/*lecture d'un template */
char* readtemp(char* f){
		char templatec[5000];
		char tl[300];
		char fin[1] ="\0";  
		char *templat;
		FILE *tmpfile = fopen(f,"r");
		printf("\n************************lecture d'un template***************\n");
		// lecture ligne par ligne ,les concaterer dans template
		while(fgets(tl, 200, tmpfile) != NULL){
				 strcat(templatec,tl);
				 //printf(tl);
		}
		strcat(templatec,fin);
		fclose(tmpfile);
		templat= templatec;
		//printf("\nTEMPLATE print in function: %s\n",templat);
		return templat;
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
	printf("%s\n",res);
	return res;
};


/********************searche colone   ************************************/
char** search_col(char** t,int n){

// chercher le premier element
	// test la taille du table
	int nl=0;	
	while(t[0][nl] !='\0'){
		nl++;		
	}
 		//printf("\nla longeur du tableau : %d\n",nl);
	int ne =0;	
	while(t[ne][0] !='\0'){
		ne++;		
	}
 		//printf("\nl'echantillionage du tableau  : %d\n",ne);
	// allocation d'espace pour ct
	char** ct; 
	int i,nc=30; 
	ct = (char**)malloc(ne * sizeof(char*));
	for (i = 0; i < ne; i++)
		ct[i] = (char*)malloc(nc * sizeof(char));
	// copy les 10 premiers caracteres  
	int m=0;
	int j=0;
	int compte=0;

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


	}
	// print ct[]
	for(i=0;i<ne;i++){
		//printf("colone %d : %s\n",i,ct[i]);
	}
	return ct;
}

/********************open fichier csv ************************************/
char** opencsv(char* c){
	int i=0;int k= 1600,n=600;
	char** tab;
	//char tl[n];//char *tl;

	tab = (char**)malloc(k * sizeof(char*));
	for (i = 0; i < k; i++)
		tab[i] = (char*)malloc(n * sizeof(char));
	FILE *csv=fopen(c,"r");
	int ii=0;
	while(fgets(tab[ii], n, csv) != NULL){
		 //tab[ii] = tl;
		//printf("tab[%d] : %s ",ii,tab[ii]);
		ii++;
	}
	fclose(csv);
//printf("tab[%d] : %s \n",0,tab[0]);
//printf("tab[%d] : %s \n",1,tab[1]);
//printf("tab[%d] : %s \n",2,tab[2]);

return tab;
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
			char* uf;char* p;
			char g='-';
			uf = (char*)malloc(36*sizeof(char));
			p=uf;int i;
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
/*
	char* cuuid(){
		int output[16][8];
		int tab[32][4];
		unsigned char c[16];
		uuid_t p ;
		int i=0;int j;

		uuid_generate(p);


		for(i=0;i<16;i++){
			c[i]=p[i];
			for (j = 0; j < 8; j++) {
			  output[i][j] = (c[i] >> j) & 1;
			 // printf("%d",output[i][j]);
			}
			printf("\n" );
    		
		}
		for(i=0;i<32;i++){
			for(j=0;j<4;j++){
				if(i%2==0)tab[i][j] = output[i/2][j];
				else tab[i][j] = output[(i-1)/2][j+4];
			}
		}

		printf("**********************************************************\n");	
		int de[32];char a[32];

		for(i=0;i<32;i++){
			de[i]  = bintodec(tab[i]);
			a[i] = lettre(de[i]);
			printf("%c",a[i]);
		}
		printf("\n**********************************************************\n");
		char* uuid = uuidformat(a);
		printf("%s",uuid);
		return uuid;
		printf("\n**********************************************************\n");

	}
*/
