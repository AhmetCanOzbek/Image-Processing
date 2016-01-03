function [after_rot,need_for_correction] = skew_correct(im)

size_im = size(im);


for degree = -10:0.1:10

radian = degree * (pi/180);
slope = tan(radian);


 for y = round(size_im(1)/3) : round(size_im(1) - size_im(1) / 3)
    count = 0;
    for x = 1:size_im(2)
      if(round(y+slope*x) == 0), break; end
      if(round(y+slope*x) > size_im(1)), break; end
      
      if (im(round(y+slope*x),x) == 1)
        count = count + 1;
      end    
    end  
    
    i= round((degree + 10)*10  + 1);
    data(i,y) = count;    
 end 
  
end

[maxrun MaxDegreeIndex] = max(max(data'));
disp('maxrun');disp(maxrun);

skew_degree = ((MaxDegreeIndex - 1) / 10) - 10;
disp('skew_degree'); disp(skew_degree);

if(skew_degree < 0.5 && skew_degree > -0.5)
    need_for_correction = 0;
    disp('***No Need for Skew Correction***');
else
    need_for_correction = 1;    
    im = imrotate(im,skew_degree);    
end

after_rot = im;

% imwrite(before_rot,'Mozart2BeforeRot.png','png');
% imwrite(after_rot,'Mozart2AfterRot.png','png');


