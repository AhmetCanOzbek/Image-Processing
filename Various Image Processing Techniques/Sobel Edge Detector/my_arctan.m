function [out_angle] = my_arctan(x,y)
%angle in degrees

if( x>0 && y > 0 )    
    out_angle = (atan(y/x) / pi) * 180;
end
if( x<0 && y > 0 )    
    out_angle = (atan(y/x) / pi) * 180 + 180;
end
if( x>0 && y < 0 )    
    out_angle = (atan(y/x) / pi) * 180 + 360;
end
if( x<0 && y < 0 )    
    out_angle = (atan(y/x) / pi) * 180 + 180;
end
%%%
if( x==0 && y > 0 )    
    out_angle =  90;
end

if( x==0 && y < 0 )    
    out_angle = 270;
end

if( x>0 && y == 0 )    
    out_angle = 0;
end

if( x<0 && y == 0 )    
    out_angle = 180;
end

if( x==0 && y == 0 )    
    out_angle = 0;
end
