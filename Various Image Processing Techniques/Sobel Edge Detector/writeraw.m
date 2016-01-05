function count = writeraw(G, filename)
%writeraw - write RAW format grey scale image file 
% Usage :	writeraw(G, filename)
% G:		input image matrix
% filename: file name of the file to write to disk
% count:	return value, the elements written to file

	disp([' Write image data to'  filename ' ...']);

	% Get file ID
	fid = fopen(filename,'wb');

	% Check if file exists
	if (fid == -1)
		error('can not open output image filem press CTRL-C to exit \n');
		pause
    end
	   
    if(ndims(G) == 2)        
        GtoBeWritten = reshape(G',size(G,1)*size(G,2),1);
    end
    
    if(ndims(G) == 3)
        GtoBeWritten = zeros(1,size(G,1)*size(G,2)*size(G,3));
        GtoBeWritten(1:3:end) = reshape(G(:,:,1)',1,size(G,1)*size(G,2)); %red
        GtoBeWritten(2:3:end) = reshape(G(:,:,2)',1,size(G,1)*size(G,2)); %green
        GtoBeWritten(3:3:end) = reshape(G(:,:,3)',1,size(G,1)*size(G,2)); %blue
    end
    
    % Write and close file
	count = fwrite(fid,GtoBeWritten, 'uchar');
	fclose(fid);

	% Transpose again to restore matrix
	%G = G';
end %function