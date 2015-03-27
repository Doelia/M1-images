#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>

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
	if (xB > img.getHeight()-1) xB = img.getHeight()-1;
	if (yB > img.getWidth()-1) yB = img.getWidth()-1;

	v[0].x = xA;
	v[0].y = y;

	v[1].x = xB;
	v[1].y = y;

	v[2].x = x;
	v[2].y = yA;

	v[3].x = x;
	v[3].y = yB;

	//cout << "voison of " << x << "," << y << " = " << v[0].x << "," << v[0].y << endl;
}

void getValuesPixels(ImageBase& img, point pixels[], int values[]) {
	for (int i = 0; i < 4; ++i) {
		int x = pixels[i].x;
		int y = pixels[i].y;
		values[i] = img[x][y];
	}
}

void colorVoisinsIn(ImageBase& img, int x, int y, int color, int canal) {
	int decal = img.getColor()?3:1;
	point voisins[4];
	getVoisins(img, x, y, voisins);
	for (int i = 0; i < 4; i++) {
		int x = voisins[i].x;
		int y = voisins[i].y;
		img[x*decal][y*decal+canal] = color;
	}
}

int getAvgVoisins(ImageBase& img, int x, int y, int seuil) {
	int decal = img.getColor()?3:1;
	point voisins[4];
	getVoisins(img, x, y, voisins);
	int sum = 0;
	int c = 0;
	int cpt = 0;
	for (int i = 0; i < 4; i++) {
		int xV = voisins[i].x;
		int yV = voisins[i].y;
		int val = img[xV*decal][yV*decal+c];
		if (val > seuil) {
			//cout << "val " << val << " at [" << xV << "," << yV << "]" << endl;
			sum += val;
			cpt++;
		}
	}
	if (cpt == 0) {
		return 0;
	}
	//cout << sum << " / " << cpt << " = " <<  (sum/cpt) << endl;
	return sum / cpt;
}

int sumPixelVoisinNoir(ImageBase& in, int seuil) {
	int sum = 0;
	int cpt = 0;

	int decal = in.getColor()?3:1;
	for (int x = 0; x < in.getHeight(); ++x) {
		for (int y = 0; y < in.getWidth(); ++y) {
			for (int c = 0; c < decal; ++c) {
				int value = in[x*decal][y*decal+c];
				if (value < seuil) {
					int avg = getAvgVoisins(in, x,y, seuil);
					if (avg > 0) {
						//cout << " a∑dd " << avg << endl;
						sum += avg;
						cpt++;
					}
					//out[x*decal][y*decal+c] = newValue;
				}
			}
		}
	}

	cout << sum << " / " << cpt << " = " <<  (sum/cpt) << endl;
	return sum / cpt;
}

ImageBase reconstruire_v1(ImageBase& in, int seuil) {

	int avg = sumPixelVoisinNoir(in, seuil);
	cout << "avg = " << avg << endl;

	cout << "Reconstruction..." << endl;
	int decal = in.getColor()?3:1;
	ImageBase out(in.getWidth(), in.getHeight(), in.getColor());
	out.copy(in);
	for (int x = 0; x < in.getHeight(); ++x) {
		for (int y = 0; y < in.getWidth(); ++y) {
			for (int c = 0; c < decal; ++c) {
				int value = in[x*decal][y*decal+c];
				if (value < seuil) {
					int newValue = avg;
					//cout << "set to " << newValue << endl;
					out[x*decal][y*decal+c] = newValue;
				}
			}
		}
	}
	return out;
}

ImageBase reconstruire_v2(ImageBase& in, int seuil) {

	int avg = sumPixelVoisinNoir(in, seuil);
	cout << "avg = " << avg << endl;

	cout << "Reconstruction..." << endl;
	int decal = in.getColor()?3:1;

	bool pixelNoir = true;
	while (pixelNoir) {
		pixelNoir = false;
		for (int x = 0; x < in.getHeight(); ++x) {
			for (int y = 0; y < in.getWidth(); ++y) {
				for (int c = 0; c < decal; ++c) {
					int value = in[x*decal][y*decal+c];
					if (value < seuil) {
						pixelNoir = true;
						int avg = getAvgVoisins(in, x,y, seuil);
						if (avg > 0) {
							int newValue = avg;
							in[x*decal][y*decal+c] = newValue;
						}
					}
				}
			}
		}
	}
	
	
	return in;
}

ImageBase reconstruire_v3(ImageBase& in, int seuil) {

	int avg = sumPixelVoisinNoir(in, seuil);
	cout << "avg = " << avg << endl;

	cout << "Reconstruction..." << endl;
	int decal = in.getColor()?3:1;

	ImageBase out(in.getWidth(), in.getHeight(), in.getColor());
	out.copy(in);

	bool pixelNoir = true;
	int max = 0;
	while (pixelNoir && max < 1000) {
		pixelNoir = false;
		for (int x = 0; x < in.getHeight(); ++x) {
			for (int y = 0; y < in.getWidth(); ++y) {
				for (int c = 0; c < decal; ++c) {
					int value = in[x*decal][y*decal+c];
					if (value < seuil) {
						pixelNoir = true;

						point voisins[4];
						getVoisins(in, x, y, voisins);
						for (int i = 0; i < 4; i++) {
							if (i >= 2)
								out[voisins[i].x][voisins[i].y] = out[voisins[i-2].x][voisins[i-2].y];
						}
					}
				}
			}
		}
		max++;
	}
	
	
	return out;
}



int main(int argc, char **argv) {

	srand(2);

	if (argc < 4) {
		printf("bad usage\n"); 
		exit(1) ;
	}

	char input[250];
	char output[250];
	int seuil = 10;

	sscanf (argv[1],"%s", input);
	sscanf (argv[2],"%s", output);
	sscanf (argv[3],"%d", &seuil);
	
	ImageBase imIn;
	imIn.load(input);

	ImageBase imOut = reconstruire_v3(imIn, seuil);


	imOut.save(output);

	return 0;
}
