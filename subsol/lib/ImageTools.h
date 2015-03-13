#ifndef IMAGETOOLS_PPM
#define IMAGETOOLS_PPM

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "Image.h"
#include "Voxel.h"
#include <Vector>

vector<Triangle> seuillage(Image img, int seuil) {

	vector<Triangle> out;

	for (int i = 0; i < img.sizeX; ++i) {
		for (int j = 0; j < img.sizeY; ++j) {
			for (int k = 0; k < img.sizeZ; ++k) {
				VALUE value = img.getValue(i,j,k);
				Voxel v(i,j,k, value);
				if (value > seuil) {
					Point* adjs = v.getAdj();
					for (int face = 0; face < 6; ++face) {
						Point adj = adjs[face];
						VALUE valueADJ = img.getValue(adj.x,adj.y,adj.z);
						if (valueADJ < seuil) {
							Triangle* triangles = v.getTriangles(face);
							out.push_back(triangles[0]);
							out.push_back(triangles[1]);
						}
					}
				}
			}
		}
	}
	return out;
}

void print(vector<Triangle> tab) {
	for (auto var : tab) {
		cout << var.toString() << endl;
	}
}
#endif

