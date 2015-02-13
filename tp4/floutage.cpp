#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

struct point {
	int x,y;
};

int getNbrPointsFlou(int n) {
	return (1+n*2) * (1+n*2);
}

point* getVoisins(ImageBase& img, int x, int y, int n) {
	point* v = new point[getNbrPointsFlou(n)];

	int cpt = 0;
	for (int i = -n; i <= n; ++i)
		for (int j = -n; j <= n; ++j)
		{
			int pX = x+i;
			int pY = y+j;
			if (pX < 0) pX = 0;
			if (pX < 0) pY = 0;
			if (pX > img.getWidth()-1) pX = img.getWidth()-1;
			if (pY > img.getHeight()-1) pY = img.getHeight()-1;

			v[cpt].x = pX;
			v[cpt].y = pY;
			cpt++;
		}

	return v;
}

int getAvgValue(ImageBase& img, int x, int y, int c, int sizeFlou) {
	int decal = img.getColor()?3:1;

	point* pts = getVoisins(img, x, y, sizeFlou);
	int val = 0;
	for (int i = 0; i < getNbrPointsFlou(sizeFlou); ++i) {
		int pX = pts[i].x;
		int pY = pts[i].y;
		val += img[pX*decal][pY*decal+c];
	}
	int avg = val/getNbrPointsFlou(sizeFlou);

	return avg;
}


int main(int argc, char **argv)
{
	//// Parametres
	if (argc < 2) {
		printf("bad usage\n"); 
		exit(1) ;
	}

	bool withSeuil = (argc == 4);

	char input[250];
	char output[250];
	sscanf (argv[1],"%s", input) ;
	sscanf (argv[withSeuil?3:2],"%s", output) ;
	ImageBase imIn,imSeuil;
	imIn.load(input);

	if (withSeuil) {
		char input2[250];
		sscanf (argv[2],"%s", input2) ;
		imSeuil.load(input2);
	}

	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	int decal = imIn.getColor()?3:1;
	
	int valSeuil = 0;

	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			if (withSeuil) valSeuil = imSeuil[x][y];
			for (int c = 0; c < decal; c++) {
				int val = imIn[x*decal][y*decal+c];
				if (!withSeuil || valSeuil == 255) {
					imG[x*decal][y*decal+c] = getAvgValue(imIn, x, y, c, 5);
				}
				else {
					imG[x*decal][y*decal+c] = val;
				}
			}
		}
	}

	imG.save(output);

	return 0;
}
