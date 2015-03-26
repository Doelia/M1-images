#include "../lib/Image.h"
#include "../lib/Voxel.h"
#include "../lib/ImageTools.h"
#include <iostream>
#include <algorithm>

using namespace std;

void printModel(const char* path, int seuil, int sizeX, int sizeY, int sizeZ) {
	Image in(sizeX, sizeY, sizeZ);
	in.load(path);
	cout << "solid name" << endl;
	vector<Triangle> triangles = seuillage(in, seuil);
	print(triangles);
	cout << "endsolid name" << endl;
}

int main() {
	//printModel("../ressources/BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img", 200, 256, 256, 100);
	printModel("../ressources/MANIX/manixSansIV.512x512x48.0.4570x0.4570x3.0.img", 1250, 512, 512, 48);
	//printModel("../ressources/BEAUFIX/beaufix.448x576x72.0.6250x0.6250x1.4.img", 120, 576, 72, 448);
	//printModel("../ressources/WHATISIT/whatisit.301x324x56.1.1.1.4.img", 50, 301, 324, 56);
	//printModel("../ressources/engine/engine.256x256x128.1x1x1.img", 200, 256, 256, 128);
}
