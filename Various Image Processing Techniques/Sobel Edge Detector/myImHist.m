function[freqs] = myImHist(img)

    if(ndims(img) ~= 2)
       error('Input matrix must be 2 dimensonal'); 
    end
    
    freqs = zeros(256,1);
    
    for i=1:size(img,1)
        for j=1:size(img,2)
            freqs(double(img(i,j))+1) = freqs(double(img(i,j))+1) + 1;
        end
    end   
          
    
end