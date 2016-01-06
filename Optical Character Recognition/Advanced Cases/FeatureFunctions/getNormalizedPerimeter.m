function[normalizedPerimeter] = getNormalizedPerimeter(inputIm)
    normalizedPerimeter = getPerimeter(inputIm) / (2 * (size(inputIm,1) + size(inputIm,2)));
end