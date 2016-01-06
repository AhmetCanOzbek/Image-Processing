function[outIm] = greyWorldCorrect(inputIm)
    %Input must be RGB
    if(ndims(inputIm) ~= 3)
        error('Input must be three dimensional');
    end
    
    [m,n,dummy]=size(inputIm);
    Rmean      = sum(sum(inputIm(:,:,1)))/(m*n);
    Gmean      = sum(sum(inputIm(:,:,2)))/(m*n);
    Bmean      = sum(sum(inputIm(:,:,3)))/(m*n);
    Avg        = (Rmean + Gmean + Bmean) / 3;
    Kr         = Avg/Rmean;
    Kg         = Avg/Gmean;
    Kb         = Avg/Bmean;
    outIm(:,:,1) = Kr*double(inputIm(:,:,1));
    outIm(:,:,2) = Kg*double(inputIm(:,:,2));
    outIm(:,:,3) = Kb*double(inputIm(:,:,3));
    outIm = uint8(outIm);



end