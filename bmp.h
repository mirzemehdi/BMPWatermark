#ifndef __BITMAPH__
#define __BITMAPH__
typedef struct BITMAPFILEHEADER {
    char           bfType[3];    /* 2 bytes + null char */
    unsigned int   bfSize;       /* 4 bytes */
    unsigned short bfReserved1;  /* 2 bytes */
    unsigned short bfReserved2;  /* 2 bytes */
    unsigned int  bfOffBits;    /* 4 bytes */
} BITMAPFILEHEADER;


typedef struct DIBHEADER {
    unsigned int   dhSize;          /* 4 bytes */
    unsigned int   dhWidth;         /* 4 bytes */
    unsigned int   dhHeight;        /* 4 bytes */
    unsigned short dhPlanes;        /* 2 bytes */
    unsigned short dhBitPerPixel;   /* 2 bytes */
} DIBHEADER;



BITMAPFILEHEADER *ReadBMFileHeader(FILE *fp);
DIBHEADER *ReadDibHeader(FILE *fp);


unsigned int SizeOfDIBHeader(FILE *fp);
void watermark(char *inputName,char *text,char *date,char *color,int xPos,int yPos,char* outputName);

#endif