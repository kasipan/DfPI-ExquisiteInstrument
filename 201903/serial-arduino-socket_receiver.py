import socket
import json
import time
from datetime import datetime


sendAddr = ('172.20.10.11', 2391)     # robot's addr
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ('0.0.0.0', 2390)
sock.bind(addr)

# index for recording time
relation_index = '''
{
    "personal":{
        "from": 0,
        "to": 120
    },
    "close":{
        "from": 121,
        "to": 200
    },
   "normal":{
        "from": 201,
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
    sock.sendto(str(msg).encode('utf8'), sendAddr)

def saveCSV(sensor_id, relation, time):
    with open('./data/record_{}.csv'.format(sensor_id), 'a') as f:
        end_time = datetime.now().strftime("%H:%M:%S")
        f.write('{},{},{}\n'.format(relation, time, end_time))

#initial relation
prev_relation={1:'public', 2:'public', 3:'public'}
start = time.time()
while True:
    msg, sender = sock.recvfrom(512)
    print('msg: {}, sender: {}'.format(msg, sender))
    if len(msg) is not 0:
        json_dict = json.loads(msg)
        sensor_id = json_dict['sensor']
        distance = json_dict['distance']

        # only center data is sent
        if sensor_id is 1:
            sendData(distance)

        # record time in particular distance
        for key, range in relation_dict.items():
            if distance > range['from'] and distance < range['to']:
                if prev_relation[sensor_id] is not key:
                    elapsed_time = time.time() - start
                    saveCSV(sensor_id, prev_relation[sensor_id], elapsed_time)

                    #couting time for next relation
                    prev_relation[sensor_id] = key
                    start = time.time()
