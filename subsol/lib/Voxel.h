#ifndef IMAGE_PPM
#define IMAGE_PPM

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Image.h"

typedef unsigned short VALUE;

using namespace std;

class Point {
public:
	float x;
	float y;
	float z;

	Point() {
		set(0,0,0);
	}

	Point(float x, float y, float z) {
		set(x,y,z);
	}

	void set(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};

class Voxel {
public:

	Point center;
	float sizeX;
	float sizeY;
	float sizeZ;
	VALUE value;

	Voxel(float x, float y, float z, VALUE value) {
		this->value = value;
		center.set(x,y,z);
		sizeX = 1;
		sizeY = 1;
		sizeZ = 1;
	}

	Point* getSommets() {
		Point* sommets = new Point[8];
		sommets[0].set(center.x -sizeX/2, center.y -sizeY/2, center.z -sizeZ/2);
		sommets[1].set(center.x +sizeX/2, center.y -sizeY/2, center.z -sizeZ/2);
		sommets[2].set(center.x +sizeX/2, center.y +sizeY/2, center.z -sizeZ/2);
		sommets[3].set(center.x -sizeX/2, center.y +sizeY/2, center.z -sizeZ/2);
		sommets[4].set(center.x -sizeX/2, center.y -sizeY/2, center.z +sizeZ/2);
		sommets[5].set(center.x +sizeX/2, center.y -sizeY/2, center.z +sizeZ/2);
		sommets[6].set(center.x +sizeX/2, center.y +sizeY/2, center.z +sizeZ/2);
		sommets[7].set(center.x -sizeX/2, center.y +sizeY/2, center.z +sizeZ/2);
		return sommets;
	}

};

#endif

