//Ahmet Can Ozbek
//8401860152
//EE569HW2Problem1b
#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/ml/ml.hpp"
#include "opencv2/ml.hpp"


#define IMAGE_HEIGHT 128
#define IMAGE_WIDTH 128

#define N_OF_GRASSIMAGES 48
#define N_OF_STRAWIMAGES 48
#define N_OF_SANDIMAGES 48
#define N_OF_LEATHERIMAGES 48

using namespace std;
using namespace cv;
using namespace cv::ml;

void myNormalize(Mat trainingData, Mat testData, Mat& normalizedTrainingData, Mat& normalizedTestData);
Mat getClassifiedLabelsByMinDist(Mat trainingData, Mat samples);
Mat myTransform(Mat arr, double max, double min);
Mat getFeatureVector(Mat inputImage);
Mat subtractLocalMean(Mat inputImage, int windowSize);
Mat getTensorProduct(Mat arr1, Mat arr2);
double calculateAvgEnergy(Mat inputImage);
void createTrainTestLabel(Mat featureMatrix1, Mat featureMatrix2, Mat featureMatrix3, Mat featureMatrix4,
                          Mat& trainingData, Mat& trueTrainingLabels, Mat& testingData, Mat& trueTestLabels);

void createTrainTestLabelGrass(Mat grassFeatureMatrix, Mat strawFeatureMatrix, Mat sandFeatureMatrix, Mat leatherFeatureMatrix,
                               Mat& grassTrainingData, Mat& grassTrueTrainingLabels, Mat& grassTestingData, Mat& grassTrueTestLabels);

Mat getClassMean(Mat classData);
int getNumberOfErrors(Mat arr1, Mat arr2);
void printResults(Mat trainingData, Mat testingData, Mat trueTrainingLabels, Mat trueTestLabels);


int main(int argc, const char * argv[]) {
    
    //*FILE READING
    //Read the images
    //Read 48 Grass Images
    Mat grassImg[48];
    for(int i=1; i<=N_OF_GRASSIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/grass_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/grass_" + to_string(i) + ".raw";
        }
        //Convert to char array
        char charArray[1024];
        strncpy(charArray, fileName.c_str(), sizeof(charArray));
        charArray[sizeof(charArray) - 1] = 0;
        FILE * f = fopen(charArray,"rb");
        if (!f){
            printf("bad path\n");
            return -1;
        }
        char pixels[128*128];
        fread(pixels,128*128,1,f);
        fclose(f);
        grassImg[i-1] = Mat(128,128, CV_8UC1 ,pixels).clone();
    }
    
    //Read 48 Straw Images
    Mat strawImg[48];
    for(int i=1; i<=N_OF_STRAWIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/straw_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/straw_" + to_string(i) + ".raw";
        }
        //Convert to char array
        char charArray[1024];
        strncpy(charArray, fileName.c_str(), sizeof(charArray));
        charArray[sizeof(charArray) - 1] = 0;
        FILE * f = fopen(charArray,"rb");
        if (!f){
            printf("bad path\n");
            return -1;
        }
        char pixels[128*128];
        fread(pixels,128*128,1,f);
        fclose(f);
        strawImg[i-1] = Mat(128,128, CV_8UC1 ,pixels).clone();
    }
    
    //Read 48 Sand Images
    Mat sandImg[48];
    for(int i=1; i<=N_OF_SANDIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/sand_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/sand_" + to_string(i) + ".raw";
        }
        //Convert to char array
        char charArray[1024];
        strncpy(charArray, fileName.c_str(), sizeof(charArray));
        charArray[sizeof(charArray) - 1] = 0;
        FILE * f = fopen(charArray,"rb");
        if (!f){
            printf("bad path\n");
            return -1;
        }
        char pixels[128*128];
        fread(pixels,128*128,1,f);
        fclose(f);
        sandImg[i-1] = Mat(128,128, CV_8UC1 ,pixels).clone();
    }
    
    //Read 48 Leather Images
    Mat leatherImg[48];
    for(int i=1; i<=N_OF_LEATHERIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/leather_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1b/EE569HW2Problem1b/EE569HW2Problem1b/part b/leather_" + to_string(i) + ".raw";
        }
        //Convert to char array
        char charArray[1024];
        strncpy(charArray, fileName.c_str(), sizeof(charArray));
        charArray[sizeof(charArray) - 1] = 0;
        FILE * f = fopen(charArray,"rb");
        if (!f){
            printf("bad path\n");
            return -1;
        }
        char pixels[128*128];
        fread(pixels,128*128,1,f);
        fclose(f);
        leatherImg[i-1] = Mat(128,128, CV_8UC1 ,pixels).clone();
    }
    //*FILE READING END
    //Converting all of them to double type
    //Convert grass images to double type
    for(int i=0; i<N_OF_GRASSIMAGES; i++){
        grassImg[i].convertTo(grassImg[i], CV_32FC1);
    }
    //Convert straw images to double type
    for(int i=0; i<N_OF_STRAWIMAGES; i++){
        strawImg[i].convertTo(strawImg[i], CV_32FC1);
    }
    //Convert straw images to double type
    for(int i=0; i<N_OF_SANDIMAGES; i++){
        sandImg[i].convertTo(sandImg[i], CV_32FC1);
    }
    //Convert straw images to double type
    for(int i=0; i<N_OF_LEATHERIMAGES; i++){
        leatherImg[i].convertTo(leatherImg[i], CV_32FC1);
    }
    
    //*Creating Feature Matrices
    //Get Grass Feature Matrix
    Mat grassFeatureMatrix = Mat::zeros(N_OF_GRASSIMAGES, 25, CV_32FC1);
    for(int i=0; i<N_OF_GRASSIMAGES; i++){
        getFeatureVector(grassImg[i]).copyTo(grassFeatureMatrix( Range(i,i+1), Range::all() ));
    }
    //Get Straw Feature Matrix
    Mat strawFeatureMatrix = Mat::zeros(N_OF_STRAWIMAGES, 25, CV_32FC1);
    for(int i=0; i<N_OF_STRAWIMAGES; i++){
        getFeatureVector(strawImg[i]).copyTo(strawFeatureMatrix( Range(i,i+1), Range::all() ));
    }
    //Get Sand Feature Matrix
    Mat sandFeatureMatrix = Mat::zeros(N_OF_SANDIMAGES, 25, CV_32FC1);
    for(int i=0; i<N_OF_SANDIMAGES; i++){
        getFeatureVector(sandImg[i]).copyTo(sandFeatureMatrix( Range(i,i+1), Range::all() ));
    }
    //Get Leather Feature Matrix
    Mat leatherFeatureMatrix = Mat::zeros(N_OF_LEATHERIMAGES, 25, CV_32FC1);
    for(int i=0; i<N_OF_STRAWIMAGES; i++){
        getFeatureVector(leatherImg[i]).copyTo(leatherFeatureMatrix( Range(i,i+1), Range::all() ));
    }
    
    //CREATING TRAINING, TEST AND LABEL MATRICES
    //GRASS
    Mat grassTrainingData; Mat grassTrueTrainingLabels; Mat grassTestingData; Mat grassTrueTestLabels;
    createTrainTestLabel(grassFeatureMatrix, strawFeatureMatrix, sandFeatureMatrix, leatherFeatureMatrix,
                         grassTrainingData,  grassTrueTrainingLabels, grassTestingData, grassTrueTestLabels);
    //STRAW
    Mat strawTrainingData; Mat strawTrueTrainingLabels; Mat strawTestingData; Mat strawTrueTestLabels;
    createTrainTestLabel(strawFeatureMatrix, grassFeatureMatrix, sandFeatureMatrix, leatherFeatureMatrix,
                         strawTrainingData,  strawTrueTrainingLabels, strawTestingData, strawTrueTestLabels);
    //SAND
    Mat sandTrainingData; Mat sandTrueTrainingLabels; Mat sandTestingData; Mat sandTrueTestLabels;
    createTrainTestLabel(sandFeatureMatrix, grassFeatureMatrix, strawFeatureMatrix, leatherFeatureMatrix,
                         sandTrainingData,  sandTrueTrainingLabels, sandTestingData, sandTrueTestLabels);
    //LEATHER
    Mat leatherTrainingData; Mat leatherTrueTrainingLabels; Mat leatherTestingData; Mat leatherTrueTestLabels;
    createTrainTestLabel(leatherFeatureMatrix, grassFeatureMatrix, strawFeatureMatrix, sandFeatureMatrix,
                         leatherTrainingData,  leatherTrueTrainingLabels, leatherTestingData, leatherTrueTestLabels);
    
    //NORMAlIZING
    //Grass
    Mat normalizedGrassTrainingData; Mat normalizedGrassTestingData;
    myNormalize(grassTrainingData, grassTestingData, normalizedGrassTrainingData, normalizedGrassTestingData);
    grassTrainingData = normalizedGrassTrainingData;
    grassTestingData = normalizedGrassTestingData;
    
    //Straw
    Mat normalizedStrawTrainingData; Mat normalizedStrawTestingData;
    myNormalize(strawTrainingData, strawTestingData, normalizedStrawTrainingData, normalizedStrawTestingData);
    strawTrainingData = normalizedStrawTrainingData;
    strawTestingData = normalizedStrawTestingData;
    
    //Sand
    Mat normalizedSandTrainingData; Mat normalizedSandTestingData;
    myNormalize(sandTrainingData, sandTestingData, normalizedSandTrainingData, normalizedSandTestingData);
    sandTrainingData = normalizedStrawTrainingData;
    sandTestingData = normalizedStrawTestingData;
    
    //Leather
    Mat normalizedLeatherTrainingData; Mat normalizedLeatherTestingData;
    myNormalize(leatherTrainingData, leatherTestingData, normalizedLeatherTrainingData, normalizedLeatherTestingData);
    leatherTrainingData = normalizedLeatherTrainingData;
    leatherTestingData = normalizedLeatherTestingData;
    

    //----------------------------------------------------------------------------------------------------------
    
    //1)GRASS VS NON-GRASS CLASSIFICATION
    cout << "1)GRASS VS NON-GRASS CLASSIFICATION" << endl;
    //With 25 Dimensions
    printResults(grassTrainingData, grassTestingData, grassTrueTrainingLabels, grassTrueTestLabels);
    
    //With 3 dimensions
    //Projection with PCA to 3 dimensions
    PCA myPcaGrass(grassTrainingData, Mat(), 0, 3); //0 is CV_PCA_DATA_AS_ROW,
    Mat projectedGrassTrainingData; myPcaGrass.project(grassTrainingData, projectedGrassTrainingData);
    Mat projectedGrassTestingData; myPcaGrass.project(grassTestingData, projectedGrassTestingData);
    printResults(projectedGrassTrainingData, projectedGrassTestingData, grassTrueTrainingLabels, grassTrueTestLabels);
    cout << endl;
    
    //2)STRAW VS NON-STRAW CLASSIFICATION
    cout << "2)STRAW VS NON-STRAW CLASSIFICATION" << endl;
    //With 25 Dimensions
    printResults(strawTrainingData, strawTestingData, strawTrueTrainingLabels, strawTrueTestLabels);
    //With 3 dimensions
    //Projection with PCA to 3 dimensions
    PCA myPcaStraw(strawTrainingData, Mat(), 0, 3); //0 is CV_PCA_DATA_AS_ROW,
    Mat projectedStrawTrainingData; myPcaStraw.project(strawTrainingData, projectedStrawTrainingData);
    Mat projectedStrawTestingData; myPcaStraw.project(strawTestingData, projectedStrawTestingData);
    printResults(projectedStrawTrainingData, projectedStrawTestingData, strawTrueTrainingLabels, strawTrueTestLabels);
    cout << endl;
    
    //3)SAND VS NON-SAND CLASSIFICATION
    cout << "3)SAND VS NON-SAND CLASSIFICATION" << endl;
    //With 25 Dimensions
    printResults(sandTrainingData, sandTestingData, sandTrueTrainingLabels, sandTrueTestLabels);
    //With 3 dimensions
    //Projection with PCA to 3 dimensions
    PCA myPcaSand(sandTrainingData, Mat(), 0, 3); //0 is CV_PCA_DATA_AS_ROW,
    Mat projectedSandTrainingData; myPcaSand.project(sandTrainingData, projectedSandTrainingData);
    Mat projectedSandTestingData; myPcaSand.project(sandTestingData, projectedSandTestingData);
    printResults(projectedSandTrainingData, projectedSandTestingData, sandTrueTrainingLabels, sandTrueTestLabels);
    cout << endl;    
    
    //4)LEATHER VS NON-LEATHER CLASSIFICATION
    cout << "4)LEATHER VS NON-LEATHER CLASSIFICATION" << endl;
    //With 25 Dimensions
    printResults(leatherTrainingData, leatherTestingData, leatherTrueTrainingLabels, leatherTrueTestLabels);
    //With 3 dimensions
    //Projection with PCA to 3 dimensions
    PCA myPcaLeather(leatherTrainingData, Mat(), 0, 3); //0 is CV_PCA_DATA_AS_ROW,
    Mat projectedLeatherTrainingData; myPcaLeather.project(leatherTrainingData, projectedLeatherTrainingData);
    Mat projectedLeatherTestingData; myPcaLeather.project(leatherTestingData, projectedLeatherTestingData);
    printResults(projectedLeatherTrainingData, projectedLeatherTestingData, leatherTrueTrainingLabels, leatherTrueTestLabels);
    cout << endl;
    
    cout << "End." << endl;
    return 0;
}

void printResults(Mat trainingData, Mat testingData, Mat trueTrainingLabels, Mat trueTestLabels){
    //Min. Distance To Means Classification
    //Training Data
    Mat predictedDataLabels = getClassifiedLabelsByMinDist(trainingData, trainingData);
    cout << "*Minimum Distance To Means Classifier ("<< testingData.cols << " Dimensions)" << endl;
    cout << "--(Training)Number of Errors: " << getNumberOfErrors(trueTrainingLabels, predictedDataLabels) << endl;
    cout << "--(Training)Error Rate: " << (double)getNumberOfErrors(trueTrainingLabels, predictedDataLabels) / trainingData.rows << endl;
    //Test Data
    predictedDataLabels = getClassifiedLabelsByMinDist(trainingData, testingData);
    cout << "--(Test)Number of Errors: " << getNumberOfErrors(trueTestLabels, predictedDataLabels) << endl;
    cout << "--(Test)Error Rate: " << (double)getNumberOfErrors(trueTestLabels, predictedDataLabels) / testingData.rows << endl;
    
    //SVM classification
    cout << "*SVM ("<< testingData.cols << " Dimensions)" << endl;
    //Initialize svm
    Ptr<ml::SVM> svm = ml::SVM::create();
    //Set Parameters
    svm->setType(ml::SVM::C_SVC);
    svm->setKernel(ml::SVM::LINEAR);
    //Train the SVM
    Mat trueTrainingLabels_FORSVM; trueTrainingLabels.convertTo(trueTrainingLabels_FORSVM, CV_32S);
    Mat trainingData_FORSVM; trainingData.convertTo(trainingData_FORSVM, CV_32F);
    svm->train(trainingData_FORSVM, ml::ROW_SAMPLE, trueTrainingLabels_FORSVM);
    //SVM is trained, now it is time to predict the error rate on training data
    Mat predictedDataLabels_FORSVM;
    svm->predict(trainingData, predictedDataLabels_FORSVM);
    cout << "--(Training)Number of Errors: " << getNumberOfErrors(trueTrainingLabels, predictedDataLabels_FORSVM) << endl;
    cout << "--(Training)Error Rate: " << (double)getNumberOfErrors(trueTrainingLabels, predictedDataLabels_FORSVM) / trainingData.rows << endl;
    //SVM is trained, now it is time to predict the error rate on test data
    svm->predict(testingData, predictedDataLabels_FORSVM);
    cout << "--(Test)Number of Errors: " << getNumberOfErrors(trueTestLabels, predictedDataLabels_FORSVM) << endl;
    cout << "--(Test)Error Rate: " << (double)getNumberOfErrors(trueTestLabels, predictedDataLabels_FORSVM) / testingData.rows << endl;
}


int getNumberOfErrors(Mat arr1, Mat arr2){
    assert(("numberOfErrors(), dimensions must match", arr1.rows == arr2.rows));
    
    int numberOfErrors = 0;
    for(int i=0; i<arr1.rows; i++){
        if(arr1.at<float_t>(i,0) != arr2.at<float_t>(i,0)){
            numberOfErrors = numberOfErrors + 1;
        }
    }
    return numberOfErrors;
}

void createTrainTestLabel(Mat featureMatrix1, Mat featureMatrix2, Mat featureMatrix3, Mat featureMatrix4,
                          Mat& trainingData, Mat& trueTrainingLabels, Mat& testingData, Mat& trueTestLabels){
    //Creating Training and Test data
    //Creating Training Data: 36 Grass, - 12 Straw, 12 Sand, 12 Leather
    //Mat trainingData;
    vconcat(featureMatrix1.rowRange(0, 36).clone(), featureMatrix2.rowRange(0, 12).clone(), trainingData);
    vconcat(trainingData, featureMatrix3.rowRange(0, 12).clone(), trainingData);
    vconcat(trainingData, featureMatrix4.rowRange(0, 12).clone(), trainingData);
    //Creating True Training Labels
    //Mat trueTrainingLabels;
    vconcat(Mat::ones(36, 1, CV_32FC1), (Mat::ones(36, 1, CV_32FC1))*-1 , trueTrainingLabels);
    
    //Creating Testing Data: 12 Grass - 4 Straw, 4 Sand, 4 Leather
    //Mat testingData;
    vconcat(featureMatrix1.rowRange(36, 48).clone(), featureMatrix2.rowRange(12, 16), testingData);
    vconcat(testingData, featureMatrix3.rowRange(12, 16), testingData);
    vconcat(testingData, featureMatrix4.rowRange(12, 16), testingData);
    //Creating True Test Labels
    //Mat trueTestLabels;
    vconcat(Mat::ones(12, 1, CV_32FC1), (Mat::ones(12, 1, CV_32FC1))*-1 , trueTestLabels);
}

Mat getClassifiedLabelsByMinDist(Mat trainingData, Mat samples){
    Mat class1 = trainingData.rowRange(0, 36).clone();  //If sample belongs to class1 -> +1
    Mat class2 = trainingData.rowRange(36, 72).clone(); //If sample belongs to class2 -> -1
    
    //Initialize classified labels (+1, -1)
    Mat classifiedLabels = Mat::zeros(samples.rows, 1, CV_32FC1);
    
    //Get class means
    Mat class1Mean = getClassMean(class1);
    Mat class2Mean = getClassMean(class2);
    
    for(int i=0; i<samples.rows; i++){
        double distToClass1Mean = norm(samples.row(i),class1Mean,NORM_L2);
        double distToClass2Mean = norm(samples.row(i),class2Mean,NORM_L2);
        
        if(distToClass1Mean<distToClass2Mean){
            classifiedLabels.at<float_t>(i,0) = 1;  //+1
        }else{
            classifiedLabels.at<float_t>(i,0) = -1; //-1
        }
    }
    return classifiedLabels;
}

Mat getClassMean(Mat classData){
    Mat classMean = Mat::zeros(1,classData.cols,CV_32FC1);
    for(int i=0; i<classData.cols; i++){
        classMean.at<float_t>(0,i) = mean(classData.col(i))[0];
    }
    return classMean;
}

Mat getFeatureVector(Mat inputImage){
    
    Mat featureVector;
    featureVector= Mat::ones(1, 25, CV_32FC1);
    
    //Subtracting local mean
    Mat localMeanSubtracted = subtractLocalMean(inputImage, 5);
    
    //cout << "localMeanSubtracted: \n" << localMeanSubtracted << endl;
    
    //1D Kernels
    Mat oneDimKernels[5];
    oneDimKernels[0] = (Mat_<float_t>(1,5) << 1,4,6,4,1 ); //L5
    oneDimKernels[1] = (Mat_<float_t>(1,5) << -1,-2,0,2,1); //E5
    oneDimKernels[2] = (Mat_<float_t>(1,5) << -1,0,2,0,-1); //S5
    oneDimKernels[3] = (Mat_<float_t>(1,5) << -1,2,0,-2,1); //W5
    oneDimKernels[4] = (Mat_<float_t>(1,5) << 1,-4,6,-4,1); //R5
    
    //Creating 25 Laws Filters
    Mat lawsFilters[25];
    for(int i=0; i<5; i++){
        for(int j=0; j<5; j++){
            //get the transpose
            Mat transposedKernel;
            transpose(oneDimKernels[i], transposedKernel);
            lawsFilters[i*5+j] = getTensorProduct(transposedKernel, oneDimKernels[j]);
            //cout << "lawsFilters[" << i*5+j << "]: \n" << lawsFilters[i*5+j] << endl;
        }
    }
    
    //Applying LawsFilters -> Get 25 Filtered Image
    Mat lawsFilteredImage[25];
    for(int i=0; i<25; i++){
        filter2D(inputImage, lawsFilteredImage[i], -1, lawsFilters[i]);
        //cout << "lawsFilteredImage[" << i << "]: \n" << lawsFilteredImage[i] << endl;
    }
    
    
    //Calculate the Energy in filtered 25 Laws Filtered Images
    //Put them into 'featureVector' variable and return it.
    for(int i=0; i<25; i++){
        featureVector.at<float_t>(0,i) = calculateAvgEnergy(lawsFilteredImage[i]);
        //cout << "AvgEnergy: "<< i << ": " << calculateAvgEnergy(lawsFilteredImage[i]) << endl;
    }
    
    return featureVector;
}

Mat subtractLocalMean(Mat inputImage, int windowSize){
    
    Mat paddedImage;
    copyMakeBorder(inputImage, paddedImage, windowSize/2, windowSize/2, windowSize/2, windowSize/2, BORDER_REFLECT);
    //cout << "padded: \n" << paddedImage << endl;
    
    Mat localMeanSubtracted = inputImage.clone();
    //Subctract local mean
    
    for(int i=0; i<inputImage.rows; i++){
        for(int j=0; j<inputImage.cols; j++){
            //get the mean
            double meanValue = 0;
            meanValue = mean(paddedImage(Range(i, i+windowSize),Range(j, j+windowSize)))[0];
            //cout << "MV: " << meanValue << ", ";
            //subtract from the pixel
            localMeanSubtracted.at<float_t>(i,j) = localMeanSubtracted.at<float_t>(i,j) - meanValue;
        }
    }
    return localMeanSubtracted;
}

double calculateAvgEnergy(Mat inputImage){
    
    double energy = 0;
    
    for(int i=0; i<inputImage.rows; i++){
        for(int j=0; j<inputImage.cols; j++){
            energy = energy + (double)(inputImage.at<float_t>(i,j))*(double)(inputImage.at<float_t>(i,j));
        }
    }
    
    energy = energy / (inputImage.rows*inputImage.cols);
    
    return energy;
}

Mat getTensorProduct(Mat arr1, Mat arr2){
    
    Mat tensorProduct = Mat::zeros(arr1.rows * arr2.rows, arr1.cols * arr2.cols, CV_32FC1);
    
    for(int i=0; i<arr1.rows; i++){
        for(int j=0; j<arr1.cols; j++){
            Mat src = arr2 * arr1.at<float_t>(i,j);
            src.copyTo(tensorProduct(Range(i*arr2.rows,(i+1)*arr2.rows), Range(j*arr2.cols,(j+1)*arr2.cols)));
            //cout << "Debug: " << arr2 * arr1.at<double>(i,j) << endl;
        }
    }
    return tensorProduct;
}

void myNormalize(Mat trainingData, Mat testData, Mat& normalizedTrainingData, Mat& normalizedTestData){
    
    assert(trainingData.cols == testData.cols);
    
    //Initializing
    normalizedTrainingData = Mat::zeros(trainingData.rows, trainingData.cols, CV_32FC1);
    normalizedTestData = Mat::zeros(testData.rows, testData.cols, CV_32FC1);
    
    double minValues[trainingData.cols];
    double maxValues[trainingData.cols];
    
    for(int j=0; j<trainingData.cols; j++){
        minMaxLoc(trainingData.col(j), &minValues[j], &maxValues[j]);
        myTransform(trainingData.col(j), maxValues[j], minValues[j]).copyTo(normalizedTrainingData.col(j));
        myTransform(testData.col(j), maxValues[j], minValues[j]).copyTo(normalizedTestData.col(j));
    }
}

Mat myTransform(Mat arr, double max, double min){
    return (arr - min) / (max - min);
}
