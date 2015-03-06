#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
#include <time.h>

using namespace std;

int* getAvg(ImageBase& imIn) {
	int count = 0;
	int decal = imIn.getColor()?3:1;
	int* avg = new int[decal];
	for (int c = 0; c < decal; c++) {
		avg[c] = 0;
	}

	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				avg[c] += imIn[x*decal][y*decal+c];
			}
			count++;
		}
	}

	for (int c = 0; c < decal; c++) {
		avg[c] /= count;
	}

	return avg;
}

int* getVariance(ImageBase& imIn) {
	int count = 0;
	int decal = imIn.getColor()?3:1;
	int* avg = getAvg(imIn);
	int* variance = new int[decal];

	for (int c = 0; c < decal; c++) {
		variance[c] = 0;
	}

	for (int x = 0; x < imIn.getHeight(); ++x) {
		for (int y = 0; y < imIn.getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				int v = avg[c] - imIn[x*decal][y*decal+c];
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


ImageBase* cropImage(ImageBase& imIn, int xBase, int yBase) {
	ImageBase* imgs = new ImageBase(imIn.getWidth()/2, imIn.getHeight()/2, imIn.getColor());
	int newWidth = imIn.getWidth()/2;
	int newHeight = imIn.getHeight()/2;
	int decal = imIn.getColor()?3:1;

	int xOut = 0;
	int yOut = 0;
	for (int x = xBase; x < newWidth+xBase; ++x) {
		for (int y = yBase; y < newHeight+yBase; ++y) {
			for (int c = 0; c < decal; c++) {
				int val = imIn[x*decal][y*decal+c];
				(*(imgs))[xOut*decal][yOut*decal+c] = val;
			}
			yOut++;
			if (yOut >= newWidth) {
				yOut = 0;
				xOut++;
			}
		}
	}

	return imgs;
}

ImageBase* mergeImage(ImageBase* images[4]) {
	int newWidth = images[0]->getWidth()*2;
	int newHeight = images[0]->getHeight()*2;
	int decal = images[0]->getColor()?3:1;
	ImageBase* img = new ImageBase(newWidth, newHeight, images[0]->getColor());

	for (int x = 0; x < newWidth; ++x) {
		for (int y = 0; y < newHeight; ++y) {
			for (int c = 0; c < decal; c++) {

				ImageBase* imIn;
				int xOut = x;
				int yOut = y;

				if (x < newWidth/2) {
					if (y < newHeight/2) {
						imIn = images[0];
					}
					else {
						yOut = y - newHeight/2;
						imIn = images[1];
					}
				} else {
					xOut = x - newWidth/2;
					if (y < newHeight/2)
						imIn = images[2];
					else {
						yOut = y - newHeight/2;
						imIn = images[3];
					}
				}


				int val = (*imIn)[xOut*decal][yOut*decal+c];
				(*(img))[x*decal][y*decal+c] = val;
			}
		}
	}

	return img;
}

// Retoune un tableau de 4 images
ImageBase** divideImage(ImageBase& imIn) {
	ImageBase** imgs = new ImageBase*[4];

	imgs[0] = cropImage(imIn, 0, 0);
	imgs[1] = cropImage(imIn, 0, imIn.getHeight()/2);
	imgs[2] = cropImage(imIn, imIn.getWidth()/2, 0);
	imgs[3] = cropImage(imIn, imIn.getWidth()/2, imIn.getHeight()/2);

	return imgs;
}

void colorImage(ImageBase* imIn, int color[]) {
	int decal = imIn->getColor()?3:1;
	for (int x = 0; x < imIn->getHeight(); ++x) {
		for (int y = 0; y < imIn->getWidth(); ++y) {
			for (int c = 0; c < decal; c++) {
				(*imIn)[x*decal][y*decal+c] = color[c];
			}
		}
	}
}

ImageBase* goAlgo(ImageBase* imIn, int n, int seuil) {

	n--;

	ImageBase** divide = divideImage(*imIn);
	
	for (int i = 0; i < 4; ++i)	{
		char out[256];
		sprintf(out, "imgs/%d_%d_%d.ppm", n, i, rand());
		
		ImageBase* im = divide[i];
		int* variance = getVariance(*(divide[i]));
		if (variance[0] > seuil && im->getWidth() > 2 && n > 0)
			divide[i] = goAlgo(divide[i], n, seuil);
		else {
			int* avg = getAvg(*(divide[i]));
			colorImage(divide[i], avg);
		}
		//divide[i]->save(out);
	}

	ImageBase* merged = mergeImage(divide);
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

	ImageBase* merged = goAlgo(&imIn, 20, seuil);
	merged->save(output);

	return 0;
}
