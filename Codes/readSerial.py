import serial
import csv
ser = serial.Serial('/dev/ttyACM0', 9600)

#with open("/home/bitto/Documents/GIT/Bachelor_Thesis/Codes/Calibration_data.csv", 'w', newline='') as csvfile:
while True:
    try:
        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        print(decoded_bytes + '\n')
    except:
        print("Keyboard Interrupt")
        break