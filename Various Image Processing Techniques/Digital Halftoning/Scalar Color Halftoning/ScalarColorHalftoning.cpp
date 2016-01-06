//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.01.2015
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "ErrorDiffusion.h"

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int inputBytesPerPixel;
	int inputImHeight; //Height
	int inputImWidth; //Width
	
	//cout << "program_name input_image.raw output_image.raw [InputBytesPerPixel] [InputImageWidth] [InputImageHeight]" << endl;
	
	inputBytesPerPixel = atoi(argv[3]);
	inputImWidth = atoi(argv[4]);
	inputImHeight = atoi(argv[5]);
		
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
	
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 3; 
	

	//Seperate Each Channel and Convert RGB to CMY
	//Red (C = 1 - r)
	unsigned char outImC[512][512];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outImC[i][j] = inputIm[i][j][0];
			outImC[i][j] = (255 - outImC[i][j]);
		}
	}
	//Green (M = 1 - g)
	unsigned char outImM[512][512];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outImM[i][j] = inputIm[i][j][1];
			outImM[i][j] = (255 - outImM[i][j]);
		}
	}
	//Blue (Y = 1 - b)
	unsigned char outImY[512][512];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outImY[i][j] = inputIm[i][j][2];
			outImY[i][j] = (255 - outImY[i][j]);
		}
	}

	//Error diffuse each CMY channel with Floyd-Steinberg
	errorDiffuse(outImC,512,512,1); //C
	errorDiffuse(outImM,512,512,1); //M
	errorDiffuse(outImY,512,512,1); //Y

	//Convert it back to RGB
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<512; i++){
			for(int j=0; j<512; j++){
				if(rgb == 0){
					outIm[i][j][rgb] = (255 - outImC[i][j]);
				}
				if(rgb == 1){
					outIm[i][j][rgb] = (255 - outImM[i][j]);
				}
				if(rgb == 2){
					outIm[i][j][rgb] = (255 - outImY[i][j]);
				}	
				
			}
		}
	}

    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	
	return 0;
}
