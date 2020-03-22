#include "supportfuncs.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>



char *getDate(){
	char *result = (char *)malloc(100 * sizeof(char));
	FILE * fp = popen("date", "r");
	fgets(result, 100, fp);
	result[strlen(result)-1]='\0';
	pclose(fp);

	return result;
}

unsigned char *intToByte(unsigned int value){

	unsigned char *bytes=(unsigned char *)malloc(4*sizeof(unsigned char));
    memcpy( bytes, &value, sizeof(unsigned int ) );

    return bytes;
}

unsigned int byteToInt(unsigned char *bytes){

	unsigned int result=0;
	for (int i = 3; i >= 0; i--) {
        result = (result << 8) | (unsigned int) bytes[i];
    }
    return result;
}

unsigned short byteToShort(unsigned char *bytes){

	unsigned short result=0;
	for (int i = 1; i >= 0; i--) {
        result = (result << 8) | (unsigned short) bytes[i];
    }
    return result;
}

unsigned char *stringToByte(char* string){

	int byteSize=strlen(string)/2;
    unsigned char *bytes=(unsigned char*)malloc(byteSize*sizeof(unsigned char));
    int n;
    for(int i = 0; i < byteSize; i++) {
        sscanf(string+2*i, "%2X", &n);
        bytes[byteSize-1-i] = (unsigned char)n;  //For changing endiannes of bytes we put to array from end
    }
    
    return bytes;
}

