#include <stdio.h>
#include <stdlib.h>
//#include <string.h>


#include "ktab.h"


char** creat_tab(int chang,int kuan){
	int i;
	char** variable;
	variable = (char**)malloc(chang * sizeof(char*));       
	for (i = 0; i < chang; i++)
		variable[i] = (char*)malloc( kuan* sizeof(char));

return variable;
}
