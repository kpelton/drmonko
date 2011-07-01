#!/usr/bin/python
import socket
import select
hosts = []
hostdict = {}
HOST = ''    
PORT = 52312
curr = 0
lsock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
lsock.bind((HOST, PORT))

hosts.append(lsock)

lsock.listen(1)
print 'listen'
def accept_client():
    conn, addr = lsock.accept()
    print 'Connected by', addr
    hosts.append(conn) 
    hostdict[conn]  = addr


def handle_input(sock):
    
    data = sock.recv(1024)
    print data

    




while 1:
    
    ready_to_read, ready_to_write, in_error = select.select(
        hosts,
        hosts,
        hosts,
        100)

    for sock in ready_to_read:
        if sock == lsock:
            accept_client()
        else:
            handle_input(sock)

