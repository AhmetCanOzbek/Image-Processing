//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015

#include "auxFunctions.h"
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <string>

using namespace std;
using namespace cv;

/*
    In this function, the boolean parameter 'thresholdFlag' indicates
    whether some matches should be eliminated by a threshold factor or not
*/

Mat aux::getSIFTmatchImage(Mat im1, Mat desc_im1, vector<KeyPoint>& kp_im1,
                           Mat im2, Mat desc_im2, vector<KeyPoint>& kp_im2,
                           double thresholdFactor, bool thresholdFlag){
    
    //Get matches
    BFMatcher matcher(NORM_L2);
    vector<DMatch> matches;
    matcher.match(desc_im1, desc_im2, matches);
    
    //Filter some matches and be left with strong ones
    vector<float> matchDistances;
    for(int i=0; i<matches.size(); i++){
        matchDistances.push_back(matches[i].distance);        
    }
    cout << endl;
    
    float minDistance = *min_element(matchDistances.begin(), matchDistances.end());
    float maxDistance = *max_element(matchDistances.begin(), matchDistances.end());
    
    float threshold = ((maxDistance - minDistance) / (2.0)) + minDistance;
    threshold = threshold * thresholdFactor;
    
    //Get the matches that are lower than the threshold
    vector<DMatch> goodMatches;
    for(int i=0; i<matches.size(); i++){
        if(thresholdFlag == true){
            if(matches[i].distance < threshold){
                goodMatches.push_back(matches[i]);
            }
        }else{
            goodMatches.push_back(matches[i]);
        }        
    }    
    
    //Get the matched image of two images
    Mat matchIm;
    drawMatches(im1, kp_im1, im2, kp_im2, goodMatches, matchIm);
    
    //Extend image to put text to the top
    vconcat(Mat::zeros(25, matchIm.cols, matchIm.type()), matchIm, matchIm);
    
    putText(matchIm, "NumberOfMatches: " +  to_string(goodMatches.size()) , cvPoint(5, 20), FONT_HERSHEY_PLAIN, 1.5, cvScalar(0,0,255),1.7);
    
    return matchIm;
}



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