function[centerInY] =  getCenter(input)
    input = logical(input);
    yLoc = 0;
    counter = 0;
    for i=1:size(input,1)
        for j=1:size(input,2)            
            if(input(i,j) == 1)
                yLoc = yLoc + i;
                counter = counter + 1;
            end            
        end
    end
    centerInY = (yLoc / counter) / size(input,1);
end