#include "Image.h"
#include <iostream>

using namespace std;

void createImage() {
	Image in(256,256,100);
	int cpt = 0;
	int interval = 3000;

	for (int i = 0; i < 256; ++i)
	for (int j = 0; j < 256; ++j)
	for (int k = 0; k < 100; ++k) {
		in.setValue(i,j,k,cpt%interval);
		cpt++;
	}

	char pathOut[256] = "test.img";
	in.write(pathOut);
}

int main() {
	Image in(448,576,72);
	char path[250] = "../ressources/BEAUFIX/beaufix.448x576x72.0.6250x0.6250x1.4.img";
	//char path[250] = "../ressources/BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img";
	in.load(path);
	cout << "minValue = " << in.getMinValue() << endl;
	cout << "maxValue = " << in.getMaxValue() << endl;
	cout << "value = " << in.getValue(200,200,20) << endl;

	createImage();

}
