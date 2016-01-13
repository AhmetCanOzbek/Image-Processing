function[soundVector] = ksPlayNote(note,duration,Fs)
switch note
    case 'C3'
        f=130.81;
    case 'C#3'
        f=138.59;
    case 'D3'
        f=146.83;
    case 'D#3'
        f=155.56;
    case 'E3'
        f=164.81;
    case 'F3'
        f=174.61;
    case 'F#3'
        f=185.00;
    case 'G3'
        f=196.00;
    case 'G#3'
        f=207.65;
    case 'A3'
        f=220.00;
    case 'A#3'
        f=233.08;
    case 'B3'
        f=246.94;
    case 'C4'
        f=261.63;
    case 'C#4'
        f=277.18;
    case 'D4'
        f=293.66;
    case 'D#4'
        f=311.13;
    case 'E4'
        f=329.63;
    case 'F4'
        f=349.23;
    case 'F#4'
        f=369.99;
    case 'G4'
        f=392.00;
    case 'G#4'
        f=415.30;
    case 'A4'
        f=440.00;
    case 'A#4'
        f=466.16;
    case 'B4'
        f=493.88;
    case 'C5'
        f=523.25;
    case 'C#5'
        f=554.37;
    case 'D5'
        f=587.33;
    case 'D#5'
        f=622.25;
    case 'E5'
        f=659.26;
    case 'F5'
        f=698.46;
    case 'F#5'
        f=739.99;
    case 'G5'
        f=783.99;
    case 'G#5'
        f=830.61;
    case 'A5'
        f=880.00;
    case 'A#5'
        f=932.33;
    case 'B5'
        f=987.77;
    case 'p'
        f=000.00;
    otherwise
        error('%s is not a recognized note.',note)
end

delayLineLength = round(Fs / f);
initialRandomWaveTable = rand(delayLineLength,1);

soundVector = zeros(round(duration * Fs) , 1);
soundVector(1:delayLineLength,1) = initialRandomWaveTable;

for i=delayLineLength+1:length(soundVector)    
    soundVector(i) = 0.5 * (soundVector(i-delayLineLength+1) + soundVector(i-delayLineLength));    
end

%Normalizing the output to -1 and +1
soundVector = soundVector-mean(soundVector);
soundVector = soundVector/max(abs(soundVector));

sound(soundVector,Fs);
end