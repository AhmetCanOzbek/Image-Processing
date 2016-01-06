function[objectsArray] = getObjects(inputIm, labelIm, numberOfObjects)
    %inputIm: Binary image
    %labelIm: Labeled Objects Image
    %numberOfObjects: Number of Objects labeled
    %
    %Returns: A cell array containing the objects cropped from the input
    %binary image
    
    %Initialize the cell array containing the objects
    objectsArray = cell(numberOfObjects,1);
    
    for i=1:numberOfObjects       
        [x y w h] = getLocOfObject(labelIm, i);
        %crop from the image
        objectsArray{i,1} = inputIm(y:y+h, x:x+w);         
    end
end

function[x y w h] = getLocOfObject(labelIm, labelNumber)
    %labelIm: Labeled objects image
    %labelNumber: Label Number of The object
    %
    %Return: x(X position), y(Y position), 
    %        w(Width of Object), h(Height of Object)
    
    [r, c] = find(labelIm == labelNumber);
    x = min(c);
    y = min(r);
    w = max(c) - min(c);
    h = max(r) - min(r);
end