import socket
import json

sendAddr = ('172.20.10.11', 2391)     # robot's addr
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ('0.0.0.0', 2390)
sock.bind(addr)


# Sending data to change robot's behaviour
def sendData(msg):
    #sock.sendto(msg.encode('utf8'), sendAddr)
    sock.sendto(str(msg).encode('utf8'), sendAddr)

while True:
    msg, sender = sock.recvfrom(512)
    print("msg: {}, sender: {}".format(msg, sender))
    if len(str) is not 0:
        json_dict = json.loads(msg);
        distance = json_dict['distance']
        sendData(distance);
