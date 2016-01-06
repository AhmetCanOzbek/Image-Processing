//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015
#ifndef __CSCI574HW5__auxFunctions__
#define __CSCI574HW5__auxFunctions__

#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/features2d.hpp>


using namespace cv;

namespace aux {
    
    //Readin the .raw image file
    Mat readRawImage(String fileName, int width, int height, int channel);
    void reverseBytes(char *pixels, int lengthOfArray);
    
    //Get the words
    Mat getWords(Mat* images, int numberOfImages, Mat* descriptorsOfTrainImages,
                 PCA& pcaSIFT, SIFT& siftExtractor, int pcaDimension, int numberOfClusters, bool usePCA);
    Mat getHistogram(Mat& inputIm, Mat& codewords, SIFT& siftExtractor, PCA& pcaSIFT, bool usePCA);
    int getClosestCodewordIndex(Mat& inputFeatureVector, Mat& codewords);
    
    //Get SIFT features
    Mat getSIFT(Mat inputIm);
    
    
}


#endif /* defined(__CSCI574HW5__auxFunctions__) */
