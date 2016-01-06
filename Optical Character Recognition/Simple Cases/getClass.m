function[objectLabels] = getClass(input)  
    
    if(getEulerNumber(input) == 1)
        if(getAspectRatio(input) > 3.5)
            objectLabels = {'I'};
            return;
        end
        
        %Symmetry High
        %It is whether 'T' or 'M'
        if(getSymmetryY(input) > 0.9)            
            if(getSymmetryX(input) > 0.33)
                objectLabels = {'M'};
                return;
            end
            if(getSymmetryX(input) < 0.33)
                objectLabels = {'T'};
                return;
            end
        end
        
        %Perimeter Low
        %It is whether '1', 'L', '7'
        if(getNormalizedPerimeter(input) < 1.15)
            %Aspect Ratio
            if(getAspectRatio(input) > 1.75)
                objectLabels = {'1'};
                return
            else
                %SymmetryX
                if(getSymmetryX(input) > 0)                    
                    objectLabels = {'L'};
                    return;
                else                    
                    objectLabels = {'7'};
                    return;
                end               
            end
            
        end
        
        
        %Perimeter High
        %It is whether 'S', '2', 'E', '3', '5'
        if(getNormalizedPerimeter(input) > 1.15)            
            if(getSymmetryX(input) > 0.75)
                objectLabels = {'E'};
                return;
            end
            
            %SymmetryX high
            if(getSymmetryX(input) >= 0.25)
                %Whether 'S' or '3'
                if(getSymmetryX(input) > 0.47)
                    objectLabels = {'3'};
                    return;
                end                
                if(getSymmetryX(input) < 0.47)
                    objectLabels = {'S'};
                    return;
                end               
            end           
            %SymmetryX low
            if(getSymmetryX(input) < 0.25)
                %Whether '5' or '2'
                if(getSymmetryY(input) >= 0.47)
                    objectLabels = {'5'};
                    return;
                end                
                if(getSymmetryY(input) < 0.47)
                    objectLabels = {'2'};
                    return;
                end                            
            end              
        end       
    end
    
    
    
    if(getEulerNumber(input) == 0)
        if(getSymmetryY(input) > 0.9)
            objectLabels = {'0'};
            return;
        end            
        if(getSymmetryY(input) < 0.2)
            objectLabels = {'4'};
            return;
        end
        if(getSymmetryX(input) > 0.9)
            objectLabels = {'D'};
            return;
        end
        if(getSymmetryX(input) < 0.3)
            objectLabels = {'P'};
            return;
        end
        %Distinguish between '6' and '9'
        %Use hole-filling and look at the center of mass in Y axis
        if(getCenter(imfill(input,'holes')) < 0.5 )
            objectLabels = {'9'};
            return;
        end
        if(getCenter(imfill(input,'holes')) > 0.5 )
            objectLabels = {'6'};
            return;
        end        
    end
    
    
    
    if(getEulerNumber(input) == -1)
        objectLabels = {'8'};
        return;
    end 
    

end