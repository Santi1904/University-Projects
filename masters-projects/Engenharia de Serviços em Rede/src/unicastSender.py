from rtpPacket import RtpPacket
import socket
import threading
from videoStream import VideoStream

class UnicastSender:

    INIT = 0
    READY = 1
    PLAYING = 2
    #state = INIT

    def __init__(self, ip, port,filename,state):
        self.sendIP = ip
        self.sendPort = int(port)
        self.filename = filename
        self.unicastStreamSender = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.videoStream = VideoStream(self.filename)
        self.state = state
        self.teardown = 0
        self.event = threading.Event()


    def sendRtp(self):
        """Send RTP packets over UDP."""
        while True:
            self.event.wait(0.05)

            if self.teardown == 1:
                break
            
            data = self.videoStream.nextFrame()
            if data:
                frameNumber = self.videoStream.frameNbr()
                try:
                    address = self.sendIP
                    port = int(self.sendPort)
                    rtpPack = self.makeRtp(data, frameNumber)
                    self.unicastStreamSender.sendto(rtpPack, (address, port))
                except:
                    print("Connection Error")


            else:
                self.videoStream.restart()


    def updateState(self,state):
        self.state = state


    def makeRtp(self, payload, frameNbr):
        """RTP-packetize the video data."""
        version = 2
        padding = 0
        extension = 0
        cc = 0
        marker = 0
        pt = 26 # MJPEG type
        seqnum = frameNbr
        ssrc = 0 

        rtpPacket = RtpPacket()

        rtpPacket.encode(version, padding, extension, cc, seqnum, marker, pt, ssrc, payload)
        print("Encoding RTP Packet: " + str(seqnum))

        return rtpPacket.getPacket()
    

    def closeServer(self):
        self.teardown = 1
