#include<stdio.h>
#include "morse.h"
#include<stdlib.h>
#include<string.h>
#include<locale.h>


char *textToMorseCode(char *text){

/*	Because in Morse code max character number is 10(with space) 
	that's why we multiply each character with 10 for to be sure,then for seperating 
	each character we need extra 3 spaces and for seperating words we need 
	extra  5* number of space  and for null character
*/	
	int maxSizeMorseText=10*strlen(text)+3*strlen(text)+5*strlen(text)/2+1;
	char *morseText=(char*)calloc(maxSizeMorseText,sizeof(char));

	for (int i = 0; text[i]; i++)
	{
		char c=text[i];

		//means it is space and another word is coming ,so we need extra 5 space
		if(c==32){
			strcat(morseText,"     "); //put 5 spaces between words 
			continue;
		}
		//means it is +
		else if(c==43) 	strcat(morseText,morseSymbols[1]);
		//means it is :
		else if(c==58)	strcat(morseText,morseSymbols[0]);


		//means it is (0-9)
		else if(c>=48&&c<=57){
			
			int index=c-48; // in morse.h numberCodes starts from 0 index
			char *code=morseNumbers[index];
			strcat(morseText,code);

		}
		//means it is (A-Z or a-z)
		else if((c>=97&&c<=122) || (c>=65&&c<=90)){
			
			int index;
			if(c>=97) index=c-97; //it is small letter (A-Z)
			else index=c-65;	  //it is capital letter (a-z)

			char *code=morseAlphas[index];
			strcat(morseText,code);

		}
		else{
			printf("There is unsupported character for Morse code in the text.Couldn't watermark the image\n");
			exit(1);
		}
		
		if(text[i+1]&&text[i+1]!=32) strcat(morseText,"   "); //put 3 spaces between characters
		
	}
	return morseText;
	
}