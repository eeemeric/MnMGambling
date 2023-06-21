function [s] =  SerialPortCommunicationMnM_Gambling(comArduino)%%
if ~nargin
    prts = serialportlist("all")
    comArduino = prts(1);
end
s = serialport(comArduino,9600,'Timeout',5);
configureTerminator(s,"LF")
configureCallback(s,"terminator",@readSerialData)
end

function readSerialData(src,evt)
    data = readline(src);
    disp(data)
    src.UserData = data;
end
