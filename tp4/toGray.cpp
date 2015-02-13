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
	char output[250];

	sscanf (argv[1],"%s", input) ;
	sscanf (argv[2],"%s", output) ;
	
	ImageBase imIn;
	imIn.load(input);

	ImageBase imG(imIn.getWidth(), imIn.getHeight(), false);

	int decal = imIn.getColor()?3:1;
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			int val = 0;
			for (int c = 0; c < decal; c++) {
				val += imIn[x*decal][y*decal+c];
			}
			imG[x][y] = val/3;
		}
	}

	imG.save(output);

	return 0;
}
