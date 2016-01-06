function[] = do_OCR(inputIm)
    
    [labelIm, numIm] = bwlabel(inputIm);  
    %Get characters
    characters = getObjects(inputIm, labelIm, numIm);
    figure(); imshow(inputIm);    
    
    for i=1:numIm        
        [r c] = find(labelIm == i);
        xPos = min(c);
        yPos = min(r);
        width = max(c) - min(c);
        height = max(r) - min(r);
        %Bounding box and Label number
        if(width > 0 && height>0)            
            rectangle('Position', [xPos,yPos,width,height], 'edgecolor', 'Red');
            fontSize = 16;
            text(xPos-(fontSize/1.8), yPos-(fontSize/1.8), getClass(characters{i,1}),... 
            'color', 'red','fontsize', fontSize, 'fontweight', 'bold');
        end
    end
    title('OCR Result');

end