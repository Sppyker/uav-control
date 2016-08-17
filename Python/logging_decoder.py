import minipack

input_file = open('data2.txt')

miniinput = minipack.MinipackInput()

data_line = ''

logNo = []
timeStep = []
controlMode = []
forwardSensor1 = []
forwardSensor2 = []
AltitudeSensor = []
throttleControl = []
yawControl = []
rollControl = []
pitchControl = []
stablilityModeControl = []
errorP = []
errorI = []
errorD = []

for line in input_file:
    if line[0] == '(':
        data_line = line
        
array_no = 1

if (data_line == ''):
    print('Data line not found!')

for c in data_line:
    packet_length = miniinput.Give(c)
    if (packet_length != 0):
        # Run Unpacking Code Here          
        logNo.append(miniinput.Unpack(2))
        timeStep.append(miniinput.Unpack(4))
        controlMode.append(miniinput.Unpack(1))
        forwardSensor1.append(miniinput.UnpackFloat())
        forwardSensor2.append(miniinput.UnpackFloat())
        AltitudeSensor.append(miniinput.UnpackFloat())
        throttleControl.append(miniinput.Unpack(2))
        yawControl.append(miniinput.Unpack(2))
        rollControl.append(miniinput.Unpack(2))
        pitchControl.append(miniinput.Unpack(2))
        stablilityModeControl.append(miniinput.Unpack(2))
        errorP.append(miniinput.UnpackFloat())
        errorI.append(miniinput.UnpackFloat())
        errorD.append(miniinput.UnpackFloat())
        error = miniinput.UnpackError()
        array_no += 1
        
        if (error):
            print("Error in pack %d" % array_no)
