from spade.message import Message
import jsonpickle
from spade.behaviour import OneShotBehaviour

from Info.ClientInfo import ClientInfo

import random

class RequestRide(OneShotBehaviour):
    
    async def run(self):
        
        XMPP = self.agent.get("XMPP")
        
        client_info = ClientInfo(self.agent.get("Name"),self.agent.get("Location"),self.agent.get("Destination"))

        managers = self.agent.get("Managers")

        client_info.setPassengers(random.randint(1,7))

        for manager in managers:

            if manager != 'glovo':

                msg = Message(to=f"{manager}{XMPP}")
                msg.body = jsonpickle.encode(client_info)
                msg.set_metadata("performative", "inform")
                await self.send(msg)
        
        
        
        