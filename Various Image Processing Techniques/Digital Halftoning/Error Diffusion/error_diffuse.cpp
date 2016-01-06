//Ahmet Can Ozbek

#include "ErrorDiffusion.h"
#include <iostream>

using namespace std;

void errorDiffuse(unsigned char inputIm[][512], int outImHeight, int outImWidth, int method){

	//*Floyd-Steinberg
	if(method == 1){	
		cout << "Floyd-Steinberg Process:" << endl;
		//Padded Output Image, Surrounding the input image with 0's with 1 unit
		int outPaddedImHeight = outImHeight+2;
		int outPaddedImWidth = outImWidth+2;
		unsigned char outPaddedIm[outPaddedImHeight][outPaddedImWidth];
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				outPaddedIm[i+1][j+1] = inputIm[i][j];
			}
		}
		//Error Diffusion Process Start
		double tempSavedPixel = 0;
		for(int i=0; i<outImHeight; i++){
			//Left to Right
			if(i % 2 == 0){
				for(int j=0; j<outImWidth; j++){
					//Saving the pixel value (to calculate error later)
					tempSavedPixel= outPaddedIm[i+1][j+1];
				
					//Thresholding with threshold 127
					if(outPaddedIm[i+1][j+1] > 127){
						outPaddedIm[i+1][j+1] = 255;
					}else{
						outPaddedIm[i+1][j+1] = 0;
					}
				
					//Calculating Error
					double error = tempSavedPixel - outPaddedIm[i+1][j+1];

					//Diffuse Error To Neighbour Pixels
					double fs[3][3] = {{0,0,0},
									   {0,0,7},
									   {3,5,1}};
									   
					for(int m=0; m<3; m++){
						for(int n=0; n<3; n++){
							outPaddedIm[i+m][j+n] += error * (fs[m][n])/(double)16;
						}
					}	
				}
			}
			//Right To Left
			if(i % 2 == 1){
				for(int j=outImWidth-1; j>=0; j--){
					//Saving the pixel value (to calculate error later)
					tempSavedPixel = outPaddedIm[i+1][j+1];
				
					//Thresholding with threshold 127
					if(outPaddedIm[i+1][j+1] > 127){					
						outPaddedIm[i+1][j+1] = 255;
					}else{					
						outPaddedIm[i+1][j+1] = 0;
					}
				
					//Calculating Error
					double error = tempSavedPixel - outPaddedIm[i+1][j+1];

					//Diffuse Error To Neighbour Pixels
					double fs[3][3] = {{0,0,0},
									   {7,0,0},
									   {1,5,3}};
									   
					for(int m=0; m<3; m++){
						for(int n=0; n<3; n++){
							outPaddedIm[i+m][j+n] += error * (fs[m][n])/(double)16;
						}
					}	
				}
			}		
		}
		//Crop Padded Image
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				inputIm[i][j] = outPaddedIm[i+1][j+1];
			}
		}
	}

	//*JJN
	if(method == 2){
		cout << "JJN process:" << endl;
		//Padded Output Image, Surrounding the input image with 0's with 1 unit
		int outPaddedImHeight = outImHeight+4;
		int outPaddedImWidth = outImWidth+4;
		unsigned char outPaddedIm[outPaddedImHeight][outPaddedImWidth];
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				outPaddedIm[i+1][j+1] = inputIm[i][j];
			}
		}
		//Error Diffusion Process Start
		double tempSavedPixel = 0;
		for(int i=0; i<outImHeight; i++){
			//Left to Right
			if(i % 2 == 0){
				for(int j=0; j<outImWidth; j++){
					//Saving the pixel value (to calculate error later)
					tempSavedPixel= outPaddedIm[i+1][j+1];
				
					//Thresholding with threshold 127
					if(outPaddedIm[i+1][j+1] > 127){
						outPaddedIm[i+1][j+1] = 255;
					}else{
						outPaddedIm[i+1][j+1] = 0;
					}
				
					//Calculating Error
					double error = tempSavedPixel - outPaddedIm[i+1][j+1];

					//Diffuse Error To Neighbour Pixels
					double jjn[5][5] = {{0,0,0,0,0},
										{0,0,0,0,0},
										{0,0,0,7,5},
									    {3,5,7,5,3},
										{1,3,5,3,1}};
					for(int m=0; m<5; m++){
						for(int n=0; n<5; n++){
							outPaddedIm[i+m][j+n] += error * (jjn[m][n])/(double)48;
						}
					}					
				}
			}
			//Right To Left
			if(i % 2 == 1){
				for(int j=outImWidth-1; j>=0; j--){
					//Saving the pixel value (to calculate error later)
					tempSavedPixel = outPaddedIm[i+1][j+1];
				
					//Thresholding with threshold 127
					if(outPaddedIm[i+1][j+1] > 127){					
						outPaddedIm[i+1][j+1] = 255;
					}else{					
						outPaddedIm[i+1][j+1] = 0;
					}
				
					//Calculating Error
					double error = tempSavedPixel - outPaddedIm[i+1][j+1];

					//Diffuse Error To Neighbour Pixels
					double jjn[5][5] = {{0,0,0,0,0},
										{0,0,0,0,0},
										{5,7,0,0,0},
									    {3,5,7,5,3},
										{1,3,5,3,1}};
					for(int m=0; m<5; m++){
						for(int n=0; n<5; n++){
							outPaddedIm[i+m][j+n] += error * (jjn[m][n])/(double)48;
						}
					}
				}
			}		
		}
		//Crop Padded Image
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				inputIm[i][j] = outPaddedIm[i+1][j+1];
			}
		}
	}

	
	//*Stucki
	if(method == 3){
		cout << "Stucki process:" << endl;
		//Padded Output Image, Surrounding the input image with 0's with 1 unit
		int outPaddedImHeight = outImHeight+4;
		int outPaddedImWidth = outImWidth+4;
		unsigned char outPaddedIm[outPaddedImHeight][outPaddedImWidth];
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				outPaddedIm[i+1][j+1] = inputIm[i][j];
			}
		}
		//Error Diffusion Process Start
		double tempSavedPixel = 0;
		for(int i=0; i<outImHeight; i++){
			//Left to Right
			if(i % 2 == 0){
				for(int j=0; j<outImWidth; j++){
					//Saving the pixel value (to calculate error later)
					tempSavedPixel= outPaddedIm[i+1][j+1];
				
					//Thresholding with threshold 127
					if(outPaddedIm[i+1][j+1] > 127){
						outPaddedIm[i+1][j+1] = 255;
					}else{
						outPaddedIm[i+1][j+1] = 0;
					}
				
					//Calculating Error
					double error = tempSavedPixel - outPaddedIm[i+1][j+1];

					//Diffuse Error To Neighbour Pixels
					double stucki[5][5] = {{0,0,0,0,0},
										   {0,0,0,0,0},
										   {0,0,0,8,4},
									       {2,4,8,4,2},
										   {1,2,4,2,1}};
					for(int m=0; m<5; m++){
						for(int n=0; n<5; n++){
							outPaddedIm[i+m][j+n] += error * (stucki[m][n])/(double)42;
						}
					}					
				}
			}
			//Right To Left
			if(i % 2 == 1){
				for(int j=outImWidth-1; j>=0; j--){
					//Saving the pixel value (to calculate error later)
					tempSavedPixel = outPaddedIm[i+1][j+1];
				
					//Thresholding with threshold 127
					if(outPaddedIm[i+1][j+1] > 127){					
						outPaddedIm[i+1][j+1] = 255;
					}else{					
						outPaddedIm[i+1][j+1] = 0;
					}
				
					//Calculating Error
					double error = tempSavedPixel - outPaddedIm[i+1][j+1];

					//Diffuse Error To Neighbour Pixels
					double stucki[5][5] = {{0,0,0,0,0},
										   {0,0,0,0,0},
										   {4,8,0,0,0},
									       {2,4,8,4,2},
										   {1,2,4,2,1}};
					for(int m=0; m<5; m++){
						for(int n=0; n<5; n++){
							outPaddedIm[i+m][j+n] += error * (stucki[m][n])/(double)42;
						}
					}
				}
			}		
		}
		//Crop Padded Image
		for(int i=0; i<outImHeight; i++){
			for(int j=0; j<outImWidth; j++){
				inputIm[i][j] = outPaddedIm[i+1][j+1];
			}
		}

	}
}