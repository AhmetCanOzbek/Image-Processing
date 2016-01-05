#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>
using namespace std;

class Pixel{

	public:
		Pixel();
		//actuators
		int getX();
		int getY();
		int getValue();
		//setters
		void setX(int px);
		void setY(int py);
		void setValue(int pvalue);

	private:
		int x;
		int y;
		int value;
};

//Non-member function here
Pixel* sortPixels(Pixel* pixelArray, int arraySize);
void sortPixelArray(Pixel* pixelArray, int arraySize);
void swapPixels(Pixel* a, Pixel* b);
//Faster sorting for pixels
void quickSortPixelArray(Pixel* pixelArray, int left, int right);


#endif