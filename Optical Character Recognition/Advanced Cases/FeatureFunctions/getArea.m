function[area] = getArea(inputIm)
    inputIm = logical(inputIm);
    area = 0;
    for i=1:size(inputIm,1)
        for j=1:size(inputIm,2)
            if(inputIm(i,j) == 1)
                area = area + 1;
            end
        end
    end
end