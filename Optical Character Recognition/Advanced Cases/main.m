testNight = imread('Test_Night.tif');
figure(); imshow(testNight); title('Original Image');

%Preprocessing
% %Grey world correction
% testNight = greyWorldCorrect(testNight);
% figure(); imshow(testNight); title('Grey World Correct');
%RGB to Grey
testNight = rgb2gray(testNight);
figure(); imshow(testNight); title('Grey Level Image');
% %Histogram Equalization
% testNight = histeq(testNight);
% figure(); imshow(testNight); title('Histogram Equalized');
% %Noise Removal
% testNight = wiener2(testNight);
% figure(); imshow(testNight); title('Noise Removal');

% %Otsu Threhsolding
% testNight_bw_otsu = im2bw(testNight, graythresh(testNight));
% %reversing the image so character pixels become '1' and background '0'
% testNight_bw_otsu = ~testNight_bw_otsu;
% figure(); imshow(testNight_bw_otsu); title('Otsu Thresholding');

%Sauvola Local Threhsolding
testNight_bw_sauvola = sauvola(testNight);
%reversing the image so character pixels become '1' and background '0'
testNight_bw_sauvola = ~testNight_bw_sauvola;
figure(); imshow(testNight_bw_sauvola); title('Sauvola Local Image Thresholding');

%Close the image to make characters more compact
testNight_bw_sauvola = imclose(testNight_bw_sauvola, ones(5));
figure(); imshow(testNight_bw_sauvola); title('Closed Image');

%Open the image to get rid of small pieces
testNight_bw_sauvola = imopen(testNight_bw_sauvola, getCross(3));
figure(); imshow(testNight_bw_sauvola); title('Opened Image');

%Do the OCR
do_OCR(testNight_bw_sauvola);