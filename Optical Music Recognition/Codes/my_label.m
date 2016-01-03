function [object object_data how_many_object sound_data] = my_label(out_im,y,n_of_StaffBlocks,avg_StaffSpacing)
%returns the number, locations and sizes of objects
%puts rectangles around objects for visualization

%object_data
%column 1-4 -> left top width height
%column 5 -> template number (duration)
%column 6 -> which staff
%column 7 -> order in the staff from left to right
%column 8 -> pitch number code

%***pitch coding*** -> first digit:pitch value, second digit:octave number


dim_im = size(out_im);

[labeled o_num] = bwlabel(out_im,8);
how_many_object = o_num;

figure();imshow(~out_im);
title('Staff Lines Removed and Objects Labeled (called from mylabel())');

for o = 1:o_num
[r, c] = find(labeled==o);
top(o) = min(r); left(o) = min(c);
right(o) = max(c);bottom(o) = max(r);
width(o) = right(o) - left(o); height(o) = bottom(o) - top(o);
hold on
h = rectangle('Position',[left(o) top(o) width(o)+1 height(o)+1]);
set(h, 'EdgeColor', [1, 0, 0]) ;

% htext = text(left(o)-4,top(o)-4,num2str(o));
% set(htext,'FontSize',10)

object_data = [left'  top'  width' height'];
end


%***Template Matching***

%read the templates
import_templates();

%perform template matching for each object
for o_number =1:how_many_object

%get the object data
obj_left = object_data(o_number,1); obj_top = object_data(o_number,2);
obj_width = object_data(o_number,3); obj_height = object_data(o_number,4);
%cut the ojbject from image
cutted_obj = out_im(obj_top:obj_top+obj_height,obj_left:obj_left+obj_width);

object{o_number} = cutted_obj;

   for i=1:how_many_template       
       corr(i) = template_match(cutted_obj,~t{i});      
   end   
   [~,matched_temp_number] = max(corr);
   %insert the type of object into object data
   object_data(o_number,5) = matched_temp_number;
   
htext = text(obj_left,obj_top-avg_StaffSpacing*(5/3),get_template_name(matched_temp_number));
set(htext,'FontSize',8);

end



[object_data] = sort_objects(object,object_data,how_many_object,y,n_of_StaffBlocks,avg_StaffSpacing,dim_im);
[object_data] = find_pitches(object,object_data,how_many_object,y,n_of_StaffBlocks,avg_StaffSpacing,dim_im);
[sound_data] = create_sound_data(object_data,n_of_StaffBlocks,how_many_object);

for o_number =1:how_many_object
%get the object data
obj_left = object_data(o_number,1); obj_top = object_data(o_number,2);
obj_width = object_data(o_number,3); obj_height = object_data(o_number,4);
htext3 = text(obj_left,obj_top-avg_StaffSpacing*(2/3),get_pitch_name(object_data(o_number,8)));
set(htext3,'FontSize',10);
end


end

function[object_data] = find_pitches(object,object_data,how_many_object,y,n_of_StaffBlocks,avg_StaffSpacing,dim_im)
%7 8 11 12

for o=1:how_many_object    
    
     %finding pitches for quarter notes
     if((object_data(o,5)) == 1 || (object_data(o,5) == 2))          
        maxloc = find_maxrunloc(object{o}) + object_data(o,2);   
        object_data(o,8) = give_pitchvalue(maxloc,sum(y(object_data(o,6),:,1))/5,avg_StaffSpacing);         
     end 
    
     %finding pitches for whole notes
     if((object_data(o,5)) == 5 || (object_data(o,5)) == 9)          
        object_data(o,8) = give_pitchvalue(object_data(o,2) + (object_data(o,4)/2),sum(y(object_data(o,6),:,1))/5,avg_StaffSpacing);         
     end 
     
     %finding pitches for half notes
     if((object_data(o,5)) == 3 || (object_data(o,5) == 10))     
        fixedobject{o} = imfilter(object{o},[1 1 1 1]);
        %fill the hole
        fixedobject{o} = imfill(fixedobject{o},'holes');
        maxloc = find_maxrunloc(fixedobject{o}) + object_data(o,2);   
        object_data(o,8) = give_pitchvalue(maxloc,sum(y(object_data(o,6),:,1))/5,avg_StaffSpacing);         
     end      
     
end

end


function [sound_data] = create_sound_data(object_data,n_of_StaffBlocks,how_many_object)
%sound_data
%first column: pitch code number, duration(template)

for i=1:n_of_StaffBlocks
    for j = 1:100
        for o=1:how_many_object
            if(object_data(o,5) ~= 7 && object_data(o,5) ~= 8 && object_data(o,5) ~= 11 && object_data(o,5) ~= 12)
                
              if(object_data(o,6) == i && object_data(o,7) == j )
                
              sound_data(i,j,1) = object_data(o,8); %pitch number code 
              sound_data(i,j,2) = object_data(o,5); %template number(duration)
                
              end
            
            end
        end   
    end
end




end

function [pitch] = give_pitchvalue(max_loc,staffcenter,avg_StaffSpacing)
%pitch coding
%first digit:pitch
%second digit:octave number
%A-1,B-2,C-3,D-4,E-5,F-6,G-7

% disp('max_loc');disp(max_loc);
% disp('staffcenter');disp(staffcenter);
% disp('avg_StaffSpacing');disp(avg_StaffSpacing);
distance = (staffcenter - max_loc) / avg_StaffSpacing;

pitch = 0;

if((distance > -4)  & (distance < -3) ),pitch = 23; end    %B3
if(distance > -3.5  & distance < -2.5 ),pitch = 34; end%C4
if(distance > -3  & distance < -2 ),pitch = 44; end %D4
if(distance > -2.5  & distance < -1.5 ),pitch = 54; end %E4
if(distance > -2  & distance < -1 ),pitch = 64; end %F4
if(distance > -1.5  & distance < -0.5 ),pitch = 74; end %G4
if(distance > -1  & distance < -0.5 ),pitch = 14; end %A4
if(distance > -0.5  & distance < 0.5 ),pitch = 24; end %B4
if(distance > 0  & distance < 1 ),pitch = 35; end %C5
if(distance > 0.5  & distance < 1.5 ),pitch = 45; end %D5
if(distance > 1  & distance < 2 ),pitch = 55; end %E5
if(distance > 1.5  & distance < 2.5 ),pitch = 65; end %F5
if(distance > 2  & distance < 3 ),pitch = 75; end %G5
if(distance > 2.5  & distance < 3.5 ),pitch = 15; end %A5
if(distance > 3  & distance < 4 ),pitch = 25; end %B5


end

function [str] = get_pitch_name(pitch)

str = 'x';
if(pitch==23), str = 'B3'; end
if(pitch==34), str = 'C4'; end
if(pitch==44), str = 'D4'; end
if(pitch==54), str = 'E4'; end
if(pitch==64), str = 'F4'; end
if(pitch==74), str = 'G4'; end
if(pitch==14), str = 'A4'; end
if(pitch==24), str = 'B4'; end
if(pitch==35), str = 'C5'; end
if(pitch==45), str = 'D5'; end
if(pitch==55), str = 'E5'; end
if(pitch==65), str = 'F5'; end
if(pitch==75), str = 'G5'; end
if(pitch==15), str = 'A5'; end
if(pitch==25), str = 'B5'; end

end

function [max_loc] = find_maxrunloc(obj)

dim_obj = size(obj);
hprojvalue = zeros(dim_obj(1),1);
for i=1:dim_obj(1)
    for j=1:dim_obj(2)        
        hprojvalue(i,1) = hprojvalue(i,1) + obj(i,j);        
    end
end

[dummy max_loc] = max(hprojvalue);

end

function [object_data] = sort_objects(object,object_data,how_many_object,y,n_of_StaffBlocks,avg_StaffSpacing,dim_im)

a = 1;
for i=1:n_of_StaffBlocks
    staffcenter(i) = sum(y(i,:,1))/5;
    
    for o = 1:how_many_object
        
        if( abs((object_data(o,2)+object_data(o,3)/2)- staffcenter(i)) < 4.5*avg_StaffSpacing )        
            object_data(o,6) = i;             
        end          
    end    
end


for i=1:n_of_StaffBlocks
for o = 1:how_many_object
  if(object_data(o,6) == i)
      
      for j = 1:dim_im(2)          
       if(object_data(o,1) == j)
           object_data(o,7) = a;
           a = a + 1;                     
       end      
      end  
  end
end
a = 1;
end

end

function[str] = get_template_name(number)

if(number==1)
    str = 'quarter';
elseif(number==2)
    str = 'quarter';
elseif(number==3)
    str = 'half';
elseif(number==4)
    str = 'half';
elseif(number==5)
    str = 'whole';
elseif(number==6)
    str = 'eight';
elseif(number==7)
     str = 'gclef';
elseif(number==8)
    str = 'bar';    
elseif(number==9)
    str = 'whole';
elseif(number==10)
    str = 'half';
elseif(number==11)
    str = 'sharp';
elseif(number==12)
    str = 'fclef';
 
end


end


