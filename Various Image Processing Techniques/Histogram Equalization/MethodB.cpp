//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//09.20.2015
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Pixel.h"
using namespace std;

#define RED 0
#define GREEN 1
#define BLUE 2

void writeHistDataToFile(int histData[][256]);


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
	
	//Define a pixel pointer array RGB: index 0:RED, index 1:GREEN, index 2:BLUE
	Pixel* inputImPixels[3];
	//Get all pixel information from the image
	for(int rgb=0; rgb<3; rgb++){
		//initialize
		inputImPixels[rgb] = new Pixel[inputImHeight*inputImWidth];
		for(int i=0; i<inputImHeight; i++){
			for(int j=0; j<inputImWidth; j++){
				inputImPixels[rgb][i*inputImHeight + j].setValue(inputIm[i][j][rgb]);
				inputImPixels[rgb][i*inputImHeight + j].setX(j);
				inputImPixels[rgb][i*inputImHeight + j].setY(i);
			}
		}
	}
	//Sort the pixel array according to its value in the image
	for(int rgb=0; rgb<3; rgb++){
		quickSortPixelArray(inputImPixels[rgb], 0, inputImHeight*inputImWidth - 1);		
	}

	//Define the output image
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 3;	
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];

	//Initializing the output image
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<inputImHeight; i++){
			for(int j=0; j<inputImWidth; j++){
				outIm[i][j][rgb] = 0;
			}
		}
	}

	//Creating the output image
	for(int rgb = 0; rgb<3; rgb++){
		for(int level=0; level<256; level++){
			for(int i=0; i<(inputImHeight*inputImWidth)/256; i++){
				int outX = inputImPixels[rgb][level * ((inputImHeight*inputImWidth)/256) + i].getX();
				int outY = inputImPixels[rgb][level * ((inputImHeight*inputImWidth)/256) + i].getY();
				//cout<<"("<<outX<<","<<outY<<"). level= " << level << endl;
				outIm[outY][outX][rgb] = level;				
			}
		}
	}

	//
	//Get the histograms of the red, green and blue channels of the output image
	//Initialize histogram data
	int histogramData[3][256];
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<256; i++){
			histogramData[rgb][i] = 0;
		}
	}
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				histogramData[rgb][(outIm[i][j][rgb])] = histogramData[rgb][(outIm[i][j][rgb])] + 1;
			}
		}
	}
	//Writing histogram data to file
	writeHistDataToFile(histogramData);


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

void writeHistDataToFile(int histData[][256]){
	ofstream myfile;
	myfile.open("histDataOfMethodB.txt");
	for(int rgb = 0; rgb<3; rgb++){
		for(int i=0; i<256; i++){			
			myfile << histData[rgb][i] << " ";
		}
		myfile << endl;
	}
	myfile.close();
}


