import socket

#UDP_IP = "192.168.1.50"
#UDP_PORT = 1234
#MESSAGE = "Hello, World! from python ...."



def udp_write(ip,port,data ): 
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP
    sock.sendto(bytes(data, "utf-8"), (ip, port))


def udp_read(ip,port): 

    sock = socket.socket(socket.AF_INET, # Internet
                         socket.SOCK_DGRAM) # UDP
    sock.bind((ip, port)) 
    data, addr = sock.recvfrom(port) # buffer size is 1024 bytes
    print("received : %s" % data)
    return data



