function[normalizedArea] = getNormalizedArea(inputIm)       
    normalizedArea = getArea(inputIm) / (size(inputIm,1) * (size(inputIm,2)));      
end