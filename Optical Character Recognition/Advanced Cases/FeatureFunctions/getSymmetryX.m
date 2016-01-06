function[symmetryMeasure] = getSymmetryX(inputIm)
    %gives some symmetry measure around the X axis
    inputIm = double(inputIm);
    
    symmetryMeasure = getArea(logical(inputIm)) -...
                      sum(sum(abs(inputIm - flipdim(inputIm,1))));
    
    symmetryMeasure = symmetryMeasure / getArea(inputIm);
end