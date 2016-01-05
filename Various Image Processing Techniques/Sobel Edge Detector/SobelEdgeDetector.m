%Ahmet Can Ozbek
%Sobel Edge Detector and Non Maximal Suppression
%Sobel Edge Detector

sobelX = (1/4) * [-1 0 1; -2 0 2; -1 0 1];
sobelY = (1/4) * [-1 -2 -1; 0 0 0; 1 2 1];

%% 1.
%To get either Farm or Cougar outputs, just change the imageName below
imageName = 'Farm';
fileName = strcat(imageName,'.raw');
img = myReshape(readraw(fileName),481,321);

%Convert to grayscale
redCoeff=0.21;
greenCoeff=0.72;
blueCoeff=0.07;
grayImg = zeros(size(img,1), size(img,2));

h = waitbar(0, 'Gray Level Image Getting Constructed');
for i=1:size(img,1)
    for j=1:size(img,2)
            grayImg(i,j) = img(i,j,1)*redCoeff + img(i,j,2)*greenCoeff + img(i,j,3)*blueCoeff;
    end
    waitbar(i/size(img,1), h); 
end
close(h);

%Apply sobel, get gradient
%Apply Sobel, Get Gx and Gy
Gx = double(myImFilter(double(grayImg), sobelX));
Gy = double(myImFilter(double(grayImg), sobelY));

%Calculate Gradient Magnitude
gradientMagMap = zeros(size(Gx,1),size(Gx,2));
for i=1:size(gradientMagMap,1)
    for j=1:size(gradientMagMap,2)
        gradientMagMap(i,j) = Gx(i,j)^2 + Gy(i,j)^2;        
    end
end
%gradientMagMap = Gx.^2 + Gy.^2;

%Scale Gradient Magnitude to 0-255  ( (([] - min) / (max-min)) * 255 )
minV = min(min(gradientMagMap));
maxV = max(max(gradientMagMap));
scaledGradientMagMap = ((gradientMagMap - minV) / (maxV-minV)) * 255;
scaledGradientMagMap = uint8(scaledGradientMagMap);
figure('name',strcat(imageName,'_','Gradient Magnitude Map'));imshow(scaledGradientMagMap);title('Gradient Magnitude Map');
writeraw(scaledGradientMagMap, strcat(imageName,'_','Gradient Magnitude Map' , '.raw'));


%% 2.
%Choosing proper thresholds %10 %15
[freq] = myImHist(scaledGradientMagMap);
threshold10 = 0.1;
sum = 0; i10=0;
while(sum < (1-threshold10)*size(img,1)*size(img,2))
    i10 = i10+1;
    sum = sum + freq(i10); 
end
thresholdIntensity10 = i10;

threshold15 = 0.15;
sum = 0; i15=0;
while(sum < (1-threshold15)*size(img,1)*size(img,2))
    i15 = i15+1;
    sum = sum + freq(i15);    
end
thresholdIntensity15 = i15;

%10percent
edgePoints10 = (scaledGradientMagMap > thresholdIntensity10);
figure('name',strcat(imageName,'_','10 Percent')); imshow(~edgePoints10); title('10 Percent');
writeraw(double(edgePoints10)*255, strcat(imageName,'_','10 Percent' , '.raw') );
%15percent
edgePoints15 = (scaledGradientMagMap > thresholdIntensity15);
figure('name',strcat(imageName,'_','15 Percent')); imshow(~edgePoints15); title('15 Percent');
writeraw(double(edgePoints15)*255, strcat(imageName,'_','15 Percent' , '.raw') );


%% 3.
%Apply non-maximal-supression
M = scaledGradientMagMap;
nonMaxM = M;
dx = Gx;
dy = Gy;
for i = 2:size(grayImg,1)-1
    for j = 2:size(grayImg,2)-1
        %finding the direction of the gradient vector
        %and rounding it to the closest 8 direction
        angle = my_arctan(dx(i,j),dy(i,j));
        direction = mod(round(angle/45),4);
        
        %along horizontal
       if (direction == 0)
           if ( (M(i,j)<M(i,j+1)) ||  (M(i,j)<M(i,j-1)) )
               nonMaxM(i,j) = 0;
           end
       end       
       %along NE
       if (direction == 1)
           if ( (M(i,j)<M(i+1,j+1)) ||  (M(i,j)<M(i-1,j-1)) )
               nonMaxM(i,j) = 0;
           end           
       end       
       %along vertical
       if (direction == 2)
           if ( (M(i,j)<M(i+1,j)) ||  (M(i,j)<M(i-1,j)) )
               nonMaxM(i,j) = 0;
           end           
       end       
       %along NW
       if (direction == 3)
           if ( (M(i,j)<M(i+1,j-1)) ||  (M(i,j)<M(i-1,j+1)) )
               nonMaxM(i,j) = 0;
           end           
       end        
    end    
end

%M has become thinned
%Choosing proper thresholds %10 %15
[freq intensity] = imhist(nonMaxM);
threshold10 = 0.1;
sum = 0; i10=0;
while(sum < (1-threshold10)*size(img,1)*size(img,2))
    i10 = i10+1;
    sum = sum + freq(i10); 
end
thresholdIntensity10 = i10;

threshold15 = 0.15;
sum = 0; i15=0;
while(sum < (1-threshold15)*size(img,1)*size(img,2))
    i15 = i15+1;
    sum = sum + freq(i15);    
end
thresholdIntensity15 = i15;

%10percent
nonMaxEdgePoints10 = (nonMaxM > thresholdIntensity10);
figure('name',strcat(imageName,'_','Non Max 10 Percent')); imshow(~nonMaxEdgePoints10); title('Non Max 10 Percent');
writeraw(double(nonMaxEdgePoints10)*255, strcat(imageName,'_','Non Max 10 Percent' , '.raw') );
%15percent
nonMaxEdgePoints15 = (nonMaxM > thresholdIntensity15);
figure('name',strcat(imageName,'_','Non Max 15 Percent')); imshow(~nonMaxEdgePoints15); title('Non Max 15 Percent');
writeraw(double(nonMaxEdgePoints15)*255, strcat(imageName,'_','Non Max 15 Percent' , '.raw') );
% figure();imshow(uint8(nonMaxM),[]);
% title('thinned edge image');


%%

