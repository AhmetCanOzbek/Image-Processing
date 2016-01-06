function[perimeter] = getPerimeter(inputIm)
    inputIm = logical(inputIm);
    structPerimeter = regionprops(inputIm, 'Perimeter');
    perimeter = structPerimeter.Perimeter;
end