//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include "auxFunctions.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
    
    
    //Read the images (School_bus1, School_bus2, Bus, Sedan)
    Mat schoolBus1_im = aux::readRawImage("/Users/ahmetcanozbek/Desktop/EE569/HW4/HW4_images/P3/School_bus1.raw", 374, 200, 3);
    Mat schoolBus2_im = aux::readRawImage("/Users/ahmetcanozbek/Desktop/EE569/HW4/HW4_images/P3/School_bus2.raw", 356, 200, 3);
    Mat bus_im = aux::readRawImage("/Users/ahmetcanozbek/Desktop/EE569/HW4/HW4_images/P3/Bus.raw", 400, 300, 3);
    Mat sedan_im = aux::readRawImage("/Users/ahmetcanozbek/Desktop/EE569/HW4/HW4_images/P3/Sedan.raw", 400, 233, 3);
    
    //Writing SIFT extracted images to file
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3c/busSIFTc.tiff", aux::getSIFT(bus_im));
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3c/sb1SIFTc.tiff", aux::getSIFT(schoolBus1_im));
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3c/sb2SIFTc.tiff", aux::getSIFT(schoolBus2_im));
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3c/sedanSIFTc.tiff", aux::getSIFT(sedan_im));
    
    //Extracting SIFT features of all image
    SIFT siftExtractor;
    
    //Putting all 3 images (schoolBus1, Bus, Sedan) into a Mat array
    Mat inputImages[3];
    inputImages[0] = schoolBus1_im;
    inputImages[1] = bus_im;
    inputImages[2] = sedan_im;
    
    //Putting their descriptors into an Mat array
    Mat inputImDescriptors[3];
    
    //Getting the codewords
    //Applying PCA to reduce dimension
    bool usePCA = false;
    PCA pcaSIFT; int pcaDimension = 20;
    int numberOfClusters = 8; //This is the parameter k in k-means algorithm
    Mat codewords;
    codewords = aux::getWords(inputImages, 3, inputImDescriptors,
                              pcaSIFT, siftExtractor, pcaDimension, numberOfClusters, usePCA);
    
    cout << "codewords: rows: " << codewords.rows << ", cols: " << codewords.cols << endl;
    
    
    //Get the codeword histogram representation of images
    Mat histSchoolBus1 = aux::getHistogram(schoolBus1_im, codewords, siftExtractor, pcaSIFT, usePCA);
    Mat histSchoolBus2 = aux::getHistogram(schoolBus2_im, codewords, siftExtractor, pcaSIFT, usePCA);
    Mat histBus = aux::getHistogram(bus_im, codewords, siftExtractor, pcaSIFT, usePCA);
    Mat histSedan = aux::getHistogram(sedan_im, codewords, siftExtractor, pcaSIFT, usePCA);
    
    
    cout << "histSB1: " << histSchoolBus1 << endl;
    cout << "histSB2: " << histSchoolBus2 << endl;
    cout << "histBus: " << histBus << endl;
    cout << "histSedan: " << histSedan << endl;
    
    cout << "SB2 - SB1: " << norm(histSchoolBus2, histSchoolBus1) << endl;
    cout << "SB2 - Bus: " << norm(histSchoolBus2, histBus) << endl;
    cout << "SB2 - Sedan: " << norm(histSchoolBus2, histSedan) << endl;    
    
    cout << "End." << endl;
    return 0;
}
