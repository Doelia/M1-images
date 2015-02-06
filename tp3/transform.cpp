#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int transform(int val, int a, int b) {
	int ecart = b - a ;
	int produit = val * 255 / ecart;
	return produit + a;
}

int main(int argc, char **argv)
{
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

	int decal = imIn.getColor()?3:1;
	int min = 255;
	int max = 0;
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int value = imIn[x*decal][y*decal+c];
				if (value < min) {
					min = value;
				}
				if (value > max) {
					max = value;
				}
			}
		}
	}

	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				imG[x*decal][y*decal+c] = transform(imIn[x*decal][y*decal+c], min, max);
			}
		}
	}

	imG.save(output);


	return 0;
}
