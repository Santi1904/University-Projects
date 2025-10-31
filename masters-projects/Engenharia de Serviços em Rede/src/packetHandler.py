import threading
import socket
from packet import Packet
from unicastReceiver import UnicastReceiver
from unicastSender import UnicastSender
from clientHandler import ClientHandler
import time
import random
import os
from tkinter import Tk

class packetHandler():

    def __init__(self,packet,senders,from_address,cache):
        self.packet = packet
        self.senders = senders
        self.from_address = from_address[0]
        self.cache = cache
        self.lock = threading.Lock()

    
    def handle_init(self):

        #print("Init packet received from -> " + self.packet.source)
        pass


    def addFilename(self,filename):
        self.filename = filename
    

    def handle_latencyRequest(self,node_name,hosts):

        for host in hosts:
            self.packet.ips.append(host)

        
        if node_name[0] == 's':
            self.packet.path.append(self.from_address)
            self.packet.id = 'LA'
            self.packet.source = hosts[0].split(':')[0]
            data = self.packet.packet_encode()

            for sender in self.senders:
                if sender.nb_address.split(':')[0] == self.packet.path[-1]:
                    sender.socket.send(data.encode())
                          
        else:
            self.packet.path.append(self.from_address)
            self.packet.jumps += 1
            data = self.packet.packet_encode()
            for send_name in self.senders:
                if send_name.nb_address not in self.packet.ips and send_name.nb_address != self.packet.source:
                    while True:
                        try:
                            send_name.socket.send(data.encode())
                            break
                        except socket.error as e:
                            time.sleep(5)
                  
        
    def handle_latencyAnswer(self,node_name,hosts):

        for host in hosts:
            self.packet.ips.append(host)

        self.packet.path.append(self.from_address)

        if node_name[0] == 'r':
            self.packet.jumps = 0
            lat = time.time() - self.packet.dateTime

            route = {'server' : self.packet.source, 'path' : self.packet.path ,'latency' : lat}

            self.cache.addRoute(route)
            self.cache.updateRoutes()

        
        elif node_name[0] == 'o':
            self.packet.jumps -= 1
            last_node_index = self.packet.jumps
            data = self.packet.packet_encode()

            for sender in self.senders:
                if sender.nb_address.split(':')[0] == self.packet.path[last_node_index]:
                    sender.socket.send(data.encode())
                 

        
    def handle_videoRequest(self, node_name, hosts):

        for host in hosts:
            self.packet.ips.append(host)

        if node_name[0] == 'r':

            alreadyRequested = self.cache.checkVideoStatus(self.packet)
            
            if alreadyRequested == 1:

                
                self.packet.path.append(self.from_address)

                while(len(self.cache.routes) == 0):
                    time.sleep(1)

                bestRoute = self.cache.routes[0]
                bestPath = bestRoute['path']

      
                streamID = str(random.randint(1,1000))

                self.packet.path.extend(bestPath)
                    
                self.cache.addStream(streamID,self.packet.filename,self.packet.source,self.cache.INIT,'','',self.packet.path)

                setupPacket = Packet('SP',"")
     
                setupPacket.addFilename(self.packet.filename)
                setupPacket.path = bestPath
                setupPacket.streamID = streamID
                setupPacket.currentHop -= 1
                data = setupPacket.packet_encode()
                for sender in self.senders:
                    if sender.nb_address.split(':')[0] == setupPacket.path[setupPacket.currentHop]:
                        sender.socket.send(data.encode())

        else:

            self.packet.path.append(self.from_address)
    
            data = self.packet.packet_encode()
            for send_name in self.senders:
                if send_name.nb_address not in self.packet.ips and send_name.nb_address != self.packet.source:
                    while True:
                        try:
                            send_name.socket.send(data.encode())
                            break
                        except:
                            time.sleep(5)

        
    def handle_setupRequest(self, node_name, hosts):

        if node_name[0] == 's':

            nextIP = (len(self.packet.path) // 2) - 1

            streamPort = self.cache.rtpPort

            unicastSender = UnicastSender(self.packet.path[nextIP],streamPort,self.packet.filename,1)
            self.cache.addStream(self.packet.streamID,self.packet.filename,self.packet.source,self.cache.READY,unicastSender,'',self.packet.path)

            self.cache.rtpPort += 1
            ackSetup = Packet('ACK_SP',"")
            ackSetup.currentHop = nextIP
            ackSetup.path = self.packet.path
            ackSetup.streamID = self.packet.streamID
            ackSetup.addFilename(self.packet.filename)
            ackSetup.streamPort = streamPort

            data = ackSetup.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == self.packet.path[nextIP]:
                    sender.socket.send(data.encode())
        
        else:
            self.packet.currentHop -= 1
            data = self.packet.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == self.packet.path[self.packet.currentHop]:
                    sender.socket.send(data.encode())
        


    def handle_ackSetup(self, node_name, hosts):

        if node_name[0] == 'r':
            

            pathBefore = self.cache.stream[self.packet.streamID]['path']

            for host in hosts:
                if host.split(':')[0] in pathBefore:
                    pos = (pathBefore.index(host.split(':')[0])) - 1

            ipBefore =  pathBefore[pos].split(':')[0]

            streamPort = self.packet.streamPort
            
            unicastReceiver = UnicastReceiver(self.packet.path[self.packet.currentHop],streamPort)

            self.packet.nextHop() 

            sendPort = self.cache.rtpPort

            unicastSender = UnicastSender(ipBefore,sendPort,self.packet.filename,2)
            unicastReceiver.addMulticastSender(unicastSender)

            self.cache.rtpPort += 1

            self.cache.stream[self.packet.streamID]['unicastReceiver'] = unicastReceiver
            self.cache.stream[self.packet.streamID]['unicastSender'] = unicastSender

            self.cache.getStream(self.packet.streamID)
            

            playPacket = Packet('PLAY',"")
            playPacket.addFilename(self.packet.filename)
            playPacket.streamID = self.packet.streamID
            playPacket.path = self.packet.path
            playPacket.currentHop = -1

            data = playPacket.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == playPacket.path[playPacket.currentHop]:
                    sender.socket.send(data.encode())
            

            ackPlay = Packet('ACK_PLAY',"")
            ackPlay.addFilename(self.packet.filename)
            ackPlay.streamID = self.packet.streamID
            ackPlay.path = self.cache.stream[self.packet.streamID]['path']
            ackPlay.streamPort = sendPort
            for host in hosts:
                if host.split(':')[0] in ackPlay.path:
                    ackPlay.currentHop = (ackPlay.path.index(host.split(':')[0])) - 1

            data2 = ackPlay.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == ackPlay.path[ackPlay.currentHop].split(':')[0] and sender.nb_address not in ackPlay.ips:
                    sender.socket.send(data2.encode())




        if node_name[0] == 'o':
            
            streamPort = self.packet.streamPort
            unicastReceiver = UnicastReceiver(self.packet.path[self.packet.currentHop],streamPort)


            self.packet.nextHop()

            senderPort = self.cache.rtpPort

            unicastSender = UnicastSender(self.packet.path[self.packet.currentHop],senderPort,self.packet.filename,2)
            unicastReceiver.addMulticastSender(unicastSender)

            self.cache.rtpPort += 1
         
            self.cache.addStream(self.packet.streamID,self.packet.filename,self.packet.source,self.cache.READY,unicastSender,unicastReceiver,self.packet.path)

            self.cache.getStream(self.packet.streamID)

    
            self.packet.streamPort = senderPort
            data = self.packet.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == self.packet.path[self.packet.currentHop]:
                    sender.socket.send(data.encode())

        
    
    def handle_play(self, node_name, hosts):

        if node_name[0] == 's':

            streamID = self.packet.streamID
            self.cache.startStream(streamID)
        
        else:
            self.packet.nextHop()
            data = self.packet.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == self.packet.path[self.packet.currentHop]:
                    sender.socket.send(data.encode())


    def handle_ackPlay(self, node_name, hosts):


        if node_name[0] != 'c':

            receiverIP = self.packet.path[self.packet.currentHop].split(':')[0]
            receiverPort = self.packet.streamPort

            unicastReceiver = UnicastReceiver(receiverIP,receiverPort)

            self.packet.nextHop()

            senderIP = self.packet.path[self.packet.currentHop].split(':')[0]
            senderPort = self.cache.rtpPort

            unicastSender = UnicastSender(senderIP,senderPort,self.packet.filename,2)
            unicastReceiver.addMulticastSender(unicastSender)

            self.cache.rtpPort += 1

            self.cache.addStream(self.packet.streamID,self.packet.filename,self.packet.source,self.cache.PLAYING,unicastSender,unicastReceiver,self.packet.path)

            self.cache.getStream(self.packet.streamID)

            nextIP = self.packet.path[self.packet.currentHop].split(':')[0]
            self.packet.streamPort = senderPort
            data = self.packet.packet_encode()
            for sender in self.senders:
                if sender.nb_address.split(':')[0] == nextIP:
                    try:
                        sender.socket.send(data.encode())
                    except:
                        time.sleep(5)


        elif node_name[0] == 'c':

            clientIP = self.packet.path[0].split(':')[0]
            clientPort = self.packet.streamPort

            os.environ['DISPLAY'] = ':0.0'
            root = Tk()

            # Create a new client
            app = ClientHandler(root,clientIP,clientPort,self.senders,self.packet.streamID)
            app.master.title("RTPClient")
            root.mainloop()
    

    def handle_pause(self, node_name, hosts):
        if node_name[0] == 'o': 

            streamID = self.packet.streamID
            senderSocket = self.cache.stream[streamID]['unicastSender']
            senderSocket.state = 1   
          
    
    def handle_play_(self, node_name, hosts):

        if node_name[0] == 'o':

            streamID = self.packet.streamID
            senderSocket = self.cache.stream[streamID]['unicastSender']
            senderSocket.state = 2

    def handle_teardown(self, node_name, hosts):


        if node_name[0] != 's': 
            if self.packet.streamID in self.cache.stream:
                self.packet.currentHop += 1

                streamID = self.packet.streamID
                twAddress = self.from_address

                for host in hosts:
                    x = host.split(':')
                    self.packet.ips.append(host)

                data = self.packet.packet_encode()

                receiverSocket = self.cache.stream[streamID]['unicastReceiver']
                receiverSocket.teardown(twAddress)

                for sender in self.senders:
                    if sender.nb_address not in self.packet.ips:
                        sender.socket.send(data.encode())
                
        else:

            streamID = self.packet.streamID
            twAddress = self.from_address

            if self.packet.streamID in self.cache.stream:

                senderSocket = self.cache.stream[streamID]['unicastSender']
                senderSocket.closeServer()
            
      

    def handlePackets(self, node_name, hosts):

        if self.packet.id == "init":
            self.handle_init()

        elif self.packet.id == "LR":
            self.handle_latencyRequest(node_name, hosts)

        elif self.packet.id == "LA":
            self.handle_latencyAnswer(node_name, hosts)

        elif self.packet.id == 'VR':
            self.handle_videoRequest(node_name, hosts)

        elif self.packet.id == 'SP':
            self.handle_setupRequest(node_name, hosts)
        
        elif self.packet.id == 'ACK_SP':
            self.handle_ackSetup(node_name, hosts)

        elif self.packet.id == "PLAY":
            self.handle_play(node_name, hosts)

        elif self.packet.id == 'ACK_PLAY':
            self.handle_ackPlay(node_name, hosts)
        
        elif self.packet.id == 'PAUSE':
            self.handle_pause(node_name, hosts)
        
        elif self.packet.id == 'PLAY_':
            self.handle_play_(node_name, hosts)
        
        elif self.packet.id == 'TEARDOWN':
            self.handle_teardown(node_name, hosts)
