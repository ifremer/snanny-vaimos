#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ktab.h"

/* sous fonction du search_col(char** t,int n, char s)       */
char* s_col1(char* c ,int n , char s){
	int i,j;
	char* t;

	j = 0;
	t  =  (char*)malloc(30*sizeof(char));
if(n==1){
	for(i=0;c[i]!=s;i++)
		t[i]= c[i];
}else {
	for(i=0;i<strlen(c)&&(n>1);i++){
		if(c[i]==s) n--;
	}	
}
do{
	t[j++]=c[i++];
}while(c[i]!=s&&c[i]!='\n');

return t;
}


char** creat_tab(int chang,int kuan){
	int i;
	char** variable;
	variable = (char**)malloc(chang * sizeof(char*));       
	for (i = 0; i < chang; i++)
		variable[i] = (char*)malloc( kuan* sizeof(char));

return variable;
}


void freetab(char **variable, int nbv){
	int i;
	

	for (i = 0; i < nbv; i++){
		free(variable[i]);
	}
	free(variable);	
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
