import socket
import json
import time

sendAddr = ('172.20.10.11', 2391)     # robot's addr
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ('0.0.0.0', 2390)
sock.bind(addr)

# index for recording time
relation_index = '''
{
    "personal":{
        "from": 0,
        "to": 150
    },
    "close":{
        "from": 151,
        "to": 250
    },
   "normal":{
        "from": 251,
        "to": 300
    },
    "public":{
        "from": 301,
        "to": 600
    }
}'''
relation_dict = json.loads(relation_index)



# Sending data to change robot's behaviour
def sendData(msg):
    #sock.sendto(msg.encode('utf8'), sendAddr)
    sock.sendto(str(msg).encode('utf8'), sendAddr)

def saveCSV(relation, time):
    with open('./data/record.csv', 'a') as f:
        f.write('{},{}\n'.format(relation, time))


prev_relation = "public"    #initial relation
start = time.time()
while True:
    msg, sender = sock.recvfrom(512)
    print('msg: {}, sender: {}'.format(msg, sender))
    if len(msg) is not 0:
        json_dict = json.loads(msg);
        distance = json_dict['distance']
        sendData(distance);

        # record time in particular distance
        for key, range in relation_dict.items():
            if distance > range['from'] and distance < range['to']:
                if prev_relation is not key:
                    elapsed_time = time.time() - start
                    saveCSV(prev_relation, elapsed_time)

                    #couting time for next relation
                    prev_relation = key
                    start = time.time()
