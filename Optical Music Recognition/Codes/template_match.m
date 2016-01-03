function [corr] = template_match(object,template)

dim_obj = size(object);
dim_temp = size(template);

template = imresize(template,[dim_obj(1) dim_obj(2)]);

%subtract
corr = abs(double(object) - double(template));
%normalize
corr = sum(sum(corr)) / (dim_obj(1)*dim_obj(2));
%invert
corr = 1 - corr;