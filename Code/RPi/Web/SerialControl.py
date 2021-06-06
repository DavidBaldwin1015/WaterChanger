import serial
import sys
import time

command = sys.argv[1]

if __name__ == '__main__':
	print(command)
	ser=serial.Serial('/dev/ttyACM0',9600, timeout=1)
	ser.write((str(command)+"\n").encode('ascii'))
	time.sleep(0.2)
	response = ser.readline().decode('ascii').rstrip()
	f=open('/home/pi/responselog.txt', 'w')
	f.write(response)
	f.close()
	ser.close()