import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
addr = ('172.20.10.6', 2390)

sock.sendto("hi!!!".encode('utf8'), addr)
