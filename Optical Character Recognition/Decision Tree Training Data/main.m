training = imread('training.tif');
%Binarize
bw_training = ~im2bw(training);
%Label different objects with 8 connectivity
[label_training, nOfObjects] = bwlabel(bw_training);


showBoundingBoxes(bw_training, label_training, nOfObjects);

%Get objects and their labels
objectsArray = getObjects(bw_training, label_training, nOfObjects);
getObjectLabels;

%Feature Extraction
featureTitles = {'*','NormalizedArea', 'NormalizedPerimeter', 'AspectRatio',...
                 'Circularity', 'EulerNumber', 'SymmetryY', 'SymmetryX'};

featureFunctions = {@getNormalizedArea, @getNormalizedPerimeter, @getAspectRatio,...
                    @getCircularity, @getEulerNumber, @getSymmetryY, @getSymmetryX};
                
%Create Feature Matrix
numberOfFunctions = max(size(featureFunctions));
featureMatrix = cell(nOfObjects, numberOfFunctions);

for i=1:nOfObjects
    for j=1:numberOfFunctions        
        featureMatrix{i,j} = featureFunctions{j}(objectsArray{i,1});        
    end
end

featureMatrixForDisp = featureMatrix;
%Merge ObjectLabels
featureMatrixForDisp = [objectLabels featureMatrix];
%Merge Feature Titles
featureMatrixForDisp = [featureTitles; featureMatrixForDisp];

predictedLabels = {18,1};
for i=1:18    
    predictedLabels{i,1} = getClass(objectsArray{i,1});    
end

do_OCR(bw_training);


