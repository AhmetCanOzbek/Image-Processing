clear all;
close all;
%%
%Test 1
%Preprocessing
test1 = imread('Test_ideal1.tif');
%RGB to Gray
test1 = rgb2gray(test1); 
%figure();imshow(test1); title('Test 1 Gray Image');
%Otsu Thresholding
test1_bw = ~im2bw(test1, graythresh(test1)); 
figure();imshow(test1_bw);title('Otsu Thresholded Image');
%Opening to get rid of blobs
test1_bw = imopen(test1_bw, getCross(5));
figure();imshow(test1_bw);title('After Opening');
%Closing to close
test1_bw = imclose(test1_bw, ones(6));
figure();imshow(test1_bw);title('After Closing');

%close all;
%do OCR
do_OCR(test1_bw);
%%
%Test 2
%Preprocessing
test2 = imread('Test_ideal2.tif');
figure(); imshow(test2); title('Original Image');
%RGB to Gray
test2 = rgb2gray(test2);
figure(); imshow(test2); title('GrayScale Image');
%Noise removal
test2 = wiener2(test2, [5 5]);
figure(); imshow(test2); title('Noise Removed');
%Otsu Thresholding
test2_bw = ~im2bw(test2, graythresh(test2));
figure(); imshow(test2_bw); title('Binary Image');
%Closing the image
test2_bw = imclose(test2_bw, ones(4));
figure(); imshow(test2_bw); title('Binary Closed Image');
%Get rid of the outer frame
test2_bw = imopen(test2_bw, ones(5,1));
test2_bw = imopen(test2_bw, ones(6));
figure(); imshow(test2_bw); title('Outer Frame Removal');
%Closing the image
test2_bw = imclose(test2_bw, ones(3));
figure(); imshow(test2_bw); title('Binary Closed Image');

%close all;

%do OCR
do_OCR(test2_bw);

%%
