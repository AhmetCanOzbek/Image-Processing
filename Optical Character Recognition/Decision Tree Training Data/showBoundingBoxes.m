function[] = showBoundingBoxes(inputIm, labelIm, numIm)
    imshow(inputIm);
    for i=1:numIm        
        [r c] = find(labelIm == i);
        xPos = min(c);
        yPos = min(r);
        width = max(c) - min(c);
        height = max(r) - min(r);
        %Bounding box and Label number
        rectangle('Position', [xPos,yPos,width,height], 'edgecolor', 'Red');
        text(xPos-5, yPos-5, num2str(i), 'color', 'red');
    end
end