import random

class StockRequest:

    def __init__(self,client,type,quantity):
        self.client = client
        self.type = type
        self.quantity = quantity
      
    def getClient(self):
        return self.client

    def getType(self):
        return self.type

    def getQuantity(self):
        return self.quantity

   