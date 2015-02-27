#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

// Retoune un tableau de 4 images
ImageBase** divideImage(ImageBase& imIn) {
	ImageBase** imgs = new ImageBase*[4];
	int decal = imIn.getColor()?3:1;

	for (int i = 0; i < 4; ++i) {
		imgs[i] = new ImageBase(imIn.getWidth()/2, imIn.getHeight()/2, imIn.getColor());
	}

	int xOut = 0;
	int yOut = 0;
	for (int x = 0; x < imIn.getWidth()/2; ++x) {
		for (int y = 0; y < imIn.getHeight(); ++y) {
			for (int c = 0; c < decal; c++) {
				int val = imIn[x*decal][y*decal+c];
				(*(imgs[0]))[xOut*decal][yOut*decal+c] = val;
				xOut++;
				if (xOut > imIn.getWidth()/2) {
					xOut = 0;
					yOut++;
				}
			}
		}
	}

	return imgs;
}

void colorImage(ImageBase& imIn, int color[]) {
	int decal = imIn.getColor()?3:1;
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				imIn[x*decal][y*decal+c] = color[c];
			}
		}
	}
}

int main(int argc, char **argv) {

	//// Parametres
	if (argc < 2) {
		printf("bad usage\n"); 
		exit(1) ;
	}

	char input[250];
	char output[250];

	sscanf (argv[1],"%s", input) ;
	sscanf (argv[2],"%s", output) ;
	
	ImageBase imIn;
	imIn.load(input);

	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	int decal = imIn.getColor()?3:1;
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int val = imIn[x*decal][y*decal+c];
				imG[x*decal][y*decal+c] = val;
			}
		}
	}

	imG.save(output);

	return 0;
}
