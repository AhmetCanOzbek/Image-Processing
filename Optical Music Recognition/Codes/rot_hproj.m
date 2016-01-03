function [] = rot_hproj(im,degree1,degree2)
im = ~im;
dim_im = size(im);
count = 0;


for degree= degree1:degree2

radian = degree * (pi/180);
slope = tan(radian);

 for y = 1:dim_im(1)    
    for x = 1:dim_im(2)
        
        if((round(y+slope*x)<1))
            continue;
        end
        
      if (im(round(y+slope*x),x) == 1)
        count = count + 1;
      end    
    end  
    
    data(y) = count;
    count = 0;
    
 end
 
figure(); stem(data,'marker','none');
str = sprintf('Degree : %d',degree);
title(str); 
 
end
 