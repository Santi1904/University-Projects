import time
import threading

class Packet:
    
    def __init__(self, id, source):

        self.id = id
        self.source = source
        self.dateTime = time.time()
        self.jumps = 0
        self.filename = ""
        self.currentHop = 0
        self.streamID = ""
        self.streamPort = 0
        self.path = []
        self.ips = []
        self.lock = threading.Lock()

    
    def addFilename(self,filename):
        self.filename = filename

    def nextHop(self):
        self.lock.acquire()
        self.currentHop -= 1
        self.lock.release()

    
    def addStreamID(self,streamID):
        self.streamID = streamID
    
    def addClientState(self,state):
        self.clientState = state

    def packet_encode(self):

        content = ""
        content += f"{self.id},{self.source},{self.dateTime},{self.jumps},{self.filename},{self.currentHop},{self.streamID},{self.streamPort},"

        for index, x in enumerate(self.path):
            if index == len(self.path)-1:
                content += str(x)
            else:
                content += str(x) + '-'
        
        content += ','

        for index, y in enumerate(self.ips):
            if index == len(self.ips)-1:
                content += str(y)
            else:
                content += str(y) + '-'
        
        
        return content    

    def packet_decode(self,content):

        elems = content.split(',')
        self.id = elems[0]
        self.source = elems[1]
        self.dateTime = float(elems[2])
        self.jumps = int(elems[3])
        self.filename = elems[4]
        self.currentHop = int(elems[5])
        self.streamID = elems[6]
        self.streamPort = int(elems[7])

        if len(elems) > 8 and elems[8] != '':
            self.path = elems[8].split('-')
        else:
            self.path = []

        if len(elems) > 9 and elems[9] != '':
            self.ips = elems[9].split('-')
        else:
            self.ips = []
        
    
    def print_packet(self):
        print(f"\nID: {self.id}, Source: {self.source}, DateTime: {self.dateTime}\nPath: {self.path}\nIPs: {self.ips}")