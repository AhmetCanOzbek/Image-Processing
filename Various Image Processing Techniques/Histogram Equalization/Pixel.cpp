#include <iostream>
#include "Pixel.h"

//constructor
Pixel::Pixel(){
	x=0; y=0; value=0;
}

//Actuators
int Pixel::getX(){
	return x;
}

int Pixel::getY(){
	return y;
}

int Pixel::getValue(){
	return value;
}

//Setters
void Pixel::setX(int px){
	x = px;
}

void Pixel::setY(int py){
	y = py;
}

void Pixel::setValue(int pvalue){
	value = pvalue;
}

/*
	Sort a pixel array according to its value
*/
Pixel* sortPixels(Pixel* pixelArray, int arraySize){

	Pixel* sortedPixels = new Pixel[arraySize];
	for(int i=0; i<arraySize; i++){
		sortedPixels[i] = pixelArray[i];
	}
	
	Pixel tempPixel;

	for(int i=0; i<arraySize; i++){
		for(int j=i; j<arraySize; j++){
			if(sortedPixels[i].getValue() > sortedPixels[j].getValue()){
				tempPixel = sortedPixels[i];
				sortedPixels[i] = sortedPixels[j];
				sortedPixels[j] = tempPixel;				
			}
		}
	}
	return sortedPixels;
}

/*
	This function is better for memory management
*/
void sortPixelArray(Pixel* pixelArray, int arraySize){
	Pixel tempPixel;
	for(int i=0; i<arraySize; i++){
		cout << (double) (i * 100)/arraySize << "%  sort completed." << endl;
		for(int j=i; j<arraySize; j++){
			if(pixelArray[i].getValue() > pixelArray[j].getValue()){
				swapPixels(&pixelArray[i], &pixelArray[j]);	
				// tempPixel = pixelArray[i];
				// pixelArray[i] = pixelArray[j];
				// pixelArray[j] = tempPixel;											
			}
		}
	}
}

void swapPixels(Pixel* a, Pixel* b){
	Pixel temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

void quickSortPixelArray(Pixel* pixelArray, int left, int right) {
      int i = left, j = right;
      Pixel tmp;
      Pixel pivot = pixelArray[(left + right) / 2];
 
      /* partition */
      while (i <= j) {
            while (pixelArray[i].getValue() < pivot.getValue())
                  i++;
            while (pixelArray[j].getValue() > pivot.getValue())
                  j--;
            if (i <= j) {
                  tmp = pixelArray[i];
                  pixelArray[i] = pixelArray[j];
                  pixelArray[j] = tmp;
                  i++;
                  j--;
            }
      };
 
      if (left < j)
            quickSortPixelArray(pixelArray, left, j);
      if (i < right)
            quickSortPixelArray(pixelArray, i, right);
}