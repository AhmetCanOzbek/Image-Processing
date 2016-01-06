function[circularity] = getCircularity(inputIm)
    inputIm = logical(inputIm);
    
    circularity = (4 * pi * getArea(inputIm)) / (getPerimeter(inputIm)^2);

end