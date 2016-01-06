//Ahmet Can Ozbek

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "ErrorDiffusion.h"

using namespace std;

int tr(int x);

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int inputBytesPerPixel;
	int inputImHeight; //Height
	int inputImWidth; //Width
	
	//cout << "program_name input_image.raw output_image1.raw output_image2.raw output_image3.raw [InputBytesPerPixel] [InputImageWidth] [InputImageHeight]" << endl;
	
	inputBytesPerPixel = atoi(argv[5]);
	inputImWidth = atoi(argv[6]);
	inputImHeight = atoi(argv[7]);
		
	// Allocate image data array
	unsigned char inputIm[inputImHeight][inputImWidth][inputBytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(inputIm, sizeof(unsigned char), inputImHeight*inputImWidth*inputBytesPerPixel, file);
	fclose(file);

	///////////////////////// PROCESS CODE START /////////////////////////
	
	//Output images
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 1;

	//Method 1: Floyd-Steinberg
	//Method 2: JJN
	//Method 3: Stucki 

	//Method 1: Floyd-Steingberg
	unsigned char outImFS[512][512];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outImFS[i][j] = inputIm[i][j][0];
		}
	}	
	errorDiffuse(outImFS,512,512,1);

	//Method 2: JJN
	unsigned char outImJJN[512][512];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outImJJN[i][j] = inputIm[i][j][0];
		}
	}	
	errorDiffuse(outImJJN,512,512,2);

	//Method 3: Stucki
	unsigned char outImStucki[512][512];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outImStucki[i][j] = inputIm[i][j][0];
		}
	}	
	errorDiffuse(outImStucki,512,512,3);
	
    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix
	//Write output file 1
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outImFS, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);
	
	//Write output file 2
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outImJJN, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);
	
	//Write output file 3
	if (!(file=fopen(argv[4],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outImStucki, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	
	return 0;
}

int tr(int x){
	return x+1;
}


