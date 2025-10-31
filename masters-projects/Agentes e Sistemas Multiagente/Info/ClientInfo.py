import random

class ClientInfo():

    def __init__(self,name,location,destination):
        self.name = name
        self.location = location
        self.destination = destination
        self.senders = []
        self.passengers = 0
    
    def getName(self):
        return self.name
    
    def getLocation(self):
        return self.location

    def getDestination(self):
        return self.destination

    
    def getPassengers(self):
        return self.passengers

    def setPassengers(self,passengers):
        self.passengers = passengers
    
    def getSenders(self):
        return self.senders

    def addSender(self,sender):
        self.senders.append(sender)

    
    
        