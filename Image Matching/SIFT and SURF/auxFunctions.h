//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015

#ifndef __EE569HW5P3a__auxFunctions__
#define __EE569HW5P3a__auxFunctions__

#include <stdio.h>
#include <opencv2/core/core.hpp>

using namespace cv;

namespace aux {
    
    //Read Raw Image
    Mat readRawImage(String fileName, int width, int height, int channel);
    void reverseBytes(char *pixels, int lengthOfArray); //Helper function to read the raw image
    
    //Get SIFT features on image
    Mat getSIFT(Mat inputIm);
    
    //Get SURF features on image
    Mat getSURF(Mat inputIm);
    
}

#endif /* defined(__EE569HW5P3a__auxFunctions__) */
