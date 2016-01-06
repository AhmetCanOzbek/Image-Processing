function[symmetryMeasure] = getSymmetryY(inputIm)
    %gives some symmetry measure around the Y axis
    inputIm = double(inputIm);
    
    symmetryMeasure = getArea(logical(inputIm)) -...
                      sum(sum(abs(inputIm - flipdim(inputIm,2))));
    
    symmetryMeasure = symmetryMeasure / getArea(inputIm);
end