#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*

// function to generate and return random numbers 
int * getRandom(){
  static int r[10];
  int i;

  // set the seed
  srand( (unsigned)time( NULL ) );
  for ( i = 0; i < 10; ++i)
  {
     r[i] = rand();
     printf( "r[%d] = %d\n", i, r[i]);

  }

  return r;
}

int count(void *tab)
{
      int i;

     for (i = 0; tab[i]; i++)
            ;
     return (i);
}
int main(){
	int* a ;
	a=getRandom();

	printf("\nlength of a:  %d \n",count(a));





return 0;
}
*/


int main(){
	char** variable;//par default 50 variables//variable[n/2][20];
 //	char template[10][10];
//	template[0][0] = "0";
	char *v = "abcdefg";int i;
	for(i=0;i<3;i++){
		variable[0][i]= v[i];
	}
	printf("\ndddddddddddddddddddddddddddddd %s\n",variable[0]);	

return 0;

}

