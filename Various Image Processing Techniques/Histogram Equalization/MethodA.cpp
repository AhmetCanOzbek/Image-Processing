//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//09.20.2015
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;

#define RED 0
#define GREEN 1
#define BLUE 2

void writeHistDataToFile(int histData[][256]);
int* getTransferFunction(int* arr, int size, int imHeight, int imWidth);
void writeTransferFunctionDataToFile(int** transferFunction);

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

	//Get the histograms of the red, green and blue channels of the original image
	//Initialize histogram data
	int histogramData[3][256];
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<256; i++){
			histogramData[rgb][i] = 0;
		}
	}
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<inputImHeight; i++){
			for(int j=0; j<inputImWidth; j++){
				histogramData[rgb][(inputIm[i][j][rgb])] = histogramData[rgb][(inputIm[i][j][rgb])] + 1;
			}
		}
	}
	//Writing histogram data to file
	writeHistDataToFile(histogramData);

	//Histogram Equalization
	//Calculating transfer functions for each channel rgb (cdf)
	int* transferFunction[3];
	for(int rgb=0; rgb<3; rgb++){		
		transferFunction[rgb] = getTransferFunction(histogramData[rgb], 256, inputImHeight, inputImWidth);	
	}
	//Writing transfer functions to file
	writeTransferFunctionDataToFile(transferFunction);
	
	//Define the output image
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 3;	
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];

	//Apply the transfer functions to corresponding rgb channel and write it to the output image
	int intensityLevel = 0; //0-255
	for(int rgb = 0; rgb<3; rgb++){
		for(int i=0; i<inputImHeight; i++){
			for(int j=0; j<inputImWidth; j++){
				intensityLevel = inputIm[i][j][rgb];
				outIm[i][j][rgb] = transferFunction[rgb][intensityLevel];
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

int* getTransferFunction(int* arr, int size, int imHeight, int imWidth){

	double* cdf = new double[size];
	cdf[0] = arr[0];
	for(int i=1; i<size; i++){
		cdf[i] = cdf[i-1] + arr[i];		
	}
	for(int i=0; i<size; i++){
		cdf[i] = cdf[i] / (imHeight * imWidth);
	}

	int* transferFunction = new int[size];
	for(int i=0; i<size; i++){
		//it is rounded down by putting double variable into int
		transferFunction[i] = (cdf[i] * 255 + 0.5);		
	}

	return transferFunction;
}

void writeTransferFunctionDataToFile(int** transferFunctionData){

	ofstream myfile;
	myfile.open("transferFunctionData.txt");
	for(int rgb = 0; rgb<3; rgb++){
		for(int i=0; i<256; i++){			
			myfile << transferFunctionData[rgb][i] << " ";
		}
		myfile << endl;
	}
	myfile.close();

}

void writeHistDataToFile(int histData[][256]){
	ofstream myfile;
	myfile.open("histData.txt");
	for(int rgb = 0; rgb<3; rgb++){
		for(int i=0; i<256; i++){			
			myfile << histData[rgb][i] << " ";
		}
		myfile << endl;
	}
	myfile.close();
}


