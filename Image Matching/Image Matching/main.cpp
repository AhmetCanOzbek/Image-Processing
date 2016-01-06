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
    
    //Initializing variables for SIFT
    //key points
    vector<KeyPoint> kp_SchoolBus1;
    vector<KeyPoint> kp_SchoolBus2;
    vector<KeyPoint> kp_Bus;
    vector<KeyPoint> kp_Sedan;
    //Descriptors
    Mat desc_SchoolBus1;
    Mat desc_SchoolBus2;
    Mat desc_Bus;
    Mat desc_Sedan;
    
    
    //Extracting SIFT features of all image
    SIFT siftExtractor;
    siftExtractor.operator()(schoolBus1_im, noArray(), kp_SchoolBus1, desc_SchoolBus1);
    siftExtractor.operator()(schoolBus2_im, noArray(), kp_SchoolBus2, desc_SchoolBus2);
    siftExtractor.operator()(bus_im, noArray(), kp_Bus, desc_Bus);
    siftExtractor.operator()(sedan_im, noArray(), kp_Sedan, desc_Sedan);
    
    
    //School_bus1 and School_bus2 images
    //Showing the keypoints in images
    Mat schoolBus1kp; Mat schoolBus2kp;
    drawKeypoints(schoolBus1_im, kp_SchoolBus1, schoolBus1kp);
    drawKeypoints(schoolBus2_im, kp_SchoolBus2, schoolBus2kp);
    //Merge two keypoint images
    Mat mergedSchoolBusKp;
    hconcat(schoolBus1kp, schoolBus2kp, mergedSchoolBusKp);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3b/SIFTkp2BusImages.tiff", mergedSchoolBusKp);
    
    
    bool thresholdFlag = true;
    cout << "SB1, SB2" << endl;
    //Matching features between SchoolBus1, SchoolBus2, and showing the results
    Mat matchIm_S1_S2 = aux::getSIFTmatchImage(schoolBus1_im, desc_SchoolBus1, kp_SchoolBus1,
                                               schoolBus2_im, desc_SchoolBus2, kp_SchoolBus2,
                                               0.7, thresholdFlag);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3b/SIFTmatch2BusImages.tiff", matchIm_S1_S2);
    
    
    
    cout << "SB1, BUS" << endl;
    //Matching between schoolBus1 and Bus
    Mat matchIm_SB1_B = aux::getSIFTmatchImage(schoolBus1_im, desc_SchoolBus1, kp_SchoolBus1,
                                               bus_im, desc_Bus, kp_Bus,
                                               1, thresholdFlag);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3b/SIFTmatch_SchoolBus1_Bus.tiff", matchIm_SB1_B);
    
    
    cout << "SB1, Sedan" << endl;
    //Matching between schoolBus1 and Sedan
    Mat matchIm_SB1_S = aux::getSIFTmatchImage(schoolBus1_im, desc_SchoolBus1, kp_SchoolBus1,
                                               sedan_im, desc_Sedan, kp_Sedan,
                                               1, thresholdFlag);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3b/SIFTmatch_SchoolBus1_Sedan.tiff", matchIm_SB1_S);
    
  
    
    cout << "End." << endl;
    return 0;
}
