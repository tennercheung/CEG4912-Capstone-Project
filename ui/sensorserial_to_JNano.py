import serial



bin_readings = ["1","2","3","4"]

def readSensorData():
    
    arduino = serial.Serial(port='/dev/ttyACM0',  baudrate=9600, timeout=.1)
    counter = 0
    
    while(counter<4):

        data = arduino.readline().decode('utf-8').rstrip()
        if(data!=""):
            # print(data)
            bin_readings[counter]=data
            counter+=1
        if (counter==4):
            break
            
def parseSensorData():
    ## write into .txt file for UI to read

    pass
while True:
    readSensorData()
    print(bin_readings)
    parseSensorData()
    


