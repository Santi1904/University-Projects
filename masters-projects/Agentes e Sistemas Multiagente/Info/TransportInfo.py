
class TransportInfo():

    def __init__(self, model ,type, passengers,location, _class):
        self.model = model
        self.type = type
        self.location = location 
        self.passengers = passengers
        self._class = _class
        self.available = True


    def getModel(self):
        return self.model
    
    def getType(self):
        return self.type

    def getLocation(self):
        return self.location
    
    def getPassengers(self):
        return self.passengers

    def getAvailability(self):
        return self.available
    
    def getFlag(self):
        return self.flag

    def getClass(self):
        return self._class
    
    def setAvailability(self,aval):
        self.available = aval