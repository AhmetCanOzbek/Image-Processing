function [im,staff_locs,y,n_of_StaffBlocks,avg_StaffLineThickness,avg_StaffSpacing] = hproj(im)
%Takes the horizonal projection
%Gives us statistical data about the music sheet


[m n] = size(im);
hproj = zeros(m,1);
%finding horizontal projections
for i=1:m
    for j = 1:n
        hproj(i,1) = hproj(i,1) + im(i,j);        
    end    
end
figure();stem(hproj,'marker','none');

staff_locs = find(hproj>max(hproj/3)); %burda openingle olan kesi?imini de ald?rabilirsin

StaffPixelN=1;StaffLineN=1;StaffBlockN=1; 
y(StaffBlockN, StaffLineN, StaffPixelN) = staff_locs(1);
approx_staffspacing= 9999;
max_pixelwidth = 0;
for i=2:size(staff_locs)    
    if(staff_locs(i) - staff_locs(i-1) == 1)
        StaffPixelN = StaffPixelN + 1;
        if(StaffPixelN > max_pixelwidth), max_pixelwidth=StaffPixelN; end
    end    
    if(staff_locs(i) - staff_locs(i-1) > 1  && staff_locs(i) - staff_locs(i-1)<2*approx_staffspacing)
        StaffLineN = StaffLineN + 1;
        approx_staffspacing = staff_locs(i) - staff_locs(i-1) ;
        StaffPixelN = 1;
    end   
    if(staff_locs(i) - staff_locs(i-1) > 3*approx_staffspacing)
        StaffBlockN = StaffBlockN + 1;
        StaffPixelN = 1;
        StaffLineN = 1;
    end       
    y(StaffBlockN, StaffLineN, StaffPixelN) = staff_locs(i);
end
n_of_StaffBlocks = StaffBlockN;
disp('**********Statisctics of The Music Sheet:**********');
disp('***Number of Staff Blocks:');disp(n_of_StaffBlocks);
dim_y = size(y); n_of_StaffLines = dim_y(1)*dim_y(2);
disp('***Number of Staff Lines:');disp(n_of_StaffLines);

%avarage staff line thickness
avg_StaffLineThickness = size(staff_locs) / n_of_StaffLines;
avg_StaffLineThickness = avg_StaffLineThickness(1,1);
disp('***Avarage staff line thickness(n):');disp(avg_StaffLineThickness);

%avarage distance between staff lines
for i=1:n_of_StaffBlocks 
    for j = 1:n_of_StaffLines / n_of_StaffBlocks -1   
        d_StaffLines(i,j) = y(i,j+1,1) - y(i,j,nnz(y(i,j,:)));             
    end    
end
avg_StaffSpacing = mean(mean(d_StaffLines));
disp('***Avarage distance between staff lines(d):');disp(avg_StaffSpacing);

%avarage distance between the staffs
LinesPerStaff = n_of_StaffLines / n_of_StaffBlocks;

if (n_of_StaffBlocks ~= 1) 
    
for i=1:n_of_StaffBlocks-1              
   d_Staffs(i) = y(i+1,1,1) - y(i,LinesPerStaff,nnz(y(i,LinesPerStaff,:)));             
end
avg_StaffDistance = mean(mean(d_Staffs));
disp('***Avarage distance between staffs:');disp(avg_StaffDistance);

else    
    disp('***Avarage distance between staffs:');disp('None');    
end
disp('-------------------------------------------');









