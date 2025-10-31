import socket
import threading
from rtpPacket import RtpPacket
from packet import Packet
import time

class UnicastReceiver():

    def __init__(self, host_ip, host_port):
        self.host_ip = host_ip
        self.host_port = int(host_port)
        self.unicastStreamReceiver = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.playEvent = threading.Event()
        self.frameNbr = 0
        self.teardownAcked = 0
        self.multicastSenders = []
    
    def updateHost(self, host_ip):
        self.host_ip = host_ip

    
    def addMulticastSender(self, multicastSender):
        self.multicastSenders.append(multicastSender)
    
    def listenRtp(self):      
        """Listen for RTP packets."""
        
        self.unicastStreamReceiver.bind((self.host_ip, self.host_port))


        while True:

            try:
                    data = self.unicastStreamReceiver.recv(20480)

                    if data:

                        rtpPacket = RtpPacket()
                        rtpPacket.decode(data)
                        currFrameNbr = rtpPacket.seqNum()
                        if self.frameNbr > currFrameNbr:
                            self.frameNbr = 0

                        print("Current Seq Num: " + str(currFrameNbr))
                        if currFrameNbr > self.frameNbr: # Discard the late packet
                            self.frameNbr = currFrameNbr
                        for mcastSender in self.multicastSenders:
                            if mcastSender.state == 2:
                                mcastSender.unicastStreamSender.sendto(data,(mcastSender.sendIP,int(mcastSender.sendPort)))
                
            except:
                pass



    def teardown(self,clientAddr):
		
        for mcastSender in self.multicastSenders:
            if mcastSender.sendIP == clientAddr.split(':')[0]:
                mcastSender.state = 0
                mcastSender.unicastStreamSender.close()
                self.multicastSenders.remove(mcastSender)
        if len(self.multicastSenders) == 0:
            self.unicastStreamReceiver.close()
                    
    
