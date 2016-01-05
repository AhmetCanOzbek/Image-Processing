#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h> 
using namespace std;

#define RED 0
#define GREEN 1
#define BLUE 2

int getBinNumber(int thresholds[][4], int rgb, unsigned char pixelValue);
int getDominantColorNumber(int*** window, int windowSize, int numberOfBins, int meanOfBin[][4]);
int getColorNumber(int r, int g, int b, int meanOfBin[][4]);
int colorNumberToR(int colorNumber);
int colorNumberToG(int colorNumber);
int colorNumberToB(int colorNumber);
int colorNumberToBinNumber(int colorNumber, int rgb);

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


	//calculating thresholds and weighted mean avarage for each bin
	int level=0;
	int numberOfBins = 4;
	int thresholds[3][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}}; 
	int meanOfBin[3][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0}}; 
	int weightedSum[3][numberOfBins]; for(int rgb=0;rgb<3;rgb++){for(int i=0;i<numberOfBins;i++){weightedSum[rgb][i]=0;}}
	for(int rgb=0; rgb<3; rgb++){
		level = 0;
		for(int bin=0; bin<numberOfBins; bin++){
			int sum = 0;
			while((sum < (inputImHeight*inputImWidth)/numberOfBins) && (level < 256)){
				//if(level >= 255) { break; }
				//cout << "level: " << level << " ";
				//cout << "histogramData[rgb][level]: " << histogramData[rgb][level] << endl;
				sum = sum + histogramData[rgb][level];
				weightedSum[rgb][bin] += histogramData[rgb][level] * level;
				level = level + 1;
			} 
			thresholds[rgb][bin] = level;
			//cout << "Weighted Sum: " << weightedSum[rgb][bin] << endl;
			meanOfBin[rgb][bin] = (weightedSum[rgb][bin]) / ((inputImHeight*inputImWidth)/numberOfBins);		
		}
	}	
	

	//Define color quantized image
	int colorQinputImHeight = inputImHeight;
	int colorQinputImWidth = inputImWidth;
	int colorQbytesPerPixel = 3;
	unsigned char colorQinputIm[colorQinputImHeight][colorQinputImWidth][colorQbytesPerPixel];\

	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<colorQinputImHeight; i++){
			for(int j=0; j<colorQinputImWidth; j++){				
				colorQinputIm[i][j][rgb] = inputIm[i][j][rgb];
			}
		}
	}
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<colorQinputImHeight; i++){
			for(int j=0; j<colorQinputImWidth; j++){				
				colorQinputIm[i][j][rgb] = meanOfBin[rgb][getBinNumber(thresholds,rgb, colorQinputIm[i][j][rgb])];				
			}
		}
	}

		
	//Write Color Quantized Image to file	
	string headerFileName ("outColorQ");
	string inputFileName (argv[1]);
	string tmp = headerFileName + inputFileName;
	char merged[1024];
	strncpy(merged, tmp.c_str(), sizeof(merged));
	merged[sizeof(merged) - 1] = 0;
	if (!(file=fopen(merged,"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(colorQinputIm, sizeof(unsigned char), colorQinputImHeight*colorQinputImWidth*colorQbytesPerPixel, file);
	fclose(file);


	//Defining an extended version of colorQuantizedInputImage
	int windowSize = 5; //N
	int paddedColorQinputImHeight = colorQinputImHeight + (windowSize/2);
	int paddedColorQinputImWidth = colorQinputImWidth + (windowSize/2);
	int paddedColorQinputImBytesPerPixel = 3;
	unsigned char paddedColorQinputIm[paddedColorQinputImHeight][paddedColorQinputImWidth][paddedColorQinputImBytesPerPixel];

	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<paddedColorQinputImHeight; i++){
			for(int j=0; j<paddedColorQinputImWidth; j++){
				paddedColorQinputIm[i][j][rgb] = 0;
			}
		}
	}
	for(int rgb=0; rgb<3; rgb++){
		for(int i=2; i<paddedColorQinputImHeight; i++){
			for(int j=2; j<paddedColorQinputImWidth; j++){
				paddedColorQinputIm[i][j][rgb] = colorQinputIm[i-2][j-2][rgb];
			}
		}
	}	
		
	//Define the output image
	int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 3;	
	unsigned char outIm[outImHeight][outImWidth][outBytesPerPixel];

	//Initializing the output image
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				outIm[i][j][rgb] = 0;
			}
		}
	}
	//Modifying the output image
	//Allocate window 
	int*** window = new int**[windowSize];
	for(int i = 0; i < windowSize; i++){
		window[i] = new int*[windowSize];
		for(int j = 0; j < windowSize; j++){
      		window[i][j] = new int[3];
      }
  	}

  	//Procedure
	for(int rgb=0; rgb<3; rgb++){
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){				
				//get the window
				for(int wi=-(windowSize/2); wi<(windowSize/2)+1; wi++){
					for(int wj=-(windowSize/2); wj<(windowSize/2)+1; wj++){
						window[wi+(windowSize/2)][wj+(windowSize/2)][rgb] = paddedColorQinputIm[i+wi][j+wj][rgb];
						//window[wi+(windowSize/2)][wj+(windowSize/2)][rgb] = 0;
					}
				}				
				int colorNumber = getDominantColorNumber(window, windowSize, numberOfBins, meanOfBin);	
				outIm[i][j][rgb] = meanOfBin[rgb][colorNumberToBinNumber(colorNumber, rgb)];
			}
		}
	}
  	
		
    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix
	string outputFileName (argv[2]);
	string tmpOut = "N" + to_string(windowSize) + outputFileName;
	char mergedOut[1024];
	strncpy(mergedOut, tmpOut.c_str(), sizeof(merged));
	merged[sizeof(mergedOut) - 1] = 0;

	if (!(file=fopen(mergedOut,"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	return 0;
}


/*
	This function returns the number of bin in which the pixel belongs
*/
int getBinNumber(int thresholds[][4], int rgb, unsigned char pixelValue){

	if(pixelValue < thresholds[rgb][0]){
		return 0;
	}
	if((pixelValue >= thresholds[rgb][0]) && (pixelValue < thresholds[rgb][1])){
		return 1;
	}
	if((pixelValue >= thresholds[rgb][1]) && (pixelValue < thresholds[rgb][2])){
		return 2;
	}
	if(pixelValue >= thresholds[rgb][2]){
		return 3;
	}

	return -1;
}

int getDominantColorNumber(int*** window, int windowSize, int numberOfBins, int meanOfBin[][4]){

	int colors[(int)pow(numberOfBins,3)];

	for(int i=0; i<pow(numberOfBins,3); i++){
		colors[i] = 0;		
	}	
	int colorNumber = 0;
	for(int i=0; i<windowSize; i++){
		for(int j=0; j<windowSize; j++){
			colorNumber = getColorNumber(window[i][j][RED],window[i][j][GREEN],window[i][j][BLUE], meanOfBin);
			colors[colorNumber] +=1;
		}
	}
	//Find the max(dominant) one and return it
	int max = -9999; //some small number
	int maxIndex = 0;
	for(int i=0; i<(int)pow(numberOfBins,3); i++){
		if(colors[i]>max){
			max = colors[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

/*
	returns the color number between 0-63
*/
int getColorNumber(int r, int g, int b, int meanOfBin[][4]){

	int colorNumber = 0;	

	for(int bin=0; bin<4; bin++){
		//R		
		if(meanOfBin[RED][bin] == r){								
			colorNumber = colorNumber +  bin*((int)pow(4,0));
		}
		//G
		if(meanOfBin[GREEN][bin] == g){					
			colorNumber = colorNumber +  bin*((int)pow(4,1));
		}
		//B
		if(meanOfBin[BLUE][bin] == b){				
			colorNumber = colorNumber +  bin*((int)pow(4,2));
		}
	}		

	return colorNumber;
}

int colorNumberToBinNumber(int colorNumber, int rgb){
	if(rgb==RED){
		return colorNumber%4;
	}
	if(rgb==GREEN){
		return (colorNumber/4)%4;
	}
	if(rgb==BLUE){
		return (colorNumber/(4*4))%4;
	}
	return -1;
}


