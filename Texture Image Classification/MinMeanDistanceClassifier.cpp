//EE569 HW2 Problem 1a
//Ahmet Can Ozbek

#include <iostream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"


#define IMAGE_HEIGHT 128
#define IMAGE_WIDTH 128

#define N_OF_GRASSIMAGES 36
#define N_OF_STRAWIMAGES 36
#define N_OF_UNKNOWNIMAGES 24

using namespace cv;
using namespace std;

Mat getFeatureVector(Mat image);
Mat subtractLocalMean(Mat inputImage, int windowSize);
Mat getTensorProduct(Mat arr1, Mat arr2);
Mat getClassifiedLabelsByMahDis(Mat grassData, Mat strawData, Mat samples);
double calculateAvgEnergy(Mat inputImage);
int getNumberOfErrors(Mat arr1, Mat arr2);
void myNormalize(Mat trainingData, Mat testData, Mat& normalizedTrainingData, Mat& normalizedTestData);
Mat applyFunction(Mat arr, double max, double min);
Mat myTransform(Mat arr, double max, double min);
void PCA_procedure(Mat trainingData, Mat testFeatureMatrix, Mat trueTrainingLabels, Mat trueTestLabels);
void LDA_procedure(Mat trainingData, Mat testFeatureMatrix, Mat trueTrainingLabels, Mat trueTestLabels);

int main(int argc, const char * argv[]) {
    
    //*FILE READING
    //Read the images
    //Read 36 Grass Images
    Mat grassImg[36];
    for(int i=1; i<=N_OF_GRASSIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/part a/grass_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/part a/grass_" + to_string(i) + ".raw";
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
    //Read 36 Straw Images
    Mat strawImg[36];
    for(int i=1; i<=N_OF_STRAWIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/part a/straw_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/part a/straw_" + to_string(i) + ".raw";
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
    //Read 24 unknown images
    Mat unknownImg[24];
    for(int i=1; i<=N_OF_UNKNOWNIMAGES; i++){
        string fileName;
        if(i < 10){
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/part a/unknown_0" + to_string(i) + ".raw";
        }else{
            fileName = "/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/part a/unknown_" + to_string(i) + ".raw";
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
        unknownImg[i-1] = Mat(128,128, CV_8UC1 ,pixels).clone();
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
    //Convert unknown images to double type
    for(int i=0; i<N_OF_UNKNOWNIMAGES; i++){
        unknownImg[i].convertTo(unknownImg[i], CV_32FC1);
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
    //Get Test Samples Feature Matrix
    Mat testFeatureMatrix = Mat::zeros(N_OF_UNKNOWNIMAGES, 25, CV_32FC1);
    for(int i=0; i<N_OF_UNKNOWNIMAGES; i++){
        getFeatureVector(unknownImg[i]).copyTo(testFeatureMatrix( Range(i,i+1), Range::all() ));
    }
    
    
    cout << "Minimum Mahalanobis Distance To Class Means Classifier: " << endl;
    //Labeling: 1 for Grass, 0 for Straw
    //TRAINING DATA ERROR CALCULATION
    //get training data matrix
    Mat trainingData;
    vconcat(grassFeatureMatrix, strawFeatureMatrix, trainingData);
    //get true training labels
    Mat trueTrainingLabels;
    vconcat(Mat::ones(36, 1, CV_32FC1), Mat::zeros(36, 1, CV_32FC1), trueTrainingLabels);
    //classify and get predicted labels by minimum Mah. distance to class means classifier
    Mat classifiedTrainingLabelsByMahDis = getClassifiedLabelsByMahDis(grassFeatureMatrix, strawFeatureMatrix, trainingData);
    //Calculating the error rate in the Training Data
    int numberOfErrorsInTrainingData = 0;
    for(int i=0; i<trainingData.rows; i++){
        if(trueTrainingLabels.at<float_t>(i,0) != classifiedTrainingLabelsByMahDis.at<float_t>(i,0)){
            numberOfErrorsInTrainingData = numberOfErrorsInTrainingData + 1;
        }
    }
    cout << "Number of Errors in Training Data: " << numberOfErrorsInTrainingData << endl;
    cout << "Error Rate in Training Data: " <<  ((double)numberOfErrorsInTrainingData / trainingData.rows) << endl;
    
    
    //TEST DATA ERROR CALCULATION
    //get true test labels
    Mat trueTestLabels = (Mat_<float_t>(1,N_OF_UNKNOWNIMAGES) << 0,0,1,1,1,0,1,0,0,1,1,1,0,1,0,0,0,0,1,1,1,0,0,1 );
    transpose(trueTestLabels, trueTestLabels);
    //classify and get predicted labels by minimum Mah. distance to class means classifier
    Mat classifiedTestLabelsByMahDis = getClassifiedLabelsByMahDis(grassFeatureMatrix, strawFeatureMatrix, testFeatureMatrix);
    //Calculating the error rate in the test Data
    int numberOfErrorsInTestData = 0;
    for(int i=0; i<testFeatureMatrix.rows; i++){
        if(trueTestLabels.at<float_t>(i,0) != classifiedTestLabelsByMahDis.at<float_t>(i,0)){
            numberOfErrorsInTestData = numberOfErrorsInTestData + 1;
        }
    }
    cout << "Number of Errors in Test Data: " << numberOfErrorsInTestData << endl;
    cout << "Error Rate in Test Data: " <<  ((double)numberOfErrorsInTestData / testFeatureMatrix.rows) << endl;
    
    
    //*DIMENSION REDUCTION
    //PCA
    PCA_procedure(trainingData, testFeatureMatrix, trueTrainingLabels, trueTestLabels);
    
    //LDA
    //LDA_procedure(trainingData, testFeatureMatrix, trueTrainingLabels, trueTestLabels);
    
    
    //Write to file
    //    FILE *imageFile = fopen("/Users/ahmetcanozbek/Desktop/EE569/HW2/HW2Codes/EE569HWQ1a/EE569HWQ1a/outputqqq.raw", "wb");
    //    fwrite(img.data, 128*128, sizeof(u_int8_t), imageFile);
    //
    
    cout << "End." << endl;
}

void LDA_procedure(Mat trainingData, Mat testFeatureMatrix, Mat trueTrainingLabels, Mat trueTestLabels){
    cout << "*Dimension Reduction*" << endl;
    cout << "LDA: " << endl;
    //LDA - REDUCING TO 1 DIMENSION
    //Normalizing the training and test data
    Mat normalizedTrainingData;
    Mat normalizedTestData;
    myNormalize(trainingData, testFeatureMatrix, normalizedTrainingData, normalizedTestData);
    //LDA start
    //Project training and test data to dimension 1
    LDA myLDA(normalizedTrainingData, trueTrainingLabels, 1);
    Mat projectedTrainingData = myLDA.project(normalizedTrainingData);
    Mat projectedTestData = myLDA.project(normalizedTestData);
    
    //Convert to CV_32FC1
    projectedTrainingData.convertTo(projectedTrainingData, CV_32FC1);
    projectedTestData.convertTo(projectedTestData, CV_32FC1);
    
    //Classification by Mah. distance for dimensionality reduced to 1
    //Calculating error rate on training data for dimension=1
    Mat projectedGrassData = projectedTrainingData(Range(0,36), Range::all()).clone();
    Mat projectedStrawData = projectedTrainingData(Range(36,72), Range::all()).clone();
    
    Mat classifiedTrainingLabelsByMahDisLDA = getClassifiedLabelsByMahDis(projectedGrassData, projectedStrawData, projectedTrainingData.clone());
    cout << "labels: \n" << classifiedTrainingLabelsByMahDisLDA << endl;
    int numberOfErrorsInTrainingDataLDA = getNumberOfErrors(trueTrainingLabels, classifiedTrainingLabelsByMahDisLDA);
    
    cout << "(LDA)Number of Errors in Training data with dimensions reduced to 1: " << numberOfErrorsInTrainingDataLDA << endl;

    //Calculate error rate on test data for dimension=1
    Mat classifiedTestLabelsByMahDisLDA = getClassifiedLabelsByMahDis(projectedGrassData, projectedStrawData, projectedTestData);
    int numberOfErrorsInTestDataLDA = getNumberOfErrors(trueTestLabels, classifiedTestLabelsByMahDisLDA);
    cout << "(LDA)Number of Errors in Test data with dimensions reduced to 1: " << numberOfErrorsInTestDataLDA << endl;
    
}

void PCA_procedure(Mat trainingData, Mat testFeatureMatrix, Mat trueTrainingLabels, Mat trueTestLabels){
    cout << "*Dimension Reduction*" << endl;
    cout << "PCA: " << endl;
    //PCA - REDUCING TO 1 DIMENSION
    //Normalizing the training and test data
    Mat normalizedTrainingData;
    Mat normalizedTestData;
    myNormalize(trainingData, testFeatureMatrix, normalizedTrainingData, normalizedTestData);
    //Pca start
    //Project training and test data to dimension 1
    
    //Another try
    PCA myPca(normalizedTrainingData, Mat(), 0, 1); //0 is CV_PCA_DATA_AS_ROW,
    Mat projectedTrainingData; myPca.project(normalizedTrainingData, projectedTrainingData);
    Mat projectedTestData; myPca.project(normalizedTestData, projectedTestData);
    //cout << "Train: \n" << projectedTrainingData << endl;
    //cout << "Test: \n" << projectedTestData << endl;
    //Another try end
    
    //**
//    int reducedDimensionalityPCA = 1;
//    PCA myPca(normalizedTrainingData, Mat(), 0, reducedDimensionalityPCA); //0 is CV_PCA_DATA_AS_ROW, Reducing to 1 dimension
//    Mat projectedTrainingData(normalizedTrainingData.rows, 1, CV_32FC1); //This will have reduced dimensionality to 1 feature
//    Mat projectedTestData(normalizedTestData.rows, 1, CV_32FC1);
//    myPca.project(normalizedTrainingData, projectedTrainingData);
//    myPca.project(normalizedTestData, projectedTestData);
    //**    
    
    //Convert to CV_32FC1
    projectedTrainingData.convertTo(projectedTrainingData, CV_32FC1);
    projectedTestData.convertTo(projectedTestData, CV_32FC1);
    
    //Classification by Mah. distance for dimensionality reduced to 1
    //Calculating error rate on training data for dimension=1
    Mat projectedGrassData = projectedTrainingData(Range(0,36), Range::all()).clone();
    Mat projectedStrawData = projectedTrainingData(Range(36,72), Range::all()).clone();
    
    Mat classifiedTrainingLabelsByMahDisPCA = getClassifiedLabelsByMahDis(projectedGrassData, projectedStrawData, projectedTrainingData);
    int numberOfErrorsInTrainingDataPCA = getNumberOfErrors(trueTrainingLabels, classifiedTrainingLabelsByMahDisPCA);
    cout << "(PCA)Number of Errors in Training data with dimensions reduced to 1: " << numberOfErrorsInTrainingDataPCA << endl;
    
    //Calculate error rate on test data for dimension=1
    Mat classifiedTestLabelsByMahDisPCA = getClassifiedLabelsByMahDis(projectedGrassData, projectedStrawData, projectedTestData);
    int numberOfErrorsInTestDataPCA = getNumberOfErrors(trueTestLabels, classifiedTestLabelsByMahDisPCA);
    cout << "(PCA)Number of Errors in Test data with dimensions reduced to 1: " << numberOfErrorsInTestDataPCA << endl;

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

//1 for Grass, 0 for Straw
Mat getClassifiedLabelsByMahDis(Mat grassData, Mat strawData, Mat samples){
    
    Mat classifiedLabels = Mat::zeros(samples.rows, 1, CV_32FC1);
    
    Mat grassMean, strawMean;
    Mat grassCovar, grassInCovar;
    Mat strawCovar, strawInCovar;
    
    //Calculating covarience matrices for both grass and straw
    //grass
    calcCovarMatrix(grassData, grassCovar, grassMean, CV_COVAR_NORMAL+CV_COVAR_ROWS, -1);
    grassCovar = grassCovar/(grassData.rows-1);
    //straw
    calcCovarMatrix(strawData, strawCovar, strawMean, CV_COVAR_NORMAL+CV_COVAR_ROWS, -1);
    strawCovar = strawCovar/(strawData.rows-1);
    
    //getting inverse covariance matrices for both grass and straw
    invert(grassCovar, grassInCovar, DECOMP_SVD);
    invert(strawCovar, strawInCovar, DECOMP_SVD);
    
    //Classify
    for(int i=0; i<samples.rows; i++){
        double distToGrass = Mahalanobis(samples.row(i), grassMean, grassInCovar);
        double distToStraw = Mahalanobis(samples.row(i), strawMean, strawInCovar);
        
        if(distToGrass<distToStraw){
            classifiedLabels.at<float_t>(i,0) = 1;
        }else{
            classifiedLabels.at<float_t>(i,0) = 0;
        }
    }
    
    return classifiedLabels;
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
