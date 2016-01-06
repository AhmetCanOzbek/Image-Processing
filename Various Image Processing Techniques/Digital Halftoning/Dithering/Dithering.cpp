//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//DATE
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

#define IMAGE_SIZE 512

using namespace std;

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int inputBytesPerPixel;
	int inputImHeight; //Height
	int inputImWidth; //Width
	
	//cout << "program_name input_image.raw output_image1.raw output_image2.raw [InputBytesPerPixel] [InputImageWidth] [InputImageHeight]" << endl;
	
	inputBytesPerPixel = atoi(argv[4]);
	inputImWidth = atoi(argv[5]);
	inputImHeight = atoi(argv[6]);
		
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
	
	//Initializing I2
	double I2[2][2] = {{1,2},
					   {3,0}};
	//Constructing T2 from I2
	double T2[2][2];		   
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			T2[i][j] = (I2[i][j] + 0.5) / (double)(2*2);			
		} 
	}

	//Initilazing I8
	double I8[8][8] = {{21,   37,   25,     41,    22,    38,    26,    42},
   					   {53,    5,    57,     9,    54,     6,    58,    10},
    				   {29,   45,    17,    33,    30,    46,    18,    34},
    				   {61,   13,    49,     1,    62,    14,    50,     2},
    				   {23,   39,    27,    43,    20,    36,    24,    40},
    				   {55,    7,    59,    11,    52,     4,    56,     8},
    				   {31,   47,    19,    35,    28,    44,    16,    32},
    				   {63,   15,    51,     3,    60,    12,    48,     0}};
    
    //Constructing T8 from I8
    double T8[8][8];
    for(int i=0; i<8; i++){
    	for(int j=0; j<8; j++){
    		T8[i][j] = (I8[i][j] + 0.5) / (double)(8*8);    		
    	}
    }

    //Dithering with I2
    int outImHeight = inputImHeight;
	int outImWidth = inputImWidth;
	int outBytesPerPixel = 1;
	unsigned char outImI2[outImHeight][outImWidth];

	double tempPixelValue;
	for(int i=0; i<outImHeight; i++){
		for(int j=0; j<outImWidth; j++){
			//Normalizing
			tempPixelValue = (double)inputIm[i][j][0] / 256;
			if(tempPixelValue > T2[i % 2][j % 2]){
				outImI2[i][j] = 255;				
			}else{
				outImI2[i][j] = 0;
			}
		}
	}	


    //Dithering with I8	
	unsigned char outImI8[outImHeight][outImWidth];
	for(int i=0; i<outImHeight; i++){
		for(int j=0; j<outImWidth; j++){
			//Normalizing
			tempPixelValue = (double)inputIm[i][j][0] / 256;
			if(tempPixelValue > T8[i % 8][j % 8]){
				outImI8[i][j] = 255;				
			}else{
				outImI8[i][j] = 0;
			}
		}
	}	
	
    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	//Write the first file
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outImI2, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	//Write the second file
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[3] << endl;
		exit(1);
	}
	fwrite(outImI8, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);




	return 0;
}
