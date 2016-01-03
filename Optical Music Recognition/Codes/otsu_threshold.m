function [im] = otsu_threshold(im)

%input check
[~, dim] = size(size(im));
if(dim == 3)
im = rgb2gray(im);
end
%%%
%thresholding with Otsu's method
if(isa(im,'uint8'))
otsu_level = graythresh(im);
im = im2bw(im,otsu_level);
end

im = ~im;