#include "../lib/Image.h"
#include "../lib/Voxel.h"
#include "../lib/ImageTools.h"
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
	char whatisit[] = "../ressources/WHATISIT/whatisit.301x324x56.1.1.1.4.img";
	char engine[] = "../ressources/engine/engine.256x256x128.1x1x1.img";
	Image in(256, 256, 128);
	//Image in(301, 324, 56);
	in.load(engine);

	cout << "solid name" << endl;
	vector<Triangle> triangles = seuillage(in, 100);
	print(triangles);
	cout << "endsolid name" << endl;
}


