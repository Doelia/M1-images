#include "../lib/Image.h"
#include "../lib/Voxel.h"
#include "../lib/ImageTools.h"
#include <iostream>
#include <algorithm>

using namespace std;


int main() {
	char whatisit[] = "../ressources/WHATISIT/whatisit.301x324x56.1.1.1.4.img";
	Image in(301, 324, 56);
	in.load(whatisit);

	cout << "solid name" << endl;
	vector<Triangle> triangles = seuillage(in, 50);
	print(triangles);
	cout << "endsolid name" << endl;
}


