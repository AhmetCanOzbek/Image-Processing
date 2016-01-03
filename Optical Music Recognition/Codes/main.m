function [sound_data] = main(im)
%IF YOU WANT SKEW CORRECTION THEN ENTER 
%want_skewcorr = 1
%want_skewcorr = 0


%PROCEDURE :
%INPUT -> [otsu_threshold] -> [correct_skew] -> [hproj] ->
%[staffline_remove] -> [my_label] -> [create_music] -> Output

%VARIABLES
%"n":avarage staff line thickness 
%"d":avarage distance between staff lines
%1 staff = 5*n + 4*d


%do otsu thresholding
im = otsu_threshold(im);

%correct skew

[im need]= skew_correct(im);
if(need == 1)
im = imclose(im,ones(3,3));
end
figure();imshow(~im);
imwrite(~im,'skewcorrectguzel.png','png');
title('Skew Corrected and Otsu Thresholding done');


%take h projection
%get statistical data about music sheet
[otsu_im,staff_locs,y,n_of_StaffBlocks,n,d] = hproj(im);


%remove the staff lines
[otsu_staffremoved_im] = staffline_remove(otsu_im,staff_locs,n);
if(need==1)
otsu_staffremoved_im = imopen(otsu_staffremoved_im,ones(2,2));
end
figure();imshow(~otsu_staffremoved_im);
title('Staff Lines Removed(called from main())');

%get the data of objects
%put rectangles around objects for visualization
[object object_data how_many_object sound_data] = my_label(otsu_staffremoved_im,y,n_of_StaffBlocks,d);
create_music(sound_data,n_of_StaffBlocks);
disp('number of objects: '); disp(how_many_object);

