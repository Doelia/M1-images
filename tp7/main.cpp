#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>
#include <fstream>
#include <string>
#include "math.h"
#include <stdio.h>

using namespace std;

float* avgs;
int divide = 10;

int getNImagePlusProche(float avg) {
	int best = 0;
	float dif = 100000;
	for (int i = 0; i <= 10000; ++i) {
		float newDiff = fabs(avg - avgs[i]);
		if (newDiff < dif) {
			dif = newDiff;
			best = i;
		}
	}
	return best;
}


class ImageDecomp;

class Region {
public:
	int pX;
	int pY;
	int width;
	int height;
	ImageBase* imIn;
public:

	Region() {

	}

	Region(ImageBase* imIn) {
		this->width = imIn->getWidth();
		this->height = imIn->getHeight();
		this->pX = 0;
		this->pY = 0;
		this->imIn = imIn;
	}

	Region*** divideRegions(int n) {
		//cout << "divideRegion..." << endl;
		Region*** parts = new Region**[n*n];

		int sizeCase = this->width/n;

		for (int i = 0; i < n; ++i) {
			parts[i] = new Region*[n];
			for (int j = 0; j < n; ++j) {
				Region* r = new Region();;
				parts[i][j] = new Region();
				r->width = this->width / n;
				r->height = this->height / n;
				r->imIn = this->imIn;
				r->pX = sizeCase * i;
				r->pY = sizeCase * j;
				parts[i][j] = r;
			}
		}

		//cout << "divideRegion done	" << endl;

		return parts;
	}

	float* getAvg() {
		float count = 0;
		int decal = imIn->getColor()?3:1;
		float* avg = new float[decal];
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

		//cout << "avg[0] = " << avg[0] << endl;

		return avg;
	}


	void colorRegion(float* color) {
		int decal = imIn->getColor()?3:1;
		for (int x = pX; x < pX+this->height; ++x) {
			for (int y = pY; y < pY+this->width; ++y) {
				for (int c = 0; c < decal; c++) {
					(*imIn)[x*decal][y*decal+c] = (int) color[c];
				}
			}
		}
	}

	void putIn(Region*** rs) {
		for (int x = pX; x < pX+this->height; ++x) {
			for (int y = pY; y < pY+this->width; ++y) {
				int i = x - pX;
				int j = y - pY;
				Region* r = rs[i][j];
				float* avg = r->getAvg();
				(*imIn)[x][y] = (int) avg[0];
			}
		}
	}

};

class ImageDecomp {

public:

	int sizeZone;
	int n;
	ImageBase* imIn;
	Region*** regions;

	ImageDecomp(ImageBase* im, int n) {
		Region r(im);
		this->imIn = im;
		this->n = n;
		regions = r.divideRegions(n);
	}

	void setAllCasesToAvg() {
		cout << "setAllCasesToAvg..." << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				Region* r = regions[i][j];
				float* avgs = r->getAvg();
				r->colorRegion(avgs);
			}
		}
		cout << "ok" << endl;
	}

	void mosaik() {
		cout << "mosaik..." << endl;
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				Region* r = regions[i][j];
				float* avgs = r->getAvg();
				float avg = avgs[0];
				int nImage = getNImagePlusProche(avg);
				ImageBase imPetite;
				char buffer[200];
				sprintf(buffer, "imgs/BOWS2OrigEp3/%d.pgm", nImage);
				imPetite.load(buffer);
				ImageDecomp b(&imPetite, divide);
				r->putIn(b.regions);
				//cout << "nImage = " << buffer << endl;
			}
		}
		cout << "ok" << endl;
	}

};


float* getAvgs() {
	cout << "getAvgs..." << endl;
	float* tab = new float[10001];
	int i = 0;
	string mon_fichier = "f.txt";  // je stocke dans la chaîne mon_fichier le nom du fichier à ouvrir
     ifstream fichier(mon_fichier.c_str(), ios::in);
 
        if(fichier)  // si l'ouverture a fonctionné
        {
                string ligne;  // déclaration d'une chaîne qui contiendra la ligne lue
                while(getline(fichier, ligne))  // tant que l'on peut mettre la ligne dans "contenu"
		        {
		                double value = atof(ligne.c_str());
		                tab[i] = value;
		               // cout << "tab " << i << " = " << tab[i] << endl;
		                i++;
		        }
 
                fichier.close();
        }
        else
                cerr << "Impossible d'ouvrir le fichier !" << endl;
 
     return tab;
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

	avgs = getAvgs();
	cout << "avgTest = " << avgs[0] << endl;
	cout << "getNImagePlusProche(100) = " << getNImagePlusProche(100) << endl;

	ImageDecomp d(&imIn, 50);
	d.setAllCasesToAvg();
	d.mosaik();
	ImageBase* imOut = d.imIn; // TODOgg

	imOut->save(output);

	return 0;
}


