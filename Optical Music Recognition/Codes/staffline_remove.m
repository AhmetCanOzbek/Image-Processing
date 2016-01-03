function [out_im] = staffline_remove(out_im,staff_locs,avg_StaffLineThickness)
%Removes the staff lines from the music sheet

n = avg_StaffLineThickness;
dim_im = size(out_im);

for i=1:max(size(staff_locs))
    for j=1:dim_im(2)
        [thickness,vector] = compute_thickness(out_im,staff_locs(i),j);
        
        if( thickness < 1.5*n  && thickness>0)
            
            for row = 1:max(size(vector))
                out_im(vector(row),j) = 0;
            end
            
        end   
    end
end

%sum filter for fixing after staff line removal
%out_im = imfilter(out_im,[1 1]);


end

function [thickness,total_vector] = compute_thickness(out_im,staff_loc,j)
u = staff_loc;
d = staff_loc;
dim_im = size(out_im);
    
if(out_im(staff_loc,j) == 1)
    
    while(out_im(u,j) == 1)        
      up_vector((staff_loc+1)-u) = u;
      u = u-1;        
    end
    
    while(out_im(d,j) == 1)        
      down_vector(d-(staff_loc-1)) = d;
      d = d+1;        
    end    
         
     up_vector = fliplr(up_vector);  
     total_vector = union(up_vector,down_vector);
     thickness = max(size(total_vector)); 
            
else 
    thickness = 0;
    up_vector = 0;
    down_vector = 0;
    total_vector = 0;
end

end
