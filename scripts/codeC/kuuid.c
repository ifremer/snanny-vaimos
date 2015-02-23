

#include <stdio.h>
#include <uuid/uuid.h>
#include <stdlib.h>

#include "kuuid.h"

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
	uf = (char*)malloc(37*sizeof(char));
	p=uf;

	for(i=0;i<8;i++)*p++= a[i];
	*p++=g;
	for(i=8;i<12;i++)*p++= a[i];
	*p++=g;
	for(i=12;i<16;i++)*p++= a[i];
	*p++=g;
	for(i=16;i<20;i++)*p++= a[i];
	*p++=g;
	for(i=20;i<32;i++)*p++= a[i];
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

		uuid = (char*)malloc(150*sizeof(char));
		
		uuid_generate(p);

		for(i=0;i<16;i++){			//!!!!!!! faire une fonction 
			c[i]=p[i];
			for (j = 0; j < 8; j++) {
			  output[i][j] = (c[i] >> j) & 1;
			 // printf("%d",output[i][j]);
			}
			//printf("\n" );    		
		}
		for(i=0;i<32;i++){			//!!!!!!! faire une fonction 
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

		printf("\n****************** Fin  UUID  ***************************\n");

		return uuid;
	}


