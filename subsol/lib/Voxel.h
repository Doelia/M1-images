#ifndef VOXEL_PPM
#define VOXEL_PPM

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
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

	string toString() {
		char s[250];
		sprintf(s, "%f %f %f", x, y, z);
		return s;
	}
};

class Triangle {
public:
	Point p1;
	Point p2;
	Point p3;

	string toString() {
		string s = "facet normal 0 0 0\n";
		s += "outer loop\n";
		s += "vertex "+p1.toString() +"\n";
		s += "vertex "+p2.toString() +"\n";
		s += "vertex "+p3.toString() +"\n";
		s += "endloop\nendfacet";
		return s;
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

	// Numéro de la face de 0 à 5
	Triangle* getTriangles(int nFace) {
		Triangle* triangles = new Triangle[2];
		Point* sommets = getSommets();

		switch (nFace) {
			case 0: // Droite
				triangles[0].p1 = sommets[1];
				triangles[0].p2 = sommets[2];
				triangles[0].p3 = sommets[5];
				triangles[1].p1 = sommets[2];
				triangles[1].p2 = sommets[6];
				triangles[1].p3 = sommets[5];
				break;
			case 1: // Gauche
				triangles[0].p1 = sommets[4];
				triangles[0].p2 = sommets[3];
				triangles[0].p3 = sommets[0];
				triangles[1].p1 = sommets[4];
				triangles[1].p2 = sommets[6];
				triangles[1].p3 = sommets[3];
				break;
			case 2: // Derrière
				triangles[0].p1 = sommets[6];
				triangles[0].p2 = sommets[2];
				triangles[0].p3 = sommets[3];
				triangles[1].p1 = sommets[6];
				triangles[1].p2 = sommets[3];
				triangles[1].p3 = sommets[7];
				break;
			case 3: // Devant
				triangles[0].p1 = sommets[0];
				triangles[0].p2 = sommets[1];
				triangles[0].p3 = sommets[5];
				triangles[1].p1 = sommets[0];
				triangles[1].p2 = sommets[5];
				triangles[1].p3 = sommets[4];
				break;
			case 4: // Haut
				triangles[0].p1 = sommets[4];
				triangles[0].p2 = sommets[5];
				triangles[0].p3 = sommets[6];
				triangles[1].p1 = sommets[6];
				triangles[1].p2 = sommets[7];
				triangles[1].p3 = sommets[4];
				break;
			case 5: // Bas
				triangles[0].p1 = sommets[3];
				triangles[0].p2 = sommets[2];
				triangles[0].p3 = sommets[1];
				triangles[1].p1 = sommets[3];
				triangles[1].p2 = sommets[1];
				triangles[1].p3 = sommets[0];
				break;
		}
		
		return triangles;
	}

	Point* getAdj() {
		Point* voxels = new Point[6];
		voxels[0].set(center.x + 1, center.y, center.z);
		voxels[1].set(center.x - 1, center.y, center.z);
		voxels[2].set(center.x, center.y + 1, center.z);
		voxels[3].set(center.x, center.y - 1, center.z);
		voxels[4].set(center.x, center.y, center.z + 1);
		voxels[5].set(center.x, center.y, center.z - 1);
		return voxels;
	}

};


#endif

