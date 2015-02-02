#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {

	cout << "test" << endl;

	if (argc < 4) {
		printf("Usage: image-in.ppm image-out.ppm seuil\n"); 
		exit(1) ;
	}

	char input[250];
	char output[250];
	int seuil;

	sscanf (argv[1],"%s", input) ;
	sscanf (argv[2],"%s", output);
	sscanf (argv[3],"%d", &seuil);
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(input);


	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for (int x = 0; x < imG.getWidth(); ++x) {
		for (int y = 0; y < imG.getHeight(); ++y) {
			if (imIn[x][y] < seuil)
				imG[x][y] = 0;
			else
				imG[x][y] = 255;
		}
	}

	imG.save(output);

}