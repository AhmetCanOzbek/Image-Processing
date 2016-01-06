function[cross] = getCross(n)
    %Return a cross shaped(+) structured element
    if( mod(n,2) ~= 1), error('Input must be a poisitive odd integer'); end
    
    cross = zeros(n);
    center = floor(n/2) + 1;
    
    %add 1s
    for i=1:n, 
        cross(center,i) = 1;  
        cross(i,center) = 1;
    end        
end
   
    
    