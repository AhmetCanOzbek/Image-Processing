//Ahmet Can Ozbek

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#define MathPI 3.14159265359

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int inputImHeight = 256; //Height
	int inputImWidth = 256; //Width
	
	// Check for proper syntax
	if (argc < 3){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name input_image.raw output_image.raw [BytesPerPixel = 1] [InputImageWidth = 256] [InputImageHeight = 256]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 4){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[3]);
		// Check if size is specified
		if (argc >= 5){
			inputImWidth = atoi(argv[4]);
			inputImHeight = atoi(argv[5]);
		}
	}
	
	// Allocate image data array
	unsigned char inputIm[inputImHeight][inputImWidth][BytesPerPixel];

	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[1],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(inputIm, sizeof(unsigned char), inputImHeight*inputImWidth*BytesPerPixel, file);
	fclose(file);

	///////////////////////// PROCESS CODE START /////////////////////////
	
	int outImHeight = 512;
	int outImWidth = 512;
	int outBytesPerPixel = 3;
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];

	//center of the image
	double x0 = (inputImWidth)/2;
	double y0 = (inputImHeight)/2;

	for(int rgb = 0; rgb<3; rgb++){
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){					
				//Going to Cartesian coordinates
				double outX = j - x0;
				double outY = i - y0;

				//Translation
				//Get the angle
				double theta = -(sqrt(outX*outX + outY*outY) / 500) * MathPI;

				//Translate, see the corresponding location in input image in Cartesian Coordinates
				double inX = outX*cos(theta) + outY*sin(theta);
				double inY = outX*(-sin(theta)) + outY*cos(theta);

				//Convert to image coordinates
				int inI = (int) (inY + x0);
				int inJ = (int) (inX + y0);

				//Modifying the output image (Swirling)
				if((inI >= 0 && inI < inputImHeight) && inJ >= 0 && inJ < inputImWidth){
					outIm[i][j][rgb] =  inputIm[inI][inJ][rgb];
				}
			}
		}
	}

	cout << "End." << endl;
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
