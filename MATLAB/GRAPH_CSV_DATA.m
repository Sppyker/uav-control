clc
clear

filename = '2016-08-19_TEST_0.csv';
full_data_array = csvread(filename,1,2)


% <LOGNO;TIMESTEP;CONTROLMODE;US_F1;US_F2;US_ALT;CTRL_THROTTLE;CTRL_YAW;CTRL_ROLL;CTRL_PITCH;CTRL_STABILITY_MODE;ErrorP;ErrorI;ErrorD>

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

% Plot values as required

hold all
plot(TimeStep,AltitudeSensor);
plot(TimeStep,ThrottleControl);
plot(TimeStep,ControlMode*3000);
