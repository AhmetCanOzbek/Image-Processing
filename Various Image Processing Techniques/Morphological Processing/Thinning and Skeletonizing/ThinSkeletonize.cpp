//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.01.2015
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include "HitOrMiss.h"

void dilate(unsigned char image[][360], unsigned char outImage[][360], int N);
void erode(unsigned char image[][360], unsigned char outImage[][360], int N);
bool isFit(unsigned char window[][7]);

using namespace std;

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

	//Pre-processing 
	//Dilation
	unsigned char dilatedIm[275][360];
	//Initalize dilatedIm
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			dilatedIm[i][j] = 0;
		}
	}
	//Just to convert 3d to 2d
	unsigned char inputImage[275][360];
	//Initialize inputImage	
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			inputImage[i][j] = inputIm[i][j][0];
		}
	}
	dilate(inputImage, dilatedIm, 7);

	//Erosion
	unsigned char erodedIm[275][360];
	//Initalize dilatedIm
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			erodedIm[i][j] = inputImage[i][j];
		}
	}
	erode(dilatedIm, erodedIm, 7);


	//*Thinning and skeletonizing
	//Matrix initializations
	//Constructing M Matrix
	unsigned char M[275][360];
	//Initializing it to zero
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			M[i][j] = 0;
		}
	}
	//Using M matrix to get the output
	int outImHeight = 275;
	int outImWidth = 360;
	int outBytesPerPixel = 1;
	//Constructing output Matrix
	unsigned char outIm[275][360];
	//Initializing it to zero
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			outIm[i][j] = 0;
		}
	}

	//With Preprocessing
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			inputIm[i][j][0] = erodedIm[i][j];
		}
	}

	//Process start
	for(int repeat=0; repeat<60; repeat++)
	{
	cout << "Progress: " << (repeat / (double)60)*100 << " percent" << endl;
	//3x3 Hit or Miss Filter 1 (Stage 1)	
	//Windowing operation
	unsigned char extractedWindow[3][3];
	for(int i=1; i<274; i++){
		for(int j=1; j<359; j++){
			//extract the window
			for(int wi=0; wi<3; wi++){
				for(int wj=0; wj<3; wj++){
					extractedWindow[wi][wj] = inputIm[i-1+wi][j-1+wj][0];					
				}
			}
			//Hit or Miss?
			//If hit			
			if(hitOrMiss(extractedWindow)){				
				M[i][j] = 255;				
			}else{				
				M[i][j] = 0;				
			}
		}
	}

	//3x3 Hit or Miss Filter 2 (Stage 2)	
	//Windowing operation
	//unsigned char extractedWindow[3][3];
	for(int i=1; i<274; i++){
		for(int j=1; j<359; j++){
			//extract the window
			for(int wi=0; wi<3; wi++){
				for(int wj=0; wj<3; wj++){
					extractedWindow[wi][wj] = M[i-1+wi][j-1+wj];					
				}
			}
			//Hit or Miss?
			//If hit			
			if(M[i][j] == 255){
				if(hitOrMiss2(extractedWindow)){					
					outIm[i][j] = inputIm[i][j][0];
					//cout << "True: " << endl;
				}else{					
					outIm[i][j] = 0;
					//cout << "False: " << endl;
				}
			}else{
				//cout << "Other" << endl;
				outIm[i][j] = inputIm[i][j][0];
			}				
		}
	}
	//To repeat the process
	for(int i=0; i<275; i++){
		for(int j=0; j<360; j++){
			inputIm[i][j][0] = outIm[i][j];
		}
	}

	}


	
	
	
	cout << "End." << endl;
	
    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix
	//Dilated Image
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(dilatedIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	//Eroded Image After Dilation
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(erodedIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	//Output im
	if (!(file=fopen(argv[4],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	
	return 0;
}

void erode(unsigned char image[][360], unsigned char outImage[][360], int N){

	N=7;
	unsigned char window[7][7];
	for(int i=0+(N); i<275-(N-1); i++){
		for(int j=0+(N); j<360-(N-1); j++){
			//extract the window
			for(int wi=0; wi<N; wi++){
				for(int wj=0; wj<N; wj++){
					window[wi][wj] = image[i+wi-N/2][j+wj-N/2];
				}
			}
			//is Fit?
			if(isFit(window)){
				outImage[i][j] = 255;
			}else{
				outImage[i][j] = 0;
			}

		}
	}

}

void dilate(unsigned char image[][360], unsigned char outImage[][360], int N){

	for(int i=0+(N/2); i<275-(N/2); i++){
		for(int j=0+(N/2); j<360-(N/2); j++){
			for(int wi=-N/2; wi<=N/2; wi++){
				for(int wj=-N/2; wj<=N/2; wj++){
					//Hit
					if(image[i+wi][j+wj] == 255){
						outImage[i][j] = 255;					
					}
				}
			}
		}
	}
}

bool isFit(unsigned char window[][7]){
	for(int i=0; i<7; i++){
		for(int j=0; j<7; j++){
			if(window[i][j] == 0){
				return false;
			}
		}
	}
	return true;
}
