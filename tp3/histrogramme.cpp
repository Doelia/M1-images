#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

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
	for (int i = 0; i < 256; ++i) {
		colors[c][i] = 0;
	}

	int decal = imIn.getColor()?3:1;
	
	cout << imIn.getWidth() << "*" << imIn.getHeight() << endl;
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int value = imIn[x*decal][y*decal+c];
				colors[c][value]++;
			}
		}
	}

	for (int i = 0; i < 256; ++i) {
		printf("%d %d %d %d\n", i, colors[0][i], colors[1][i], colors[2][i]);
	}

	return 0;
}
