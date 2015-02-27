#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

class Region {
public:
	int pX;
	int pY;
	int width;
	int height;
	ImageBase* imIn;
public:

	// 4 regions
	Region(Region** regions) {
		cout << "merge..." << endl;
		this->pX = regions[0]->pX;
		this->pY = regions[0]->pY;
		this->imIn = regions[0]->imIn;
		this->width = regions[0]->width*2;
		this->height = regions[0]->height*2;
		cout << "merge done" << endl;
	}

	Region() {

	}

	Region(ImageBase* imIn) {
		this->width = imIn->getWidth();
		this->height = imIn->getHeight();
		this->pX = 0;
		this->pY = 0;
		this->imIn = imIn;
	}

	Region** divideRegions() {
		cout << "divideRegion..." << endl;
		Region** imgs = new Region*[4];

		for (int i = 0; i < 4; ++i) {
			imgs[i] = new Region();
			imgs[i]->width = this->width / 2;
			imgs[i]->height = this->height / 2;
			imgs[i]->imIn = this->imIn;
		}

		imgs[0]->pX = 0;
		imgs[0]->pY = 0;

		imgs[1]->pX = 0;
		imgs[1]->pY = this->height / 2;

		imgs[2]->pX = this->width / 2;
		imgs[2]->pY = 0;

		imgs[3]->pX = this->width / 2;
		imgs[3]->pY = this->height / 2;

		cout << "divideRegion done	" << endl;

		return imgs;
	}

	int* getAvg() {
		int count = 0;
		int decal = imIn->getColor()?3:1;
		int* avg = new int[decal];
		for (int c = 0; c < decal; c++) {
			avg[c] = 0;
		}

		for (int x = pX; x < pX+this->height; ++x) {
			for (int y = pY; y < pY+this->width; ++y) {
				for (int c = 0; c < decal; c++) {
					avg[c] += (*imIn)[x*decal][y*decal+c];
				}
				count++;
			}
		}

		if (count == 0) {
			cout << "aucun pixel trouvé sur " << pX << ", " << pY << ", " << height << ", " << width << "." << endl;
			exit(0);
		}

		for (int c = 0; c < decal; c++) {
			avg[c] /= count;
		}

		return avg;
	}

	int* getVariance() {
		int count = 1;
		int decal = imIn->getColor()?3:1;
		int* avg = this->getAvg();
		int* variance = new int[decal];
		for (int c = 0; c < decal; c++) {
			variance[c] = 0;
		}

		for (int x = pX; x < pX+this->height; ++x) {
			for (int y = pY; y < pY+this->width; ++y) {
				for (int c = 0; c < decal; c++) {
					int v = avg[c] - (*imIn)[x*decal][y*decal+c];
					variance[c] += v*v;
				}
				count++;
			}
		}

		for (int c = 0; c < decal; c++) {
			variance[c] /= count;
		}

		return variance;
	}

	void colorRegion(int* color) {
		int decal = imIn->getColor()?3:1;
		for (int x = pX; x < pX+this->height; ++x) {
			for (int y = pY; y < pY+this->width; ++y) {
				for (int c = 0; c < decal; c++) {
					(*imIn)[x*decal][y*decal+c] = color[c];
				}
			}
		}
	}

};


Region* goAlgo(Region* r, int n, int seuil) {

	n--;

	Region** divide = r->divideRegions();
	
	for (int i = 0; i < 4; ++i)	{
		int* variance = divide[i]->getVariance();
		if (variance[0] > seuil && divide[i]->width > 2 && n > 0) {
			divide[i] = goAlgo(divide[i], n, seuil);
		}
		else {
			int* avg =  divide[i]->getAvg();
			divide[i]->colorRegion(avg);
		}
	}

	Region* merged = new Region(divide);
	return merged;
}

int main(int argc, char **argv) {

	srand(2);

	if (argc < 4) {
		printf("bad usage\n"); 
		exit(1) ;
	}

	char input[250];
	char output[250];
	int seuil = 50;

	sscanf (argv[1],"%s", input);
	sscanf (argv[2],"%s", output);
	sscanf (argv[3],"%d", &seuil);
	
	ImageBase imIn;
	imIn.load(input);

	Region* r = new Region(&imIn);
	Region* out = goAlgo(r, 10, seuil);
	cout << "end algo" << endl;
	out->imIn->save(output);

	return 0;
}
