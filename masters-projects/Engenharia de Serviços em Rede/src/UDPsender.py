import socket
import time
from packet import Packet
from packetHandler import *

class UDPsender:

    def __init__(self,node_name,hosts,nb_address):

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.node_name = node_name
        self.hosts = hosts
        self.nb_address = nb_address
        self.host_address = ""
    
    def addHost(self,host_address):

        ip, port = host_address.split(':')
        self.host_address = ip
 
    def udp_connect(self):
        
        ip, port = self.nb_address.split(':')
        #self.nb_address = ip

        try:
            time.sleep(10)
            self.socket.connect((ip, int(port)))
            print("Connected to " + ip + ":" + port)
            packet = Packet("init",self.host_address)
            data = packet.packet_encode()
            while True:
                try:
                    self.socket.send(data.encode())
                    break
                except:
                    time.sleep(5)

        except socket.error as e:
            print("Error connecting to " + ip + ":" + port + ". Details: " + str(e))
        

    def latencyTest(self):

        time.sleep(11)
        
        while(True):
            packet = Packet('LR',self.host_address)
            for host in self.hosts:
                packet.ips.append(host)
            ip, port = self.nb_address.split(':')
            data = packet.packet_encode()
            while True:
                try:
                    self.socket.sendto(data.encode(),(ip,int(port)))
                    break
                except:
                    time.sleep(5)
            time.sleep(60)

    def videoRequest(self,packet):

        time.sleep(15)

        data = packet.packet_encode()
        while True:
            try:
                self.socket.send(data.encode())
                break
            except:
                time.sleep(5)
        

