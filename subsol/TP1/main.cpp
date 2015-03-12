#include "Image.h"
#include <iostream>
#include <algorithm>

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

void testRead() {
	Image in(448,576,72);
	char path[250] = "../ressources/BEAUFIX/beaufix.448x576x72.0.6250x0.6250x1.4.img";
	//char path[250] = "../ressources/BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img";
	in.load(path);
	cout << "minValue = " << in.getMinValue() << endl;
	cout << "maxValue = " << in.getMaxValue() << endl;
	cout << "value = " << in.getValue(200,200,20) << endl;
}

void volumeRendering_MinIP(const char* path, int x, int y, int z) {
	Image in(x,y,z);
	in.load(path);

	Image out(x,y,1);

	for (int i = 0; i < in.sizeX; ++i)
	for (int j = 0; j < in.sizeY; ++j) {
		VALUE minVal = in.getValue(i,j,0);
		for (int k = 0; k < in.sizeZ; ++k) {
			minVal = min(in.getValue(i,j,k), minVal);
		}
		out.setValue(i,j,0,minVal);
	}

	char pathOut[256];
	sprintf(pathOut, "%s_MinIP.raw", path);
	out.write(pathOut);
}

void volumeRendering_MIP(const char* path, int x, int y, int z) {
	Image in(x,y,z);
	in.load(path);

	Image out(x,y,1);

	for (int i = 0; i < in.sizeX; ++i)
	for (int j = 0; j < in.sizeY; ++j) {
		VALUE maxVal = in.getValue(i,j,0);
		for (int k = 0; k < in.sizeZ; ++k) {
			maxVal = max(in.getValue(i,j,k), maxVal);
		}
		out.setValue(i,j,0, maxVal);
	}

	char pathOut[256];
	sprintf(pathOut, "%s_MIP.raw", path);
	out.write(pathOut);
}



void volumeRendering_AIP(const char* path, int x, int y, int z) {
	Image in(x,y,z);
	in.load(path);

	Image out(x,y,1);

	for (int i = 0; i < in.sizeX; ++i)
	for (int j = 0; j < in.sizeY; ++j) {
		unsigned long long val = 0;
		for (int k = 0; k < in.sizeZ; ++k) {
			val += in.getValue(i,j,k);
		}
		//cout << "val = " << val/in.sizeZ << endl;
		out.setValue(i,j,0,val/in.sizeZ);
	}

	char pathOut[256];
	sprintf(pathOut, "%s_AIP.raw", path);
	out.write(pathOut);
}

int main() {

	char engine[] = "../ressources/engine/engine.256x256x128.1x1x1.img";
	char foot[] = "../ressources/FOOT/foot.256x256x256.1.1.1.img";
	char beaufix[] = "../ressources/BEAUFIX/beaufix.448x576x72.0.6250x0.6250x1.4.img";
	char brainix[] = "../ressources/BRAINIX/brainix.256x256x100.0.9375x0.9375x1.5.img";
	char manix[] = "../ressources/MANIX/manixSansIV.512x512x48.0.4570x0.4570x3.0.img";
	char orange[] = "../ressources/ORANGE/orange.256x256x64.0.3906x0.3906x1.0.img";
	char whatisit[] = "../ressources/WHATISIT/whatisit.301x324x56.1.1.1.4.img";


	volumeRendering_AIP(whatisit, 301, 324, 56);	
	volumeRendering_AIP(engine, 256, 256, 128);	
	volumeRendering_AIP(foot, 256, 256, 256);	
	volumeRendering_AIP(beaufix, 448, 576, 72);	
	volumeRendering_AIP(brainix, 256, 256, 100);	
	volumeRendering_AIP(manix, 512, 512, 48);	
	//volumeRendering_AIP(orange, 256, 256, 64);	

	volumeRendering_MIP(engine, 256, 256, 128);	
	volumeRendering_MIP(foot, 256, 256, 256);	
	volumeRendering_MIP(beaufix, 448, 576, 72);	
	volumeRendering_MIP(brainix, 256, 256, 100);	
	volumeRendering_MIP(manix, 512, 512, 48);	
	//volumeRendering_MIP(orange, 256, 256, 64);	
	volumeRendering_MIP(whatisit, 301, 324, 56);	

	volumeRendering_MinIP(engine, 256, 256, 128);	
	volumeRendering_MinIP(foot, 256, 256, 256);	
	volumeRendering_MinIP(beaufix, 448, 576, 72);	
	volumeRendering_MinIP(brainix, 256, 256, 100);	
	volumeRendering_MinIP(manix, 512, 512, 48);	
	//volumeRendering_MinIP(orange, 256, 256, 64);	
	volumeRendering_MinIP(whatisit, 301, 324, 56);
}


