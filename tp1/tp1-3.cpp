#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	//// Parametres
	if (argc < 3) {
		printf("bad usage\n"); 
		exit(1) ;
	}

	char input[250];
	sscanf (argv[1],"%s", input) ;
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(input);


	int isLine = 0;
	int nLineOrColonne = 50;

	if (isLine) {
		for (int x = 0; x < imIn.getWidth(); ++x) {
			printf("%d %d\n", x, imIn[nLineOrColonne][x]);
		}
	} else {
		for (int x = 0; x < imIn.getHeight(); ++x) {
			printf("%d %d\n", x, imIn[x][nLineOrColonne]);
		}
	}
	



	return 0;
}
