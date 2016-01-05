//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//09.20.2015
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

#define RED 0
#define GREEN 1
#define BLUE 2

int tr(int a){
	return a+1;
}


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
	
	//1)Padding the input image by mirror reflections
	//Define a new padded version of the input image
	int paddedInputImHeight = inputImHeight+2;
	int paddedInputImWidth = inputImWidth+2;
	int paddedBytesPerPixel = 1;
	unsigned char paddedInputIm[paddedInputImHeight][paddedInputImWidth][paddedBytesPerPixel];

	//Initializing to zero
	for(int i=0; i<paddedInputImHeight; i++){
		for(int j=0; j<paddedInputImWidth; j++){
			paddedInputIm[i][j][0] = 0;
		}
	}
	//Filling the middle of the padded image
	for(int i=0; i<inputImHeight;i++){
		for(int j=0; j<inputImWidth; j++){
			paddedInputIm[i+1][j+1][0] = inputIm[i][j][0];
		}
	}
	//Mirroring the corners
	paddedInputIm[0][0][0] = inputIm[1][1][1]; //top-left corner
	paddedInputIm[0][paddedInputImWidth-1][0] = inputIm[1][inputImWidth-2][0]; //top-right corner
	paddedInputIm[paddedInputImHeight-1][0][0] = inputIm[inputImHeight-2][1][0]; //bottom-left corner
	paddedInputIm[paddedInputImHeight-1][paddedInputImWidth-1][0] = inputIm[inputImHeight-2][inputImWidth-2][0]; //bottom-right 
	//Mirroring the top and bottom rows (second row in input image becomes the first row in padded image)
	for(int j=0; j<inputImWidth; j++){
		paddedInputIm[0][j+1][0] = inputIm[1][j][0]; //top row
		paddedInputIm[paddedInputImHeight-1][j+1][0] = inputIm[inputImHeight-2][j][0]; //bottom row 
	}
	//Mirroring the left and right columns
	for(int i=0; i<inputImHeight; i++){
		paddedInputIm[i+1][0][0] = inputIm[i][1][0]; //left column
		paddedInputIm[i+1][paddedInputImWidth-1][0] = inputIm[i][inputImWidth-2][0]; //right column
	}


	//Defining output image 
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 3;
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];	

	//2)Constructing the colors
	//In this part, I am going over the image by 2x2 blocks
	
	for(int i=0; i<inputImHeight; i=i+2){
		for(int j=0; j<inputImWidth; j = j+2){
			//at 0 (red pixel->no need to construct red)
			//put red
			outIm[i][j][RED] = paddedInputIm[tr(i)][tr(j)][0];
			//construct green
			outIm[i][j][GREEN] = ((double)1/4) * (paddedInputIm[tr(i)-1][tr(j)][0] + paddedInputIm[tr(i)+1][tr(j)][0] +
										  		  paddedInputIm[tr(i)][tr(j)-1][0] + paddedInputIm[tr(i)][tr(j)+1][0]);
			//construct blue
			outIm[i][j][BLUE] =  ((double)1/4) * (paddedInputIm[tr(i)-1][tr(j)-1][0] + paddedInputIm[tr(i)-1][tr(j)+1][0] + 
										          paddedInputIm[tr(i)+1][tr(j)-1][0] + paddedInputIm[tr(i)+1][tr(j)+1][0]);


			//at 1 (green pixel) -> (construct red and green)
			//put green
			outIm[i][j+1][GREEN] = paddedInputIm[tr(i)][tr(j+1)][0];
			//constructing red
			outIm[i][j+1][RED] =  ((double)1/2) * (paddedInputIm[tr(i)][tr(j+1)-1][0] + paddedInputIm[tr(i)][tr(j+1)+1][0]);
			//constructing blue
			outIm[i][j+1][BLUE] = ((double)1/2) * (paddedInputIm[tr(i)-1][tr(j+1)][0] + paddedInputIm[tr(i)+1][tr(j+1)][0]);


			//at 2 (green pixel) ->(construct red and green)
			//put green
			outIm[i+1][j][GREEN] = paddedInputIm[tr(i+1)][tr(j)][0];
			//constructing blue
			outIm[i+1][j][BLUE] = ((double)1/2) * (paddedInputIm[tr(i+1)][tr(j)-1][0] + paddedInputIm[tr(i+1)][tr(j)+1][0]);
			//constructing red
			outIm[i+1][j][RED] =  ((double)1/2) * (paddedInputIm[tr(i+1)-1][tr(j)][0] + paddedInputIm[tr(i+1)+1][tr(j)][0]);


			//at 3 (blue pixel)
			//put blue
			outIm[i+1][j+1][BLUE] = paddedInputIm[tr(i+1)][tr(j+1)][0];
			//construct green
			outIm[i+1][j+1][GREEN] = ((double)1/4) * (paddedInputIm[tr(i+1)-1][tr(j+1)][0] + paddedInputIm[tr(i+1)+1][tr(j+1)][0] +
										  		      paddedInputIm[tr(i+1)][tr(j+1)-1][0] + paddedInputIm[tr(i+1)][tr(j+1)+1][0]);
			// //construct red
			outIm[i+1][j+1][RED] = ((double)1/4) * (paddedInputIm[tr(i+1)-1][tr(j+1)-1][0] + paddedInputIm[tr(i+1)-1][tr(j+1)+1][0] + 
										            paddedInputIm[tr(i+1)+1][tr(j+1)-1][0] + paddedInputIm[tr(i+1)+1][tr(j+1)+1][0]);

		}
	}

	


    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	//fwrite(inputIm, sizeof(unsigned char), inputImWidth*inputImHeight, file);
	//fwrite(paddedInputIm, sizeof(unsigned char), paddedInputImWidth*paddedInputImHeight, file);
	fwrite(outIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	return 0;
}








