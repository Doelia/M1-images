#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

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

/*
int integrale(int vals[], int a, int b) {
	int sum = 0;
	for (int i = a; i < b; ++i) {
		sum += vals[i];
	}
	return sum;
}
*/

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

	int** colors = histogramme(imIn);

	for (int i = 0; i < 256; ++i) {
		printf("%d %d %d %d\n", i, colors[0][i], colors[1][i], colors[2][i]);
	}

	float** integrs = repartitionNormalize(imIn, colors);
	for (int i = 0; i < 256; ++i) {
		//printf("%d %f %f %f\n", i, integrs[0][i], integrs[1][i], integrs[2][i]);
	}

	// plot 'repart.txt' using 1:2 with lines, 'repart.txt' using 1:3 with lines, 'repart.txt' using 1:4 with lines
	// plot 'histo.txt' using 1:2 with lines, 'histo.txt' using 1:3 with lines, 'histo.txt' using 1:4 with lines

	return 0;
}

