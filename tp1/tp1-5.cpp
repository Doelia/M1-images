#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	//// Parametres
	if (argc < 2) {
		printf("bad usage\n"); 
		exit(1) ;
	}

	char input[250];
	sscanf (argv[1],"%s", input) ;
	
	ImageBase imIn;
	imIn.load(input);

	int colors[3][256];

	for (int c = 0; c < 3; ++c)
	for (int i = 0; i < 255; ++i) {
		colors[c][i] = 0;
	}
	
	for (int x = 0; x < imIn.getWidth(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < 3; ++c)
			{
				int value = imIn[x*3][(y*3)+c];
				colors[c][value]++;
			}
		}
	}

	for (int i = 0; i < 255; ++i) {
		printf("%d %d %d %d\n", i, colors[0][i], colors[1][i], colors[2][i]);
	}


	int divi = 16;
	int nbrValues = 255/divi;
	int colorsRen[3][nbrValues];
	for (int i = 0; i < nbrValues; i++) {
		for (int c = 0; c < 3; ++c) {
			colorsRen[c][i] = 0;
			for (int j = 0; j < divi; ++j) {
				colorsRen[c][i] += colors[c][(i*divi)+j];
			}
		}
	}

	for (int i = 0; i < nbrValues; i++) {
		//printf("%d %d %d %d\n", i, colorsRen[0][i], colorsRen[1][i], colorsRen[2][i]);
	}


	return 0;
}
