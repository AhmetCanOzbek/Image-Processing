function[aspectRatio] = getAspectRatio(inputIm)
    %Aspect Ratio = width of BB / height of BB
    inputIm = logical(inputIm);
    aspectRatio = (size(inputIm,1)) / (size(inputIm,2));
end