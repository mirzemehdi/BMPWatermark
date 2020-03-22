#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"
#include "supportfuncs.h"

int getX(char *positions);
int getY(char *positions);
int main(int argc, char *argv[])
{
    
    char *text=(char *)calloc(100,sizeof(char));
    char *date=(char *)calloc(100,sizeof(char));
    char *color=(char*)malloc(10*sizeof(char));
    char *position=(char*)calloc(10,sizeof(char));
    char *output=(char *)calloc(100,sizeof(char));

    //User  at least should give input name and color
    if (argc <4) {
        printf("Usage: %s\n Give bitmap name and color for watermark\n",argv[0]);
        exit(1);
    }
    for (int i = 2; i < argc; i++)
    {
        
        if (strcmp(argv[i], "-text") == 0) {
            text=argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-date") == 0){
            date = getDate();
            continue;
        }
        if (strcmp(argv[i], "-color") == 0){
            color = argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-pos") == 0){
            position=argv[++i];
            continue;
        }
        if (strcmp(argv[i], "-o") == 0){
            output =argv[++i];
            continue;
        }
    }

    //Positions is seperated with comma so we need take x and y from this position
    int xPos=getX(position);
    int yPos=getY(position);

    if ((strlen(text)==0) && (strlen(date)==0))
    {
        printf("For watermarking please at least give one of date or text options\n");
        exit(1);
    }

    //Means user didn't give -o option
    if (strlen(output)==0)
    {
        printf("Please, give the output name:\n");
        scanf("%s",output);
    }
    //Means user didn't give -color option
    if (strlen(color)==0)
    {
        printf("Please, give the color for watermark:\n");
        scanf("%s",color);
    }


    watermark(argv[1],text,date,color, xPos,yPos,output); //argv[1] is inputName
    
   

    
    
    

    return 0;
}

int getX(char *positions){

    int x=0;
    char pos[10]={'\0'};
    for (int i = 0; i < strlen(positions); ++i)
    {
        if (positions[i]==',') break;
        pos[i]=positions[i];
        
    }


    return atoi(pos);
}

int getY(char *positions){

    char pos[10]={'\0'};
    int i;
    for (i = 0; i < strlen(positions); ++i) {
        if (positions[i]==',') break;
    }
    int j=0;
    for (++i; i < strlen(positions); ++i) pos[j++]=positions[i];

    return atoi(pos);
}
