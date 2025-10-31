import threading

class Cache:

    INIT = 0
    READY = 1
    PLAYING = 2
    state = INIT

    def __init__(self):
        self.rtpPort = 40000
        self.routes = []
        self.videoRequests = []
        self.stream = {}
        self.lock = threading.Lock()

    
    def addRoute(self,route):

        self.lock.acquire()
        self.routes.append(route)
        self.lock.release()

    
    def updateRoutes(self):

        self.lock.acquire()
        self.routes = sorted(self.routes, key=lambda route: route['latency'])
        self.lock.release()


    def addStream(self,streamID,filename,videoSource,state,unicastSender,unicastReceiver,path):

        self.stream[streamID] = {'filename' : filename, 'videoSource' : videoSource, 'state' : state, 'unicastSender' : unicastSender, 'unicastReceiver' : unicastReceiver ,'path' : path}


    def updateState(self,streamID,state):
        self.stream[streamID]['state'] = state

    
    def checkVideoStatus(self,packet):

        self.lock.acquire()
        
        flag = 1

        videoSoure = packet.source
        videoFilename = packet.filename

        for videoDict in self.videoRequests:
            if videoDict['videoSource'] == videoSoure and videoDict['videoFilename'] == videoFilename:
                flag = 0
                break
            
        if flag == 1:
            videoRequest = {'videoSource' : videoSoure, 'videoFilename' : videoFilename}
            self.videoRequests.append(videoRequest)

        self.lock.release()
      
        return flag


    def startStream(self,streamID):

        self.stream[streamID]['state'] = self.PLAYING
        newStream = self.stream[streamID]
        playThread = threading.Thread(target=newStream['unicastSender'].sendRtp, args=())
        playThread.start()
    

    def getStream(self,streamID):
        
        receive_stream = self.stream[streamID]
        getStreamThread = threading.Thread(target=receive_stream['unicastReceiver'].listenRtp, args=())
        getStreamThread.start()

