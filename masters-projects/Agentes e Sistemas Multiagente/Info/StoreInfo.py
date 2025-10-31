
class StoreInfo:

    def __init__(self,name,stock1,stock2,stock3):
        self.name = name
        self.stock1 = stock1 
        self.stock2 = stock2
        self.stock3 = stock3
    
    def getName(self):
        return self.name

    
    def getStock1(self):
        return self.stock1
    
    def getStock2(self):
        return self.stock2
    
    def getStock3(self):
        return self.stock3
    
    def setStock1(self,stock1):
        self.stock1[0] = stock1

    def setStock2(self,stock2):
        self.stock2[0] = stock2
    
    def setStock3(self,stock3):
        self.stock3[0] = stock3
    