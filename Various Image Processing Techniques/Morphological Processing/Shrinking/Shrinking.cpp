//Ahmet Can Ozbek

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include "HitOrMiss.h"

using namespace std;

bool isIsolated(unsigned char window[][3]);

int main(int argc, char *argv[])

{
	// Define file pointer and variables
	FILE *file;
	int inputBytesPerPixel;
	int inputImHeight; //Height
	int inputImWidth; //Width
	
	//Program Usage: "program_name input_image.raw output_image1.raw output_image2.raw [InputBytesPerPixel] [InputImageWidth] [InputImageHeight]"
	
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
	inputIm[87][17][0] = 0;	inputIm[84][60][0] = 0; inputIm[86][68][0] = 0;
	///////////////////////// PROCESS CODE START /////////////////////////

	//Matrix initializations
	//Constructing M Matrix
	unsigned char M[108][91];
	//Initializing it to zero
	for(int i=0; i<108; i++){
		for(int j=0; j<91; j++){
			M[i][j] = 0;
		}
	}
	//Using M matrix to get the output
	int outImHeight = 108;
	int outImWidth = 91;
	int outBytesPerPixel = 1;
	//Constructing output Matrix
	unsigned char outIm[108][91];
	//Initializing it to zero
	for(int i=0; i<108; i++){
		for(int j=0; j<91; j++){
			outIm[i][j] = 0;
		}
	}



	for(int repeat=0; repeat<10; repeat++)
	{

	//3x3 Hit or Miss Filter 1 (Stage 1)	
	//Windowing operation
	unsigned char extractedWindow[3][3];
	for(int i=1; i<107; i++){
		for(int j=1; j<90; j++){
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
	for(int i=1; i<107; i++){
		for(int j=1; j<90; j++){
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
	for(int i=0; i<108; i++){
		for(int j=0; j<91; j++){
			inputIm[i][j][0] = outIm[i][j];
		}
	}

	}


	//Counting the number of nails
	//To count the number of nails, we need to count isolated pixels in the thinned image
	int numberOfNails = 0;
	unsigned char extractedWindow[3][3];
	for(int i=1; i<107; i++){
		for(int j=1; j<90; j++){
			//extract the window
			for(int wi=0; wi<3; wi++){
				for(int wj=0; wj<3; wj++){
					extractedWindow[wi][wj] = outIm[i-1+wi][j-1+wj];					
				}
			}
			//if isolated pixel, increment the number of nails
			if(isIsolated(extractedWindow)){
				numberOfNails++;
			}
		}
	}
	cout << "Number of Nails: " << numberOfNails << endl;


	//Connected component labeling
	//Two pass algorithm is going to be applied on the thinned image
	unsigned char labelImage[108][91];
	for(int i=0; i<108; i++){
		for(int j=0; j<91; j++){
			labelImage[i][j] = outIm[i][j];
		}
	}
	vector< vector<int> > eqTable;
	eqTable.push_back( vector<int>() ); //dummy
	int totalNumberOfLabels = 0;
	int currentLabel = 0;
	for(int j=1; j<90; j++){
		for(int i=1; i<107; i++){
			//Check 8 connectivity neighbours
			if(outIm[i][j] == 255){
				//If all neighbour pixels are background
				if(labelImage[i][j-1] == 0 && labelImage[i-1][j-1] == 0 && labelImage[i-1][j] == 0 && labelImage[i+1][j+1] == 0){
					//Increment current label and assign new label number to the pixel
					currentLabel = currentLabel + 1;
					labelImage[i][j] = currentLabel;

				}else{

				}
			}
		}
	}

	
	
    ///////////////////////// PROCESS CODE END /////////////////////////

	// Write image data (filename specified by second argument) from image data matrix

	//Writing M matrix
	if (!(file=fopen(argv[2],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(M, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	//Writing outIm matrix
	if (!(file=fopen(argv[3],"wb"))) {
		cout << "Cannot open file: " << argv[2] << endl;
		exit(1);
	}
	fwrite(outIm, sizeof(unsigned char), outImHeight*outImWidth*outBytesPerPixel, file);
	fclose(file);

	
	return 0;
}

bool isIsolated(unsigned char window[][3]){

	if(window[0][0] == 0 && window[0][1] == 0 && window[0][2] == 0 &&
	   window[1][0] == 0 && window[1][1] == 255 && window[1][2] == 0 && 
	   window[2][0] == 0 && window[2][1] == 0 && window[2][2] == 0 ){
		return true;
	}else{
		return false; 
	}

}

