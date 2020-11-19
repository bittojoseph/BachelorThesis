import serial
import csv
ser = serial.Serial('/dev/ttyACM0', 9600)

with open('/home/bitto/Documents/GIT/Bachelor_Thesis/Codes/calibration_file.csv', mode='w') as calibration_file:
    calibration_writer = csv.writer(calibration_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    calibration_writer.writerow(['Acceleration in X', 'Acceleration in Y', 'Acceleration in Z'])

    calibration_list = []
    i = 0
    while i < 500:
        try:
            ser_bytes = ser.readline()
            decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
            calibration_list = decoded_bytes.split(" ")
            calibration_writer.writerow(calibration_list)
            i += 1
            print(ser_bytes)
        except:
            print("Keyboard Interrupt")
            break