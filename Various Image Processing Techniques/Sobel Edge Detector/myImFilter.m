function[output_im] = myImFilter(im,h)

%size of the image
[m n] = size(im);
%fs = filter size
[fsm fsn] = size(h);
%flipped h
hf = rot90(h,2);

%zero padding
im = padarray(im, [fsm-1 fsn-1]);

output_im = zeros(m + (fsm -1) , n + (fsn -1));
im = double(im);

for i=1:m + (fsm-1)
    for j = 1:n + (fsn-1)             
        
       output_im(i,j) = sum(sum( im(i:i+(fsm-1) , j:j+(fsn-1)).*hf ));
        
    end
end

%crop unnecessary part
output_im = output_im(2:end-1,2:end-1);

end