//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015
#include "auxFunctions.h"
#include <stdio.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <vector>
#include <iostream>
#include <string>

using namespace cv;
using namespace std;

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


Mat aux::getWords(Mat* images, int numberOfImages, Mat* descriptorsOfTrainImages,
                  PCA& pcaSIFT, SIFT& siftExtractor, int pcaDimension, int numberOfClusters,
                  bool usePCA){
    
    //SIFT feature extraction
    //Get descriptors of training images
    vector<KeyPoint> keyPoints;
    for(int i=0; i<numberOfImages; i++){
        cvtColor(images[i], images[i], CV_BGR2GRAY);
        siftExtractor.operator()(images[i], noArray(), keyPoints, descriptorsOfTrainImages[i]);
    }
    
       
    
    //Merge all SIFT features from all training images to apply PCA
    Mat mergedTrainDescriptors;
    vconcat(descriptorsOfTrainImages, numberOfImages, mergedTrainDescriptors);
    
    
    //Apply PCA to merged SIFT descriptors of all training images    
    pcaSIFT = PCA(mergedTrainDescriptors, Mat(), 0, pcaDimension);
    Mat projectedMergedTrainDescriptors;
    pcaSIFT.project(mergedTrainDescriptors, projectedMergedTrainDescriptors);
    
    if(usePCA == false){
        //Bypass PCA procedure
        projectedMergedTrainDescriptors = mergedTrainDescriptors;
    }    
    
    //k-means clustering merged SIFT features of all training images
    Mat labels;
    int attempts = 5;
    Mat clusterMeans;
    kmeans(projectedMergedTrainDescriptors, numberOfClusters, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001), attempts, KMEANS_PP_CENTERS,
           clusterMeans);
   
    
    return clusterMeans;
}

/**
    Returns the histogram feature of an image
 
    @param inputIm input image
    @param codeWords codewords from the training data (cluster centers)
    @return histogram of codewords of the input image
*/

Mat aux::getHistogram(Mat& inputIm, Mat& codewords, SIFT& siftExtractor, PCA& pcaSIFT, bool usePCA){
    
    cvtColor(inputIm, inputIm, CV_BGR2GRAY);
    
    //Initialize Histogram
    int numberOfHistogramBins = codewords.rows;
    Mat histogram = Mat::zeros(1, numberOfHistogramBins, CV_32FC1);
    
    //Extract SIFT features of the input image
    vector<KeyPoint> keyPoints; //dummy keyPoints variable
    Mat inputImDescriptor;
    siftExtractor.operator()(inputIm, noArray(), keyPoints, inputImDescriptor); //extract SIFT features
    //Apply PCA to SIFT features of input image (reduce the dimensionality)
    Mat projectedInputImDescriptor;
    pcaSIFT.project(inputImDescriptor, projectedInputImDescriptor);
    
    if(usePCA == false){
        //Bypass PCA procedure
        projectedInputImDescriptor = inputImDescriptor;
    }
    
    //Construct the histogram
    int codewordIndex = 0;
    for(int i=0; i<projectedInputImDescriptor.rows; i++){
        //Quantize the vector, (get the index)
        Mat featureVectorToBeQuantized = projectedInputImDescriptor.row(i);
        codewordIndex = aux::getClosestCodewordIndex(featureVectorToBeQuantized, codewords);
        //Update the histogram
        histogram.at<float_t>(0,codewordIndex) = histogram.at<float_t>(0,codewordIndex) + 1;
    }
    
    //Normalize the histogram
    histogram = histogram / (sum(histogram)[0]);
        
    return histogram;
}


int aux::getClosestCodewordIndex(Mat& inputFeatureVector, Mat& codewords){
    
    vector<float> distanceArray;
    
    //Get all distance between inputFeatureVector and all the codewords
    int numberOfCodewords = codewords.rows;
    for(int i=0; i<numberOfCodewords; i++){
        distanceArray.push_back(norm(inputFeatureVector, codewords.row(i)));
    }
    //Find the minimum distance and return the index
    int minIndex = min_element(distanceArray.begin(), distanceArray.end()) - distanceArray.begin();
    return minIndex;
}

Mat aux::getSIFT(Mat inputIm){
    
    //Defining keypoints and descriptors of the input image
    vector<KeyPoint> keyPoints;
    Mat descriptors;
    //Extract SIFT keypoints and their descriptors
    SIFT siftExtractor;
    siftExtractor.operator()(inputIm, noArray(), keyPoints, descriptors);
    
    Mat outSIFTim;
    drawKeypoints(inputIm, keyPoints, outSIFTim);    
    
    return outSIFTim;
}

