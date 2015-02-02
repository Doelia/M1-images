#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

typedef unsigned char OCTET;

/* cf : l'entete d'une image .ppm : P6                   */
/*				       nb_colonnes nb_lignes */
/*    			       max_grey_val          */


void ignorer_commentaires(FILE * f)
{
	unsigned char c;
	while((c=fgetc(f)) == '#')
	while((c=fgetc(f)) != '\n');
	fseek(f, -sizeof(unsigned char), SEEK_CUR);
}

void ecrire_image_ppm(char  nom_image[], OCTET *pt_image, int nb_lignes, int nb_colonnes)
{
	FILE *f_image;
	int taille_image = 3*nb_colonnes * nb_lignes;

	if ((f_image = fopen(nom_image, "wb")) == NULL) {
		printf("\nPas d'acces en ecriture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else {
		fprintf(f_image,"P6\r");
		fprintf(f_image,"%d %d\r255\r", nb_colonnes, nb_lignes) ;

		if( (fwrite((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image))
			!= (size_t)(taille_image))
		{
			printf("\nErreur d'ecriture de l'image %s \n", nom_image);
			exit(EXIT_FAILURE);
		}
		fclose(f_image);
	}
}

void lire_image_ppm(char  nom_image[], OCTET *pt_image, int taille_image)
{
	FILE *f_image;
	int  nb_colonnes, nb_lignes, max_grey_val;
	taille_image = 3 * taille_image;

	if ((f_image = fopen(nom_image, "rb")) == NULL) {
		printf("\nPas d'acces en lecture sur l'image %s \n", nom_image);
		exit(EXIT_FAILURE);
	}
	else {
		fscanf(f_image, "P6 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %d%*c",
	       &nb_colonnes, &nb_lignes, &max_grey_val); /*lecture entete*/
			if ((fread((OCTET*)pt_image, sizeof(OCTET), taille_image, f_image)) !=  (size_t)(taille_image)) {
				printf("\nErreur de lecture de l'image %s \n", nom_image);
				exit(EXIT_FAILURE);
			}
			fclose(f_image);
		}
	}


void get_nbrLinesAndColumns(char path[], int *nb_lignes, int *nb_colonnes)
{
	FILE *f_image;
	int max_grey_val;

	if((f_image = fopen(path, "rb")) == NULL) {
		printf("\nPas d'acces en lecture sur l'image %s \n", path);
		exit(EXIT_FAILURE);
	}
	else {
		fscanf(f_image, "P6 ");
		ignorer_commentaires(f_image);
		fscanf(f_image, "%d %d %d%*c", nb_colonnes, nb_lignes, &max_grey_val);
		fclose(f_image);
	}
}

void allocForImage(OCTET** tab, int size) {
	*tab = (OCTET*) malloc(sizeof(OCTET) * size);
}


int main(int argc, char** argv) {

	//// Parametres
	if (argc < 4) {
		printf("Usage: image-in.ppm image-out.ppm seuil\n"); 
		exit(1) ;
	}

	char input[250];
	char output[250];
	int seuil = 100;

	sscanf (argv[1],"%s", input) ;
	sscanf (argv[2],"%s", output);
	sscanf (argv[3],"%d", &seuil);

	
	///// Entete
	int width = 0;
	int height = 0;
	get_nbrLinesAndColumns(input, &height, &width);
	printf("width=%d, height=%d\n", width, height);
	int totalSize = width * height;

	OCTET* imgOut;
	printf("size = %d\n", totalSize);
	allocForImage(&imgOut, totalSize);

	//lire_image_ppm(input, imgOut, totalSize);
	//ecrire_image_ppm(output, imgOut, height, width);



}