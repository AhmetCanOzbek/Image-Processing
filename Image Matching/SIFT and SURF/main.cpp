//Ahmet Can Ozbek
//8401860152
//ozbek@usc.edu
//11.29.2015

//EE569 HW4 - Problem3a

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include "auxFunctions.h"

using namespace std;
using namespace cv;

int main(int argc, const char * argv[]) {
   
    //Read Bus Image
    Mat busImage;
    busImage = aux::readRawImage("/Users/ahmetcanozbek/Desktop/EE569/HW4/HW4_images/P3/bus.raw", 400, 300, 3);
    //Read Sedan Image
    Mat sedanImage;
    sedanImage = aux::readRawImage("/Users/ahmetcanozbek/Desktop/EE569/HW4/HW4_images/P3/sedan.raw", 400, 233, 3);
    
    
    //*BUS
    //SIFT
    cout << "*SIFT features of 'Bus' image" << endl;
    Mat busSIFT = aux::getSIFT(busImage);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3a/busSIFT.jpg", busSIFT);
    //SURF
    cout << "*SURF features of 'Bus' image" << endl;
    Mat busSURF = aux::getSURF(busImage);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3a/busSURF.jpg", busSURF);
        
    cout << endl;
    
    //*SEDAN
    //SIFT
    cout << "*SIFT features of 'Sedan' image" << endl;
    Mat sedanSIFT = aux::getSIFT(sedanImage);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3a/sedanSIFT.jpg", sedanSIFT);
    //SURF
    cout << "*SURF features of 'Sedan' image" << endl;
    Mat sedanSURF = aux::getSURF(sedanImage);
    imwrite("/Users/ahmetcanozbek/Desktop/EE569/HW4/hw4Codes/hw4p3a/sedanSURF.jpg", sedanSURF);
    
    
    cout << "End." << endl;
    return 0;
}
