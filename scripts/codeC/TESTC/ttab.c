#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "/usr/bin/uuid/uuid.h"
#include <uuid/uuid.h>
/*#include <atlstr.h>
CString ConvertGUIDToText (GUID x)
{
CString C;
C.Format(_T("%08x-%04x-%04x-%02x%02x-%02x%02x%02x%02x%02x%02x"),
x.Data1,
x.Data2,
x.Data3,
x.Data4[0],
x.Data4[1],
x.Data4[2],
x.Data4[3],
x.Data4[4],
x.Data4[5],
x.Data4[6],
x.Data4[7]);
return C;
}
*/
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

	char* cuuid(){
		int output[16][8];
		int tab[32][4];
		unsigned char c[16];
		
		uuid_t p ;
		uuid_generate(p);

		int i=0;int j;
		for(i=0;i<16;i++){
		c[i]=p[i];
		for (j = 0; j < 8; j++) {
		  output[i][j] = (c[i] >> j) & 1;
		  printf("%d",output[i][j]);
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


 main(void)
{


	char*a = cuuid();



	//int tab[4]={1,0,0,1};
	//
	//printf("\n%x\n",de );

	//char a = lettre(1);

	//printf tableu
/*
		for(i=0;i<16;i++){
			for(j=0;j<8;j++){
				printf("%d",output[i][j]);
			}
			printf("\n");
		}
*/
/*				
		for(i=0;i<32;i++){
			for(j=0;j<4;j++){				
				printf("%d",tab[i][j]);
			}
			de[i]  = bintodec(tab[i]);
			printf("\n");
		}
*/	


/*	int i;int k= 1600,n=600;
	char** tab;
	char tl[n];//char *tl;


	tab = (char**)malloc(k * sizeof(char*));
	for (i = 0; i < k; i++)
		tab[i] = (char*)malloc(n * sizeof(char));
	FILE *csv=fopen("mycsv.csv","r");
	i=0;
	while(fgets(tl, n, csv) != NULL){
		tab[i] = tl;
		printf("tab[%d] : %s \n",i,tab[i]);
		i++;
	}
	for(i=0;fgets(tl, n, csv) != NULL;i++){
		tab[i] = tl;
		printf("tab[%d] : %s \n",i,tab[i]);
	}
//tab[1]="zhangkai";
//printf("tab[%d] : %s \n",1,tab[160]);
printf("tdddddddd[%d] : %s \n",1,tab[0]);
	for(i=0;i<100;i++){
		printf("%c",tab[3][i]);
}
	fclose(csv);

printf("tab[i] : %s \n",tab[1]);

*/
/* test fonction** */
/*char* choisetab(char**,int);

	int k=10, n=8,i;
	char **tabc;
 	char* ctab;	
	tabc = (char**)malloc(k * sizeof(char*));
	for (i = 0; i < k; i++)
		tabc[i] = (char*)malloc(n * sizeof(char));
	for(i=0;i<k;i++)
		tabc[i]="zhangkai";
	ctab = choisetab(tabc,1);
	printf("\ntabc[0] : %s \n",tabc[0]);		
	
	printf("\nctab : %s\n",ctab);

	//for (i = 0; i < k; i++)
	//	free(tabc[i]);
	//free(tabc);

*/

/**** test pointeur du pointeur : tableau
	int k=10, n=4,i;
	int **tab;
	tab = (int**)malloc(k * sizeof(int*));
	for (i = 0; i < k; i++)
		tab[i] = (int*)malloc(n * sizeof(int));
	tab[0][0]=2;	
	printf("\n%d\n",tab[0][0]);
	printf("\n%d\n",tab[0][1]);
	for (i = 0; i < k; i++)
		free(tab[i]);
	free(tab);

	//int k=10, n=4,i;
	char **tabc;
	tabc = (char**)malloc(k * sizeof(char*));
	for (i = 0; i < k; i++)
		tabc[i] = (char*)malloc(n * sizeof(char));
	tabc[0][0]='k';tabc[0][1]='z';		
	printf("\n%c\n",tabc[0][0]);
	printf("\n%s length of tabc[0]: %d\n",tabc[0],strlen(tabc[0]));
	for (i = 0; i < k; i++)
		free(tabc[i]);
	free(tabc);
**/



/*
char tab[] = "exemple";
union champbits a;//= {10,32};
a.a =0;
a.b = 'c';
//a = {1,32};

{
enum booleen {faux, vrai};
enum booleen b;
b = vrai;
printf("b = %d\n",b);
}
printf("Nombre de caracteres du tableau = %d   %c  %d \n",a.a,a.b, sizeof(union champbits)); 

int i;float m;
long int j;

i =3;
m =4.4444; 
j =m;
printf("sizeof(&i):%d, m:%f ,&m: %x ,sizeof(&m):%d\n",sizeof(&i),m,&m,sizeof(&m));

float ii,jj;
ii= 45.11;
jj= ii;
printf("sizeof(ii)%d,sizeof(&ii):%d,&ii : %o, &jj : %o\n",sizeof(ii),sizeof(&ii),&ii,&jj);

printf("sizeof(ii)%d,sizeof(&ii):%d,&ii : %d, &ii-1: %d &jj : %d\n",sizeof(ii),sizeof(&ii),&ii,&ii-1,&jj);

int *p;
int *f;
f = p +8;
printf("f: %o, p : %o ,(f-p):%d\n",f,p,(f-p)/sizeof(int));

printf("***********************************\n");

p = malloc(sizeof(int));
printf("p: %o, p :  \n",p);

char* tab1="zhang kai tong yun jing";
char* ptab;
for(ptab= tab1;ptab<= tab1+10; ptab++)
	printf("%c ",*ptab);
printf("\n%s\n",tab1);
*/
/*
int i;
char *chaine1, *chaine2, *res, *p;
chaine1 = "chaine ";
chaine2 = "de caracteres";
char *chaine3 = "chaine3";
res = (char*)malloc((strlen(chaine1) + strlen(chaine2)) * sizeof(char));
p = res;
printf("length chaine1: %d\n",strlen(chaine1));
printf("length chaine3: %d\n",strlen(chaine3));
for(i = 0; i < strlen(chaine1); i++)
	printf("%c",chaine3[i]);

printf("\nsizeof(chaine3[2]) : %d sizeof(chaine3): %d\n",sizeof(chaine3[2]),sizeof(chaine3));

for (i = 0; i < strlen(chaine1); i++)
  *p++ = chaine1[i];
for (i = 0; i < strlen(chaine2); i++)
   *p++ = chaine2[i];
*p='\0';
printf("%s\n",res);
*/



 }



