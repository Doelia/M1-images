#include "ImageBase.h"
#include <stdio.h>
#include <iostream>

using namespace std;

struct point {
	int x,y;
};

void getVoisins(ImageBase& img, int x, int y, point v[]) {
	int xA = x-1;
	int yA = y-1;
	int xB = x+1;
	int yB = y+1;
	if (xA < 0) xA = 0;
	if (yA < 0) yA = 0;
	if (xB > img.getWidth()-1) xB = img.getWidth()-1;
	if (yB > img.getHeight()-1) yB = img.getHeight()-1;
	v[0].x = xA;
	v[0].y = yA;
	v[1].x = xA;
	v[1].y = yB;
	v[2].x = xB;
	v[2].y = yA;
	v[3].x = xB;
	v[3].y = yB;
}

void getValuesPixels(ImageBase& img, point pixels[], int values[]) {
	for (int i = 0; i < 4; ++i) {
		int x = pixels[i].x;
		int y = pixels[i].y;
		values[i] = img[x][y];
	}
}

void colorVoisinsIn(ImageBase& img, int x, int y, int color) {
	int nbrVoisins = 0;
	point voisins[4];
	getVoisins(img, x, y, voisins);
	for (int i = 0; i < 4; i++) {
		int x = voisins[i].x;
		int y = voisins[i].y;
		img[x][y] = color;
	}
}


ImageBase eroder(ImageBase& in) {
	ImageBase out(in.getWidth(), in.getHeight(), in.getColor());
	for (int x = 0; x < in.getWidth(); ++x) {
		for (int y = 0; y < in.getHeight(); ++y) {
			if (in[x][y] == 255) {
				colorVoisinsIn(out, x, y, 255);
			}  {
				out[x][y] = in[x][y];
			}
		}
	}
	return out;
}

ImageBase dilater(ImageBase& in) {
	ImageBase out(in.getWidth(), in.getHeight(), in.getColor());
	for (int x = 0; x < in.getWidth(); ++x) {
		for (int y = 0; y < in.getHeight(); ++y) {
			if (in[x][y] == 0) {
				colorVoisinsIn(out, x, y, 0);
			}  {
				out[x][y] = in[x][y];
			}
		}
	}
	return out;
}

ImageBase fermeture(ImageBase& img) {
	ImageBase ero = dilater(img);
	return eroder(ero);
}


ImageBase ouverture(ImageBase& img) {
	ImageBase dilat = eroder(img);
	return dilater(dilat);
}


int main(int argc, char **argv) {

	char input[250];
	char output[250];

	if (argc == 3) {
		sscanf (argv[1],"%s", input) ;
		sscanf (argv[2],"%s", output);
	}
	else if (argc == 2) {
		sscanf (argv[1],"%s", input) ;
		sprintf (output, "out.pgm");
	} else {
		sprintf (input, "out.pgm");
		sprintf (output, "out.pgm");
	}

	ImageBase imIn;
	imIn.load(input);

	/*ImageBase out = ouverture(imIn);
	ImageBase out2 = fermeture(out);
	ImageBase out3 = fermeture(out2);
	ImageBase out4 = ouverture(out3);

	out4.save(output);*/

	ImageBase out = dilater(imIn);
	out.save(output);
}
