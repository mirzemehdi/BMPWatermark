#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bmp.h"
#include "supportfuncs.h"
#include "morse.h"

/*
 * Read bitmap file header
 */
BITMAPFILEHEADER *ReadBMFileHeader(FILE *fp)
{
    BITMAPFILEHEADER *header;
    char           filetype[3] = {'\0'};
    unsigned short reserved1;
    unsigned short reserved2;

    /* File type (2 bytes) */
    fread(&filetype, 1, 2, fp);

    /* File size (4 bytes) */
    unsigned char buf[4];
    fread(buf, 1, 4, fp);


    unsigned int filesize = byteToInt(buf);
   
    
    /* Reserved 1 (2 bytes) */
    fread(&reserved1, 2, 1, fp);
    
    /* Reserved 2 (2 bytes) */
    fread(&reserved2, 2, 1, fp);

    /* Offset where image starts (4 bytes) */
    fread(buf, 1, 4, fp);
    unsigned int offset =byteToInt(buf);

    header = (BITMAPFILEHEADER *) malloc(sizeof(BITMAPFILEHEADER));
    strcpy(header->bfType, filetype);
    header->bfSize      = filesize;
    header->bfReserved1 = reserved1;
    header->bfReserved2 = reserved2;
    header->bfOffBits   = offset;

    return header;
}




DIBHEADER *ReadDibHeader(FILE *fp){

	DIBHEADER *header;
	unsigned char buf4[4]; //For saving 4 bytes
	unsigned char buf2[2]; //For saving 2 bytes

    /* Header size (4 bytes) */
    fread(buf4, 1, 4, fp);
    unsigned int headersize = byteToInt(buf4);


    /* Width (4 bytes) */
    fread(buf4, 1, 4, fp);
    unsigned int width = byteToInt(buf4);

    /* Height (4 bytes) */
    fread(buf4, 1, 4, fp);
    unsigned int height = byteToInt(buf4);

    /* Planes (2 bytes) */

    fread(buf2, 1, 2, fp);
    unsigned short planes = byteToShort(buf2);

    /* Bit Count (2 bytes) */
    fread(buf2, 1, 2, fp);
    unsigned bitcount = byteToShort(buf2);

    header = (DIBHEADER *) malloc(sizeof(DIBHEADER));
    header->dhSize     = headersize;
    header->dhWidth    = width;
    header->dhHeight   = height;
    header->dhPlanes   = planes;
    header->dhBitPerPixel = bitcount;

    return header;
}

/*
 * Returns size of DIB header
 */
unsigned int SizeOfDIBHeader(FILE *fp)
{
	unsigned char buf[4];
    fread(buf, 1, 4, fp);
    unsigned int headersize=byteToInt(buf);
    fseek(fp, 14, SEEK_SET);
    return headersize;
}


void watermark(char *inputName,char *text,char *date,char *color,int xPos,int yPos,char* outputName){

	FILE *fp;
    BITMAPFILEHEADER *bmFileHeader = NULL;
    DIBHEADER *dibHeader=NULL;
    int dibHeadersize;

	if ((fp = fopen(inputName, "rb")) == NULL) {
        printf("Cannot open file: %s\n", inputName);
        exit(1);
    }
    bmFileHeader = ReadBMFileHeader(fp);
    if (strcmp(bmFileHeader->bfType, "BM") != 0) {
        printf("The file is not BITMAP.\n");
        exit(1);
    }
    dibHeadersize = SizeOfDIBHeader(fp);

    // For checking everything is okay with headers
    //Size of info header is 14
    if(dibHeadersize+14!=bmFileHeader->bfOffBits){
        printf("Header is not correct\n");
        exit(1);
    }
    dibHeader=ReadDibHeader(fp);

    if((xPos>=dibHeader->dhWidth) || (yPos>=dibHeader->dhHeight) ){
        printf("Positions are not inside the image\n");
        exit(1);
    }
    printf("***************************\n");
    printf("File type          = %s\n", bmFileHeader->bfType);
    printf("File size          = %d bytes\n", bmFileHeader->bfSize);
    printf("Data offset        = %d bytes\n", bmFileHeader->bfOffBits);
    
    printf("DibHeader size     = %d bytes\n", dibHeader->dhSize);
    printf("Width              = %d pixels\n", dibHeader->dhWidth);
    printf("Height             = %d pixels\n", dibHeader->dhHeight);
    printf("Planes             = %d\n", dibHeader->dhPlanes);
    printf("Bit count          = %d bits/pixel\n", dibHeader->dhBitPerPixel);
    

    char *finalText=(char*)calloc(400,sizeof(char));
    //We concatenate text and date
	strcat(finalText,text);
    strcat(finalText,date);

    //if there is unsupported character in the text the it will not create new file and exit the program
    // Morse code supports only (A-Z,a-z,0-9 +,:) characters
    char *morseText=textToMorseCode(finalText);

    // Creating new Bitmap file....
    FILE *newBitmap=fopen(outputName,"wb");
    if (newBitmap==NULL)
    {
    	printf("Couldn't create %s  file\n", outputName);
    	exit(1);
    }

    // We create copy of original image ,then modify it
    char *image=(char *)malloc(bmFileHeader->bfSize*sizeof(char)); 
    rewind(fp);
    fread(image,1,bmFileHeader->bfSize,fp);
    fwrite(image,1,bmFileHeader->bfSize,newBitmap);


    int bytePerPixel=dibHeader->dhBitPerPixel/8;

    //Means we should also consider alpha channel
    if (bytePerPixel==4)  strcat(color,"00");
    
    int width=(dibHeader->dhWidth)*bytePerPixel; //Width in bytes
    
	if((width % 4) != 0) width = width + (4 - width % 4); //Means there is padding
		
	// gets offset of the the pixel on the position xPos, yPos	
	int offset = (dibHeader->dhHeight - yPos - 1) * width + xPos * bytePerPixel + bmFileHeader->bfOffBits; 

    fseek(newBitmap, offset, SEEK_SET);

    unsigned char *byteColor=stringToByte(color);
    

    

    
    for (int i = 0; i < strlen(morseText); ++i)
    {
    	char c=morseText[i];
    	// Dot is one pixel,dash is 3 pixel and for space we just keep background color as it is
    	switch(c){

    		case '.':
    		fwrite(byteColor,1,bytePerPixel,newBitmap);
    		break;
    		case '-':
    		fwrite(byteColor,1,bytePerPixel,newBitmap);
    		fwrite(byteColor,1,bytePerPixel,newBitmap);
    		fwrite(byteColor,1,bytePerPixel,newBitmap);
    		break;
    		case ' ':
    		fseek(newBitmap,bytePerPixel,SEEK_CUR);
    		break;
    	}

    }
    printf("\n*******Watermark is successful******\n");
    
    
    fclose(fp);
    fclose(newBitmap);

    //We free all memory which we allocated
    free(bmFileHeader);
    free(dibHeader);
    free(image);
    free(byteColor);
    free(finalText);
    free(morseText);


	

}

