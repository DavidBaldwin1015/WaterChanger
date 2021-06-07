#!/usr/bin/env python3
import serial
import sys
import time

command = sys.argv[1]

if __name__ == '__main__':
	print(command)
	ser=serial.Serial('/dev/ttyACM0',9600, timeout=1)
	time.sleep(1)
	ser.setDTR(0)
	time.sleep(1)
	print((str(command)+"\n").encode('ascii'))
	#decodedCommand = command.decode('utf-8')
	#print((str(decodedCommand)+"\n").encode('ascii'))
	ser.write((str(command)+"\n").encode('ascii'))
	response = ser.readline().decode('utf-8').rstrip()
	print(response)
	#f=open('/home/pi/responselog.txt', 'w')
	#f.write(response)
	#f.close()
	ser.close()
	exit()