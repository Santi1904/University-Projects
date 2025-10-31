from spade.message import Message
import jsonpickle
from spade.behaviour import OneShotBehaviour

from Info.ClientInfo import ClientInfo
from Info.StockRequest import StockRequest

import random

class RequestFood(OneShotBehaviour):
    
    async def run(self):
        
        XMPP = self.agent.get("XMPP")

        tri   = random.randint(1,3)
        quant = random.randint(1,5)

        stock_request = StockRequest(self.get("Name"),f"Stock{tri}",quant)

        self.agent.print_requestFood(stock_request)

        managers = self.agent.get("Managers")
       
        for manager in managers:

            if manager != 'freenow':

                msg = Message(to=f"{manager}{XMPP}")
                msg.body = jsonpickle.encode(stock_request)
                msg.set_metadata("performative", "inform")
                await self.send(msg)
        
        
        
        