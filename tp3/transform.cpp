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
	return produit;
}

float* normaliser(ImageBase &im, int* vals) {
	float size = im.getHeight() * im.getWidth();
	float* out = (float*) malloc(256*sizeof(float));

	for (int i = 0; i < 256; ++i) {
		out[i] = (float) vals[i] / size;
	}
	return out;
}

float* repartition(float* vals) {
	float sum = 0;
	float* out = (float*) malloc(256*sizeof(float));
	for (int i = 0; i < 256; ++i) {
		sum += vals[i];
		out[i] = sum;
	}
	return out;
}

int** histogramme(ImageBase &imIn) {

	int decal = imIn.getColor()?3:1;

	int** colors = (int**) malloc(3*sizeof(int));
	for (int c = 0; c < decal; c++) {
		colors[c] = (int*) malloc(256*sizeof(int));
	}

	for (int c = 0; c < 3; ++c)
	for (int i = 0; i < 256; ++i) {
		colors[c][i] = 0;
	}
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int value = imIn[x*decal][y*decal+c];
				colors[c][value]++;
			}
		}
	}

	return colors;
}

float** repartitionNormalize(ImageBase &im, int** histo) {
	float** out = (float**) malloc(3*sizeof(float));
	for (int c = 0; c < 3; c++) {
		out[c] = (float*) malloc(256*sizeof(float));
	}

	for (int i = 0; i < 3; ++i) {
		out[i] = normaliser(im, histo[i]);
		out[i] = repartition(out[i]);
	}

	return out;
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
	*/

	int min[3] = {20, 20, 20};
	int max[3] = {100, 100, 100};
	int decal = imIn.getColor()?3:1;

	cout << "alpha(r) = " << min[0] << endl;
	cout << "alpha(g) = " << min[1] << endl;
	cout << "alpha(b) = " << min[2] << endl;

	cout << "beta(r) = " << max[0] << endl;
	cout << "beta(g) = " << max[1] << endl;
	cout << "beta(b) = " << max[2] << endl;

	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	float** normalFct = repartitionNormalize(imIn, histogramme(imIn));
	
	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int val = imIn[x*decal][y*decal+c];
				imG[x*decal][y*decal+c] = normalFct[c][val]*val;
			}
		}
	}

	imG.save(output);


	return 0;
}
