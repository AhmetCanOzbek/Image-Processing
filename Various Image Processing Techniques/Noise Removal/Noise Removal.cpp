//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//09.20.2015
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include <vector>
using namespace std;

#define RED 0
#define GREEN 1
#define BLUE 2

int** createMedianFilter(int size);
double calculatePSNR(unsigned char cleanIm[][512], unsigned char noisyIm[][512], int imHeight, int imWidth);
double calculatePSNR2(unsigned char cleanIm[][512], unsigned char** noisyIm, int imHeight, int imWidth);
int getMedian(unsigned char** window, int medianFilterPoints);

unsigned char** applyMedianFilter(unsigned char** inputIm, int medianFilterPoints, int imHeight, int imWidth);
unsigned char** applyGaussianFilter(unsigned char** inputIm, int gaussianFilterSize, int imHeight, int imWidth);
unsigned char** applyMeanFilter(unsigned char** inputIm, int meanFilterSize, int imHeight, int imWidth);
double getGaussianPixelValue(unsigned char** window, int gaussianFilterSize);
double getMeanPixelValue(unsigned char** window, int meanFilterSize);



int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int BytesPerPixel;
	int inputImHeight = 256; //Height
	int inputImWidth = 256; //Width
	
	// Check for proper syntax
	if (argc < 4){
		cout << "Syntax Error - Incorrect Parameter Usage:" << endl;
		cout << "program_name inputNoisy_image.raw inputCleanImage.raw output_image.raw\
		[BytesPerPixel = 1] [InputImageWidth = 256] [InputImageHeight = 256] \
		[medianFilterPoints = 5 or 9] [gaussianFilterSize = 3]" << endl;
		return 0;
	}
	
	// Check if image is grayscale or color
	if (argc < 5){
		BytesPerPixel = 1; // default is grey image
	} 
	else {
		BytesPerPixel = atoi(argv[4]);
		// Check if size is specified
		if (argc >= 5){
			inputImWidth = atoi(argv[5]);
			inputImHeight = atoi(argv[6]);
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

	// Allocate image data array for clean image
	unsigned char inputCleanIm[inputImHeight][inputImWidth][BytesPerPixel];
	// Read image (filename specified by first argument) into image data matrix
	if (!(file=fopen(argv[2],"rb"))) {
		cout << "Cannot open file: " << argv[1] <<endl;
		exit(1);
	}
	fread(inputCleanIm, sizeof(unsigned char), inputImHeight*inputImWidth*BytesPerPixel, file);
	fclose(file);



	///////////////////////// PROCESS CODE START /////////////////////////
	
	//Seperate the noisy image into RGB channels
	//RED
	unsigned char inputImR[512][512];	
	//Get data
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputImR[i][j] = inputIm[i][j][RED];
		}
	}
	//Green
	unsigned char inputImG[512][512];
	//Get data
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputImG[i][j] = inputIm[i][j][GREEN];
		}
	}
	//Blue
	unsigned char inputImB[512][512];
	//Get data
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputImB[i][j] = inputIm[i][j][BLUE];
		}
	}
	
	//Seperate the clean image into RGB channels
	//RED
	unsigned char inputCleanImR[512][512];	
	//Get data
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputCleanImR[i][j] = inputCleanIm[i][j][RED];
		}
	}
	//Green
	unsigned char inputCleanImG[512][512];
	//Get data
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputCleanImG[i][j] = inputCleanIm[i][j][GREEN];
		}
	}
	//Blue
	unsigned char inputCleanImB[512][512];
	//Get data
	for(int i=0; i<inputImHeight; i++){
		for(int j=0; j<inputImWidth; j++){
			inputCleanImB[i][j] = inputCleanIm[i][j][BLUE];
		}
	}
	//Seperation into channels end.

	//Write each noisy image channel to file
	//red
	file=fopen("noisyPeppersRed.raw","wb");		
	fwrite(inputImR, sizeof(unsigned char), inputImHeight*inputImWidth, file);
	fclose(file);
	//green
	file=fopen("noisyPeppersGreen.raw","wb");		
	fwrite(inputImG, sizeof(unsigned char), inputImHeight*inputImWidth, file);
	fclose(file);
	//blue
	file=fopen("noisyPeppersBlue.raw","wb");		
	fwrite(inputImB, sizeof(unsigned char), inputImHeight*inputImWidth, file);
	fclose(file);

	//calculate psnr
	cout << "(No Filter) PSNR (RED channel): " << calculatePSNR(inputCleanImR, inputImR, inputImHeight, inputImWidth) << endl;
	cout << "(No Filter) PSNR (GREEN channel): " << calculatePSNR(inputCleanImG, inputImG, inputImHeight, inputImWidth) << endl;
	cout << "(No Filter) PSNR (BLUE channel): " << calculatePSNR(inputCleanImB, inputImB, inputImHeight, inputImWidth) << endl;
	

	//define padded input im and allocate memory
	int intermediateOutRedImHeight = inputImHeight;
	int intermediateOutRedImWidth = inputImWidth;
	unsigned char** intermediateOutRedIm = new unsigned char*[intermediateOutRedImHeight];
	for(int i=0; i<512; i++){intermediateOutRedIm[i] = new unsigned char[intermediateOutRedImWidth];}
	//get Data
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			intermediateOutRedIm[i][j] = inputIm[i][j][RED];
		}
	}
	int intermediateOutGreenImHeight = inputImHeight;
	int intermediateOutGreenImWidth = inputImWidth;
	unsigned char** intermediateOutGreenIm = new unsigned char*[intermediateOutGreenImHeight];
	for(int i=0; i<512; i++){intermediateOutGreenIm[i] = new unsigned char[intermediateOutGreenImWidth];}
	//get Data
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			intermediateOutGreenIm[i][j] = inputIm[i][j][GREEN];
		}
	}
	int intermediateOutBlueImHeight = inputImHeight;
	int intermediateOutBlueImWidth = inputImWidth;
	unsigned char** intermediateOutBlueIm = new unsigned char*[intermediateOutBlueImHeight];
	for(int i=0; i<512; i++){intermediateOutBlueIm[i] = new unsigned char[intermediateOutBlueImWidth];}
	//get Data
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			intermediateOutBlueIm[i][j] = inputIm[i][j][BLUE];
		}
	}


	cout<<endl;
	//use apply median function
	int medianFilterPoints = 21;
	intermediateOutRedIm = applyMedianFilter(intermediateOutRedIm, medianFilterPoints, 512, 512);
	intermediateOutGreenIm = applyMedianFilter(intermediateOutGreenIm, medianFilterPoints, 512, 512);
	intermediateOutBlueIm = applyMedianFilter(intermediateOutBlueIm, medianFilterPoints, 512, 512);
	cout << "After " <<medianFilterPoints<< " point MedianFilter PSNR(red channel): " << calculatePSNR2(inputCleanImR, intermediateOutRedIm, 512, 512) << endl;
	cout << "After " <<medianFilterPoints<< " point MedianFilter PSNR(green channel): " << calculatePSNR2(inputCleanImG, intermediateOutGreenIm, 512, 512) << endl;
	cout << "After " <<medianFilterPoints<< " point MedianFilter PSNR(blue channel): " << calculatePSNR2(inputCleanImB, intermediateOutBlueIm, 512, 512) << endl;
	cout << endl;
	
	//apply gaussian
	int gaussianFilterSize = 5;
	intermediateOutRedIm = applyGaussianFilter(intermediateOutRedIm, gaussianFilterSize, 512, 512);
	intermediateOutGreenIm = applyGaussianFilter(intermediateOutGreenIm, gaussianFilterSize, 512, 512);
	intermediateOutBlueIm = applyGaussianFilter(intermediateOutBlueIm, gaussianFilterSize, 512, 512);
	cout << "After " <<gaussianFilterSize<< " size GaussianFilter PSNR(red channel): "<< calculatePSNR2(inputCleanImR, intermediateOutRedIm, 512, 512) << endl;
	cout << "After " <<gaussianFilterSize<< " size GaussianFilter PSNR(green channel): "<< calculatePSNR2(inputCleanImG, intermediateOutGreenIm, 512, 512) << endl;
	cout << "After " <<gaussianFilterSize<< " size GaussianFilter PSNR(blue channel): "<< calculatePSNR2(inputCleanImB, intermediateOutBlueIm, 512, 512) << endl;
	cout<< endl;
	
	//apply mean
	// int meanFilterSize = 3;
	// intermediateOutRedIm = applyMeanFilter(intermediateOutRedIm, meanFilterSize, 512, 512);
	// intermediateOutGreenIm = applyMeanFilter(intermediateOutGreenIm, meanFilterSize, 512, 512);
	// intermediateOutBlueIm = applyMeanFilter(intermediateOutBlueIm, meanFilterSize, 512, 512);
	// cout << "After " <<meanFilterSize<< " size MeanFilter PSNR(red channel): " << calculatePSNR2(inputCleanImR, intermediateOutRedIm, 512, 512) << endl;
	// cout << "After " <<meanFilterSize<< " size MeanFilter PSNR(green channel): " << calculatePSNR2(inputCleanImG, intermediateOutGreenIm, 512, 512) << endl;
	// cout << "After " <<meanFilterSize<< " size MeanFilter PSNR(blue channel): " << calculatePSNR2(inputCleanImB, intermediateOutBlueIm, 512, 512) << endl;
	// cout << endl;


	//define array to write output
	int outFilteredImHeight = inputImHeight;
	int outFilteredImWidth = inputImWidth;
	int outFilteredBytesPerPixel = 3;	
	unsigned char outFilteredIm[outFilteredImHeight][outFilteredImWidth][outFilteredBytesPerPixel];
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outFilteredIm[i][j][RED] = intermediateOutRedIm[i][j];
		}
	}
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outFilteredIm[i][j][GREEN] = intermediateOutGreenIm[i][j];
		}
	}
	for(int i=0; i<512; i++){
		for(int j=0; j<512; j++){
			outFilteredIm[i][j][BLUE] = intermediateOutBlueIm[i][j];
		}
	}		
	

    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outFilteredIm, sizeof(unsigned char), outFilteredImHeight*outFilteredImWidth*outFilteredBytesPerPixel, file);
	fclose(file);

	return 0;
}

//medianFilterPoints, N=9;
int getMedian(unsigned char** window, int medianFilterPoints){

	int windowHeight = (medianFilterPoints/2) + 1;
	int windowWidth = (medianFilterPoints/2) + 1;

	vector<int> myVector;

	//vertical
	for(int i=0; i<windowHeight; i++){
		myVector.push_back(window[i][windowWidth/2]);
	}
	//horizontal
	for(int j=0; j<windowWidth; j++){
		myVector.push_back(window[windowHeight/2][j]);
	}

	sort(myVector.begin(),myVector.end());

	return myVector[medianFilterPoints/2];
}

unsigned char** applyMeanFilter(unsigned char** inputIm, int meanFilterSize, int imHeight, int imWidth){

	//define padded input im and allocate memory
	int paddedImHeight = imHeight + ((meanFilterSize/2)*2);
	int paddedImWidth = imWidth + ((meanFilterSize/2)*2);
	unsigned char** paddedInputIm = new unsigned char*[paddedImHeight];
	for(int i=0; i<paddedImHeight; i++){
		paddedInputIm[i] = new unsigned char[paddedImWidth];
	}
	//initialize to zeros
	for(int i=0; i<paddedImHeight; i++){
		for(int j=0; j<paddedImWidth; j++){
			paddedInputIm[i][j] = 0;
		}
	}
	//fill in the middle
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			paddedInputIm[i+(meanFilterSize/2)][j+(meanFilterSize/2)] = inputIm[i][j];
		}
	}

	//define output filtered image and allocate memory
	unsigned char** outIm = new unsigned char*[imHeight];
	for(int i=0; i<512; i++){
		outIm[i] = new unsigned char[imWidth];
	}
	//initialize to zeros
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			outIm[i][j] = 0;
		}
	}

	//apply mean filter
	//define the window and allocate memory	
	int windowHeight = meanFilterSize;
	int windowWidth = meanFilterSize;
	unsigned char** window = new unsigned char*[windowHeight];
	for(int i=0; i<windowHeight; i++){
		window[i] = new unsigned char[windowWidth];
	}
	//time to apply mean filter, modify output image
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			//extract the window
			for(int wi=0; wi<windowHeight; wi++){
				for(int wj=0; wj<windowWidth; wj++){
					window[wi][wj] =  paddedInputIm[i+wi][j+wj];
				}
			}
			//put the window into the function and get the calculated mean value
			int meanPixelValue = getMeanPixelValue(window, meanFilterSize);
			//modify output image			
			outIm[i][j] = meanPixelValue;
		}
	}

	return outIm;
}

double getMeanPixelValue(unsigned char** window, int meanFilterSize){

	double sum = 0;
	
	for(int i=0; i<meanFilterSize; i++){
		for(int j=0; j<meanFilterSize; j++){
			sum = sum + (double)window[i][j];
		}
	}
		
	sum = sum / (double)(meanFilterSize*meanFilterSize);
	

	return sum;
}

unsigned char** applyGaussianFilter(unsigned char** inputIm, int gaussianFilterSize, int imHeight, int imWidth){

	//define padded input im and allocate memory
	int paddedImHeight = imHeight + ((gaussianFilterSize/2)*2);
	int paddedImWidth = imWidth + ((gaussianFilterSize/2)*2);
	unsigned char** paddedInputIm = new unsigned char*[paddedImHeight];
	for(int i=0; i<paddedImHeight; i++){
		paddedInputIm[i] = new unsigned char[paddedImWidth];
	}
	//initialize to zeros
	for(int i=0; i<paddedImHeight; i++){
		for(int j=0; j<paddedImWidth; j++){
			paddedInputIm[i][j] = 0;
		}
	}
	//fill in the middle
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			paddedInputIm[i+(gaussianFilterSize/2)][j+(gaussianFilterSize/2)] = inputIm[i][j];
		}
	}

	//define output filtered image and allocate memory
	unsigned char** outIm = new unsigned char*[imHeight];
	for(int i=0; i<512; i++){
		outIm[i] = new unsigned char[imWidth];
	}
	//initialize to zeros
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			outIm[i][j] = 0;
		}
	}

	//apply gaussian filter
	//define the window and allocate memory	
	int windowHeight = gaussianFilterSize;
	int windowWidth = gaussianFilterSize;
	unsigned char** window = new unsigned char*[windowHeight];
	for(int i=0; i<windowHeight; i++){
		window[i] = new unsigned char[windowWidth];
	}
	//time to apply gaussian filter, modify output image
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			//extract the window
			for(int wi=0; wi<windowHeight; wi++){
				for(int wj=0; wj<windowWidth; wj++){
					window[wi][wj] =  paddedInputIm[i+wi][j+wj];
				}
			}
			//put the window into the function and get the calculated gaussian value
			int gaussianPixelValue = getGaussianPixelValue(window, gaussianFilterSize);
			//modify output image			
			outIm[i][j] = gaussianPixelValue;
		}
	}

	return outIm;



}

double getGaussianPixelValue(unsigned char** window, int gaussianFilterSize){

	double gauss3[3][3] = {{0.0113,0.0838,0.0113}, 
						   {0.0838,0.6193,0.0838}, 
						   {0.0113,0.0838,0.0113}};
	
	double gauss5[5][5] = { {(6.9625 * pow(10,-8)), (2.8089 * pow(10,-5)), (2.0755*pow(10,-4)), (2.8089 * pow(10,-5)), (6.9625 * pow(10,-8))} , 
							{(2.8089*pow(10,-5)), (0.0113), (0.0837), (0.0113), (2.8089*pow(10,-5))} , 
							{(2.0755*pow(10,-4)), (0.0837), (0.6187), (0.0837), (2.0755*pow(10,-4))} , 
							{(2.8089*pow(10,-5)), (0.0113), (0.0837), (0.0113), (2.8089*pow(10,-5))} , 
							{(6.9625 * pow(10,-8)), (2.8089 * pow(10,-5)), (2.0755*pow(10,-4)), (2.8089 * pow(10,-5)), (6.9625 * pow(10,-8))} };
	
	double sum = 0;

	if(gaussianFilterSize == 3){
		for(int i=0; i<gaussianFilterSize; i++){
			for(int j=0; j<gaussianFilterSize; j++){
				sum = sum + (double)((double)window[i][j] * (double)gauss3[i][j]);
			}
		}
	}
	if(gaussianFilterSize == 5){
		for(int i=0; i<gaussianFilterSize; i++){
			for(int j=0; j<gaussianFilterSize; j++){
				sum = sum + (double)((double)window[i][j] * (double)gauss5[i][j]);
			}
		}
	}

	return sum;
}

double** getGaussianCoefficients(int gaussianFilterSize){


	double gauss3[3][3] = {{0.0113,0.0838,0.0113}, 
						   {0.0838,0.6193,0.0838}, 
						   {0.0113,0.0838,0.0113}};
	
	double gauss5[5][5] = { {(6.9625 * pow(10,-8)), (2.8089 * pow(10,-5)), (2.0755*pow(10,-4)), (2.8089 * pow(10,-5)), (6.9625 * pow(10,-8))} , 
							{(2.8089*pow(10,-5)), (0.0113), (0.0837), (0.0113), (2.8089*pow(10,-5))} , 
							{(2.0755*pow(10,-4)), (0.0837), (0.6187), (0.0837), (2.0755*pow(10,-4))} , 
							{(2.8089*pow(10,-5)), (0.0113), (0.0837), (0.0113), (2.8089*pow(10,-5))} , 
							{(6.9625 * pow(10,-8)), (2.8089 * pow(10,-5)), (2.0755*pow(10,-4)), (2.8089 * pow(10,-5)), (6.9625 * pow(10,-8))} };

	double** gaussianFilter = new double*[gaussianFilterSize];
	for(int i=0; i<gaussianFilterSize; i++){
		gaussianFilter[i] = new double[gaussianFilterSize];
	}

	if(gaussianFilterSize == 3){
		for(int i=0; i<gaussianFilterSize; i++){
			for(int j=0; j<gaussianFilterSize; j++){
				gaussianFilter[i][j] = gauss3[i][j];
			}
		}

	}

	if(gaussianFilterSize == 5){
		for(int i=0; i<gaussianFilterSize; i++){
			for(int j=0; j<gaussianFilterSize; j++){
				gaussianFilter[i][j] = gauss5[i][j];
			}
		}
	}

	return gaussianFilter;
}

//medianFilterPoints, N=9;
unsigned char** applyMedianFilter(unsigned char** inputIm, int medianFilterPoints, int imHeight, int imWidth){

	//define padded input im and allocate memory
	int paddedImHeight = imHeight + (medianFilterPoints/2);
	int paddedImWidth = imWidth + (medianFilterPoints/2);
	unsigned char** paddedInputIm = new unsigned char*[paddedImHeight];
	for(int i=0; i<paddedImHeight; i++){
		paddedInputIm[i] = new unsigned char[paddedImWidth];
	}
	//initialize to zeros
	for(int i=0; i<paddedImHeight; i++){
		for(int j=0; j<paddedImWidth; j++){
			paddedInputIm[i][j] = 0;
		}
	}
	//fill in the middle
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			paddedInputIm[i+(medianFilterPoints/4)][j+(medianFilterPoints/4)] = inputIm[i][j];
		}
	}


	//define output filtered image and allocate memory
	unsigned char** outIm = new unsigned char*[imHeight];
	for(int i=0; i<512; i++){
		outIm[i] = new unsigned char[imWidth];
	}
	//initialize to zeros
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			outIm[i][j] = 0;
		}
	}
	//apply median filter
	//define the window and allocate memory	
	int windowHeight = (medianFilterPoints/2) + 1;
	int windowWidth = (medianFilterPoints/2) + 1;
	unsigned char** window = new unsigned char*[windowHeight];
	for(int i=0; i<windowHeight; i++){
		window[i] = new unsigned char[windowWidth];
	}
	//time to apply median filter, modify output image
	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){
			//extract the window
			for(int wi=0; wi<windowHeight; wi++){
				for(int wj=0; wj<windowWidth; wj++){
					window[wi][wj] =  paddedInputIm[i+wi][j+wj];
				}
			}
			//put the window into the function and get the median value
			int medianNumber = getMedian(window, medianFilterPoints);
			//modify output image
			outIm[i][j] = medianNumber;
		}
	}

	return outIm;
}

double calculatePSNR2(unsigned char cleanIm[][512], unsigned char** noisyIm, int imHeight, int imWidth){

	double mse = 0; //mean square error

	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){			
			mse = mse + (double) ((double)cleanIm[i][j]-(double)noisyIm[i][j]) * ((double)cleanIm[i][j]-(double)noisyIm[i][j]);
		}
	}

	mse = mse / (imHeight*imWidth);

	double psnr = 0;	
	psnr = 10 * ( log10((255*255)/mse) );
	return psnr;

}



double calculatePSNR(unsigned char cleanIm[][512], unsigned char noisyIm[][512], int imHeight, int imWidth){

	double mse = 0; //mean square error

	for(int i=0; i<imHeight; i++){
		for(int j=0; j<imWidth; j++){			
			mse = mse + (double) ((double)cleanIm[i][j]-(double)noisyIm[i][j]) * ((double)cleanIm[i][j]-(double)noisyIm[i][j]);
		}
	}

	mse = mse / (imHeight*imWidth);

	double psnr = 0;	
	psnr = 10 * ( log10((255*255)/mse) );
	return psnr;
}

//size(N) = 9 , (5x5)
int** createMedianFilter(int size){	
		
	int height = size/2 + 1;
	int width = size/2 + 1;

	int** medianFilter = new int*[height];
	for(int i=0; i<height; i++){
		medianFilter[i] = new int[width];
	}

	//fill with zeros
	for(int i=0; i<height; i++){
		for(int j=0; j<width; j++){
			medianFilter[i][j] = 0;
		}
	}
	//fill vertical with 1s
	for(int i=0; i<height; i++){
		medianFilter[i][width/2] = 1;
	}
	//fill horizontal with 1s
	for(int j=0; j<width; j++){
		medianFilter[height/2][j] = 1;
	}

	return medianFilter;
}
