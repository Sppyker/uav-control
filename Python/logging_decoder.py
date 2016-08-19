import minipack
import sys
import os
import csv
import datetime

# Import from dragged in text file

# Else ask for local file name

# Then use that as input
try:
    file_name = sys.argv[1] # Read from drag-n-drop file
    if not file_name.endswith('.TXT'):
        print(".txt file required!")
except IndexError:
    file_name = ''   

invalid_file = True

if not file_name.endswith('.TXT'): # If the drag-n-drop file is not a txt file
    while invalid_file: # Loop until valid file is encountered
        try:
            # Manually enter file name
            file_name = input("Enter file name to decode: ")
            # Try open the file
            input_file = open(file_name)
            # Confirm that it is a text file, else loop again!
            if file_name.endswith('.txt'): 
                invalid_file = False
            else:
                print(".txt file required!")
        except FileNotFoundError: 
            # Error if invalid location
            print("File not found!")
else:
    ### Doing this to pull out just the local filename ###
    #i = 0
    #for c in reversed(file_name):
        #if (c == "\\"):
            #break
        #i = i+1
    
    #last_backslash = len(file_name) - i
    #file_name = file_name[last_backslash:len(file_name)]
    ###---------------------------------------------###
    
    input_file = open(file_name) # If drag-n-drop in file is a .txt, open it

print("Loading file...", end = '')
print(file_name)
    
print("Success! Decoding ", end="")
print(file_name)

miniinput = minipack.MinipackInput()

data_line = ''

header = ['InitialVarHeader','InitialVars','logNo','timeStep','controlMode', 'forwardSensor1', 'forwardSensor2', 'AltitudeSensor', 'throttleControl', 'yawControl', 'rollControl', 'pitchControl', 'stablilityModeControl', 'errorP', 'errorI', 'errorD']

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

for i,line in enumerate(input_file):
    if i == 1:
        # Create an array 
        initial_vars = line.rstrip()
        initial_vars = initial_vars.split(' ')
        initial_vars = [float(i) for i in initial_vars]
        
        
    if i == 2:
        initial_vars_header = line.rstrip()
        initial_vars_header = initial_vars_header.split(',')
        
    if line[0] == '(':
        data_line = line
        


if (data_line == ''):
    print('Data line not found!')

array_no = 1

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


# Extend short inital values arrays with zeros

total_data_logs = len(logNo)
while (len(initial_vars)<total_data_logs):
    initial_vars.append(0)
    
while (len(initial_vars_header)<total_data_logs):
    initial_vars_header.append(0)


data_array = [initial_vars_header,initial_vars,logNo,timeStep,controlMode,forwardSensor1,forwardSensor2,AltitudeSensor,throttleControl,yawControl,rollControl,pitchControl,stablilityModeControl,errorP,errorI,errorD]
transposed_data_array = [list(x) for x in zip(*data_array)]
transposed_data_array.insert(0, header)


time = datetime.datetime.strftime(datetime.datetime.now(), '%Y-%m-%d')

output_file_name = time + '_TEST_'
output_file_suffix = '%s.csv'

i = 0
check_output_file_name = output_file_name + output_file_suffix
while os.path.exists(check_output_file_name % i):
    i += 1

output_file_name = output_file_name + (output_file_suffix % i)

# ERROR: Permissions denied when running via drag and drop
try:
    with open(output_file_name, 'w', newline='') as fp:
        data_csv = csv.writer(fp, delimiter=',')
        data_csv.writerows(transposed_data_array)
    print("Complete! Results stored in %s" % output_file_name)
except PermissionError:
    print("Permission error! Cannot write " + output_file_name)
    

input("Press enter to exit...")

#Use the unpacked data here!!!