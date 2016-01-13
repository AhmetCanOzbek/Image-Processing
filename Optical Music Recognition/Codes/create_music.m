function [] = create_music(sound_data,n_of_StaffBlocks)

dim_sound = size(sound_data);
full_music = [];

for i=1:dim_sound(1)
    for j = 1:dim_sound(2)        
        %note
        note = get_pitch_name(sound_data(i,j,1));
        %duration
        template_number = sound_data(i,j,2);
        duration = template2duration(template_number);
        
        %***create sound***        
        if((note~='x') & (duration~=0))
            full_music = [full_music ksPlayNote(note,duration,44100)'];
            %pause(duration);
        end          
    end
end
wavwrite(full_music, 44100, 'jingle_ks.wav');

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

function [duration] = template2duration(number)

duration = 0;
if(number == 1 || number==2 ), duration = 0.25; end %quarter
if(number == 3 || number==4 ), duration = 0.5; end %half
if(number == 5 || number==9), duration = 1; end %whole
if(number == 6), duration = 0.125; end %eight

end