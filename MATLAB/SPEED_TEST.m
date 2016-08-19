clc
clear

filename = '2016-08-19_TEST_0.csv';
full_data_array = csvread(filename,1,2)

LogNo = full_data_array(:,1)
TimeStep = full_data_array(:,2)
ControlMode = full_data_array(:,3)
FowardSensor1 = full_data_array(:,4)
FowardSensor2 = full_data_array(:,5)
AltitudeSensor = full_data_array(:,6)
ThrottleControl = full_data_array(:,7)
YawControl = full_data_array(:,8)
RollControl = full_data_array(:,9)
PitchControl = full_data_array(:,10)
StabilityModeControl = full_data_array(:,11)
ErrorP = full_data_array(:,12)
ErrorI = full_data_array(:,13)
ErrorD = full_data_array(:,14)

logCount = 0;
prevSecond = floor(TimeStep(1)/1000);
i = 0;

for time = TimeStep'
     currentSecond = floor(time/1000);
     if(currentSecond == prevSecond)
        logCount = logCount+1;
     else
        i = i+1;
        logCountArray(i) = logCount;
        logCount = 0;
     end
     prevSecond = currentSecond;
end

logCountArray = logCountArray(2:length(logCountArray)-1);
logsPerSecond = mean(logCountArray)



