//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015

#include "auxFunctions.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

using namespace std;
using namespace cv;

Mat aux::getSIFT(Mat inputIm){
    
    //Defining keypoints and descriptors of the input image
    vector<KeyPoint> keyPoints;
    Mat descriptors;
    //Extract SIFT keypoints and their descriptors
    double t = (double)getTickCount();
    SIFT siftExtractor;
    siftExtractor.operator()(inputIm, noArray(), keyPoints, descriptors);
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "SIFT done in seconds: " << t << endl;
    
    Mat outSIFTim;
    drawKeypoints(inputIm, keyPoints, outSIFTim);
    
    cout << "Number Of Keypoints: " << keyPoints.size() << endl;
    
    return outSIFTim;
}

Mat aux::getSURF(Mat inputIm){
    
    //Defining keypoints and descriptors of the input image
    vector<KeyPoint> keyPoints;
    Mat descriptors;
    //Extract SURF keypoints and their descriptors
    double t = (double)getTickCount();
    SURF surfExtractor;
    surfExtractor.operator()(inputIm, noArray(), keyPoints, descriptors);
    t = ((double)getTickCount() - t)/getTickFrequency();
    cout << "SURF done in seconds: " << t << endl;
    
    Mat outSURFim;
    drawKeypoints(inputIm, keyPoints, outSURFim);
    
    cout << "Number Of Keypoints: " << keyPoints.size() << endl;
    
    return outSURFim;
}

/*
    Read the .raw file and return Mat object of the image
*/
Mat aux::readRawImage(String fileName, int width, int height, int channel){
    char charArray[1024];
    strncpy(charArray, fileName.c_str(), sizeof(charArray));
    charArray[sizeof(charArray) - 1] = 0;
    FILE * f = fopen(charArray,"rb");
    if (!f){
        printf("bad path\n");
    }
    char pixels[width * height * channel];
    fread(pixels,width * height * channel,1,f);
    fclose(f);
    int type = 0;
    if(channel == 1){type = CV_8UC1;}
    if(channel == 3){type = CV_8UC3;}
    
    reverseBytes(pixels, width * height * channel);
    
    return Mat(height,width, type ,pixels).clone();
    
}

/**
 The data in the .raw format is in the shape -> R byte, G byte, B byte, R byte and so on..
 However opencv Mat() constructor expects it in the reverse shape (BGR)
 That is why I need this function to reverse B and R
*/

void aux::reverseBytes(char *pixels, int lengthOfArray){
    //temporary char variable to swap two char variables
    char temp;
    for(int i=0; i<lengthOfArray; i = i+3){
        temp = pixels[i+2];
        pixels[i+2] = pixels[i];
        pixels[i] = temp;
    }    
}