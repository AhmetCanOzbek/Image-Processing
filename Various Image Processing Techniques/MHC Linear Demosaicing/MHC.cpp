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

unsigned char** padWithZeros(unsigned char** arr, int height, int width, int padAmount);
double calculatePixelValue(unsigned char** paddedInputIm2d, int paddedInputImHeight, int paddedInputImWidth, int rgb, int i, int j);
double getPixelValue(double filterCoeffs[][5], unsigned char**paddedInputIm2d, int pi, int pj);

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
	
	//allocating memory for 2d array (I need to convert 3d greyscale image to 2d to use my padding function)
	unsigned char** inputIm2d = (unsigned char** ) malloc(inputImHeight * sizeof(unsigned char*));
	for(int i=0; i<inputImHeight; i++){
		inputIm2d[i] = (unsigned char* ) malloc(inputImWidth * sizeof(unsigned char*));
	}

	//put the image data into 2d inputIm2d array
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputIm2d[i][j] = inputIm[i][j][0];
		}
	}

	//allocate memory for padded version of input
	int padAmount = 2;
	int paddedInputImHeight = inputImHeight + padAmount*2;
	int paddedInputImWidth = inputImWidth + padAmount*2;
	unsigned char** paddedInputIm2d = (unsigned char** ) malloc(paddedInputImHeight * sizeof(unsigned char*));
	for(int i=0; i<inputImHeight; i++){
		paddedInputIm2d[i] = (unsigned char* ) malloc(paddedInputImWidth * sizeof(unsigned char*));
	}
	//pad the input image with zeros
	paddedInputIm2d = padWithZeros(inputIm2d, inputImHeight, inputImWidth, padAmount);


	//Defining output image 
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 3;
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];	

	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<inputImHeight; i++){
			for(int j=0; j<inputImWidth; j++){
				outIm[i][j][rgb] = calculatePixelValue(paddedInputIm2d, paddedInputImHeight, paddedInputImWidth, rgb, i+padAmount, j+padAmount);
				//cout<<"Value at (" << i << "," << j << "): " << outIm[i][j][rgb] << endl; 
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

double calculatePixelValue(unsigned char** paddedInputIm2d, int paddedInputImHeight, int paddedInputImWidth, int rgb, int i, int j){

	double sum;

	double G_at_R[5][5] = {{0,0,-1,0,0},{0,0,2,0,0},{-1,2,4,2,-1},{0,0,2,0,0},{0,0,-1,0,0}};
	double G_at_B[5][5] = {{0,0,-1,0,0},{0,0,2,0,0},{-1,2,4,2,-1},{0,0,2,0,0},{0,0,-1,0,0}};
	double R_at_G_Rrow[5][5] = {{0,0,0.5,0,0},{0,-1,0,-1,0},{-1,4,5,4,-1},{0,-1,0,-1,0},{0,0,0.5,0,0}};
	double R_at_G_Rcol[5][5] = {{0,0,-1,0,0},{0,-1,4,-1,0},{0.5,0,5,0,0.5},{0,-1,4,-1,0},{0,0,-1,0,0}};
	double R_at_B[5][5] = {{0,0,-1.5,0,0},{0,2,0,2,0},{-1.5,0,6,0,-1.5},{0,2,0,2,0},{0,0,-1.5,0,0}};	
	double B_at_G_Brow[5][5] = {{0,0,0.5,0,0},{0,-1,0,-1,0},{-1,4,5,4,-1},{0,-1,0,-1,0},{0,0,0.5,0,0}};	
	double B_at_G_Bcol[5][5] = {{0,0,-1,0,0},{0,-1,4,-1,0},{0.5,0,5,0,0.5},{0,-1,4,-1,0},{0,0,-1,0,0}};	
	double B_at_R[5][5] = {{0,0,-1.5,0,0},{0,2,0,2,0},{-1.5,0,6,0,-1.5},{0,2,0,2,0},{0,0,-1.5,0,0}};

	//calculate RED values
	if(rgb == RED){
		//at 0 (red)
		if((i%2==0) && (j%2==0)){
			return paddedInputIm2d[i][j];
		}
		//at 1 (green)
		if((i%2==0) && (j%2==1)){
			return getPixelValue(R_at_G_Rrow, paddedInputIm2d, i, j);
		}
		//at 2 (green)
		if((i%2==1) && (j%2==0)){
			return getPixelValue(R_at_G_Rcol, paddedInputIm2d, i, j);
		}
		//at 3 (blue)
		if((i%2==1) && (j%2==1)){
			return getPixelValue(R_at_B, paddedInputIm2d, i, j);
		}		
	}
	//calculate GREEN values
	if(rgb == GREEN){
		//at 0 (red)
		if((i%2==0) && (j%2==0)){
			return getPixelValue(G_at_R, paddedInputIm2d, i, j);
		}
		//at 1 (green)
		if((i%2==0) && (j%2==1)){
			return paddedInputIm2d[i][j];
		}
		//at 2 (green)
		if((i%2==1) && (j%2==0)){
			return paddedInputIm2d[i][j];
		}
		//at 3 (blue)
		if((i%2==1) && (j%2==1)){
			return getPixelValue(G_at_B, paddedInputIm2d, i, j);
		}			
	}
	//calculate BLUE value
	if(rgb == BLUE){
		//at 0 (red)
		if((i%2==0) && (j%2==0)){
			return getPixelValue(B_at_R, paddedInputIm2d, i, j);
		}
		//at 1 (green)
		if((i%2==0) && (j%2==1)){
			return getPixelValue(B_at_G_Bcol, paddedInputIm2d, i, j);
		}
		//at 2 (green)
		if((i%2==1) && (j%2==0)){
			return getPixelValue(B_at_G_Brow, paddedInputIm2d, i, j);
		}
		//at 3 (blue)
		if((i%2==1) && (j%2==1)){
			return paddedInputIm2d[i][j];
		}		
	}

	
	return 0;

}

double getPixelValue(double filterCoeffs[][5], unsigned char**paddedInputIm2d, int pi, int pj){

	double sum;
	sum = 0;

	for(int i=-2; i<3; i++){
		for(int j= -2; j<3 ; j++){
			sum = sum + filterCoeffs[i+2][j+2] * paddedInputIm2d[pi+i][pj+j];
		}
	}

	//cout<<"Value at (" << pi << "," << pj << "): " << sum/8 << endl; 

	if(sum < 0){
		return 0;
	}

	if((double)sum/(double)8 > 255){
		return 255;
	}

	return (double)sum/(double)8;

}

unsigned char** padWithZeros(unsigned char** arr, int height, int width, int padAmount){

	int outHeight = height + padAmount * 2;
	int outWidth = width + padAmount * 2;
	//allocating memory
	unsigned char** paddedArray = (unsigned char** ) malloc((outHeight) * sizeof(unsigned char*));	
	for(int i=0; i<outHeight; i++){
		paddedArray[i] = (unsigned char* ) malloc((outWidth) * sizeof(unsigned char));
	}

	//fill with zeros
	for(int i=0; i<outHeight; i++){
		for(int j=0; j<outWidth; j++){
			paddedArray[i][j] = 0;
 		}
	}
	//fill the middle
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			paddedArray[i+padAmount][j+padAmount] = arr[i][j];
		}
	}

	return paddedArray;
}
