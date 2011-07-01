#!/usr/bin/python
import socket
import select
import struct
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


def index_of(v,l):
    i = 0
    for x in l:
        if x == v:
            return i
        i+=1
    lsock.close()
    raise RuntimeError("Not found")


def handle_input(sock,ready):
    cmds = [
       "UPDATE",
	"SEED",
	"NEWGAME",
	"NEWPIECE",
	"GAMEOVER",
        "CONNECT"
        "WIN",
	"PAUSE",
	"PONG",
        "ADDPLAYER",
     

       ]

    data = sock.recv(4)
    #Get Msg Type
    msg = struct.unpack("I", data)[0]
        
        

    if msg >= 0 and msg < len(cmds):
        print cmds[msg]
        if cmds[msg] == "GAMEOVER":
            print hosts
            if len(hosts[1:]) > 1:
                for s in hosts[1:]:
                    if s != lsock:
                        s.send(struct.pack("I",index_of("SEED",cmds)))
                        s.send(struct.pack("I",512312))
        elif cmds[msg] == "UPDATE":
            for s in hosts:
                if s != sock and s != lsock:
                    s.send(struct.pack("I",index_of("UPDATE",cmds)))
                    s.send(sock.recv(4))

        elif cmds[msg] == "NEWPIECE":
             for s in hosts:
                if s != sock and s != lsock:
                    s.send(struct.pack("I",index_of("NEWPIECE",cmds)))
                    s.send(sock.recv(4))
 
       
while 1:
    ready_to_read, ready_to_write, in_error = select.select(
        hosts,
        [],
        hosts,
        5000)

    for sock in ready_to_read:
        if sock == lsock:
            accept_client()
        else:
            handle_input(sock,ready_to_write)

