

#include <stdio.h>
#include <stdlib.h>

int main(void){
	char *file;
	
	float t;
	file = (char *)malloc(20*sizeof(char));
	file = "om2.json";//"templateOMracourci.json";
	FILE *fp;
	fp = fopen(file,"r");
	fseek(fp,0,SEEK_END);
	t = ftell(fp);
	printf("fseek ; %d  \n",(int)t);
	



	fclose(fp);


}
