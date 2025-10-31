from asyncio import sleep
from spade.agent import Agent
from Behaviours.SubscribeStore import SubscribeStore

import random

class Store(Agent):

    def __str__(self):
        return f"Name: {self.name}"
    
    async def setup(self):

        local = str(self.jid).split('@')[0]

        managers = ["uber","glovo"]

        self.set("Name", local)
        self.set("Managers", managers)
        self.set("Stock1", [random.randint(10,20),random.randint(1,10)])
        self.set("Stock2", [random.randint(10,20),random.randint(1,30)])
        self.set("Stock3", [random.randint(10,20),random.randint(1,50)])

        sub = SubscribeStore()
        self.add_behaviour(sub)







