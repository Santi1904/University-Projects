import socket
import threading
from packetHandler import *
from packet import Packet


class UDPreceiver:

    def __init__(self,node_name,senders,hosts,cache):

        self.node_name = node_name
        self.senders = senders
        self.hosts = hosts
        self.cache = cache


    def udp_bind(self, host):

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        ip, port = host.split(':')
        self.socket.bind((ip, int(port)))

        print("Bind to " + ip + ":" + port)

        try:
            while True:
                data, from_address = self.socket.recvfrom(1024)
                content = data.decode()
                packet = Packet("","")
                packet.packet_decode(content)
                pcktHandler = packetHandler(packet,self.senders,from_address,self.cache)
                send_socket_thread = threading.Thread(target=pcktHandler.handlePackets, args=(self.node_name,self.hosts,))
                send_socket_thread.start()
            
        
        finally:
            self.socket.close()
    