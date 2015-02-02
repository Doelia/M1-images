#include "ImageBase.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	//// Parametres
	if (argc < 6) {
		printf("Usage: image-in.ppm image-out.ppm s1 s2 s3\n"); 
		exit(1) ;
	}

	char input[250];
	char output[250];
	int s1,s2,s3;

	sscanf (argv[1],"%s", input) ;
	sscanf (argv[2],"%s", output);
	sscanf (argv[3],"%d", &s1);
	sscanf (argv[4],"%d", &s2);
	sscanf (argv[5],"%d", &s3);
	
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(input);


	ImageBase imG(imIn.getWidth(), imIn.getHeight(), imIn.getColor());

	for (int x = 0; x < imG.getWidth(); ++x) {
		for (int y = 0; y < imG.getHeight(); ++y) {
			if (imIn[x][y] < s1)
				imG[x][y] = 0;
			else if (imIn[x][y] < s2)
				imG[x][y] = 128;
			else
				imG[x][y] = 255;
		}
	}

	imG.save(output);




	return 0;
}
