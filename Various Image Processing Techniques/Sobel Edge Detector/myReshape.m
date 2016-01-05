function [reshaped] = myReshape(array,height, width)

    reshaped(:,:,1) = reshape(array(1:3:size(array,2)),height,width)';
    reshaped(:,:,2) = reshape(array(2:3:size(array,2)),height,width)';
    reshaped(:,:,3) = reshape(array(3:3:size(array,2)),height,width)';
    
    reshaped = uint8(reshaped);
end