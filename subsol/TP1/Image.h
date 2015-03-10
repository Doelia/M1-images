#ifndef IMAGE_PPM
#define IMAGE_PPM

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef unsigned short VALUE;

class Image {

private:
	

	VALUE* bin;

	void allocateValues() {
		bin = new VALUE[getSize()];	
	}


	int getSize() {
		return sizeX*sizeY*sizeZ;
	}

	void testValue(int x, int y, int z) {
		if (x > sizeX) {
			printf("L'indice se trouve en dehors des limites de l'image (x %d > %d)\n", x, sizeX);
			exit(0);
		}
		if (y > sizeY) {
			printf("L'indice se trouve en dehors des limites de l'image (y %d > %d)\n", y, sizeY);
			exit(0);
		}
		if (z > sizeZ) {
			printf("L'indice se trouve en dehors des limites de l'image (z %d > %d)\n", z, sizeZ);
			exit(0);
		}
	}

	VALUE convertValue(VALUE v) {
		int x1 = v/256;
		int x2 = v - x1*256;
		return x2*256 + x1;
	}

	VALUE unconvertValue(VALUE v) {
		return convertValue(v);
	}

	int getIndexInTabBin(int x, int y, int z) {
		int v = z*sizeX*sizeY + y*sizeX + x;
		return v;
	}

	VALUE* getVoxel(int x, int y, int z) {
		return &bin[getIndexInTabBin(x,y,z)];
	}

public:
	int sizeX; // Largeur
	int sizeY; // Hateur
	int sizeZ; // Profondeur
	
	Image(int sizeX, int sizeY, int sizeZ) {
		this->sizeX = sizeX;
		this->sizeY = sizeY;
		this->sizeZ = sizeZ;
		this->allocateValues();
	}

	VALUE getValue(int x, int y, int z) {
		return convertValue(*getVoxel(x,y,z));
	}

	void setValue(int x, int y, int z, VALUE val) {
		*getVoxel(x,y,z) = unconvertValue(val);
	}

	VALUE getMinValue() {
		int min = bin[0];
		for (int i = 0; i < getSize(); ++i) {
			int v = this->convertValue(bin[i]);
			if (v < min)
				min = v;
		}
		return min;
	}

	VALUE getMaxValue() {
		int max = bin[0];
		for (int i = 0; i < getSize(); ++i) {
			int v = this->convertValue(bin[i]);
			if (v > max)
				max = v;
		}
		return max;
	}

	void load(char* filename) {
		FILE *f_image;

		if ((f_image = fopen(filename, "rb")) == NULL) {
			printf("\nPas d'acces en lecture sur l'image %s \n", filename);
			exit(EXIT_FAILURE);
		}
		else {
			if (fread((VALUE*)bin, sizeof(VALUE), getSize(), f_image) != (size_t)(getSize())) {
				printf("\nErreur de lecture de l'image %s \n", filename);
				exit(EXIT_FAILURE);
			}
			fclose(f_image);
		}
	}

	void write(char* filename) {
		FILE *f_image;
		if ((f_image = fopen(filename, "wb")) == NULL) {
			printf("\nPas d'acces en ecriture sur l'image %s \n", filename);
			exit(EXIT_FAILURE);
		}
		else {
			if((fwrite((VALUE*)bin, sizeof(VALUE), getSize(), f_image)) != (size_t)(getSize())) {
				printf("\nErreur d'ecriture de l'image %s \n", filename);
				exit(EXIT_FAILURE);
			}
			fclose(f_image);
		}
	}
};

#endif
