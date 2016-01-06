function[eulerNumber] = getEulerNumber(inputIm)
    eulerStruct = regionprops(inputIm, 'EulerNumber');
    eulerNumber = eulerStruct.EulerNumber;
end