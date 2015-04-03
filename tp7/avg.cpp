#include "ImageBase.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <vector>

using namespace std;


int main(int argc, char **argv) {

	char input[250];

	sscanf (argv[1],"%s", input);
	
	ImageBase imIn;
	imIn.load(input);

	cout << imIn.getAvg() << endl;
	
	return 0;
}


