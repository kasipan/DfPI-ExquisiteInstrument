import serial
import time
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ('172.20.10.8', 2390)

def sendData(msg):
    sock.sendto(msg.encode('utf8'), addr)

if __name__ == '__main__':
    gpio_seri = serial.Serial('/dev/ttyACM0', 9600, timeout=10)
    print(gpio_seri.portstr)
    time.sleep(3)
    while 1:
        gpio_seri.write('get')
        time.sleep(1)
        data = gpio_seri.readline()
        print(data)
        sendData(data)
