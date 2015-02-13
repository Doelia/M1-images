#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

float transform(int val, int a, int b) {
	if (val < a)
		val = a;
	if (val > b)
		val = b;
	int ecart = b - a ;
	float produit = (val-a) * 255.0 / ecart;
	//cout << val << " > " << produit + a << endl;
	return produit;
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

	/*
	int min[3] = {255, 255, 255};
	int max[3] = {0, 0, 0};
	int decal = imIn.getColor()?3:1;

	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int value = imIn[x*decal][y*decal+c];
				if (value < min[c]) {
					min[c] = value;
				}
				if (value > max[c]) {
					max[c] = value;
				}
			}
		}
	}
	//*/

	//*
	int min[3] = {50, 50, 50};
	int max[3] = {175, 175, 175};
	int decal = imIn.getColor()?3:1;
	//*/

	cout << "alpha(r) = " << min[0] << endl;
	cout << "alpha(g) = " << min[1] << endl;
	cout << "alpha(b) = " << min[2] << endl;

	cout << "beta(r) = " << max[0] << endl;
	cout << "beta(g) = " << max[1] << endl;
	cout << "beta(b) = " << max[2] << endl;

	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				imG[x*decal][y*decal+c] = transform(imIn[x*decal][y*decal+c], min[c], max[c]);
			}
		}
	}

	imG.save(output);

	return 0;
}
