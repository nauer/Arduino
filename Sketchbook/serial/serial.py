#!/usr/bin/python3
import serial

ser = serial.Serial('/dev/ttyACM0', 19200)

# check which port was really used
print(ser.name)

# Start reading on Arduino - send 1
ser.write("1")

while 1:
  tdata = ser.read()           # Wait forever for anything
  print(tdata)

ser.close()
