import asyncio
from spade.agent import Agent

from Behaviours.ReceiveInfo import ReceiveInfo
from Behaviours.RequestRide import RequestRide
from Behaviours.RequestFood import RequestFood

from termcolor import colored

import random


class Client(Agent):

    async def setup(self):

        name = str(self.jid).split("@")[0]

        self.set("Name", name)
        self.set("Service", {})
        self.set("Stores", [])
        self.set("Location", (random.randint(-1000,1000),random.randint(-1000,1000)))
        self.set("Destination", (random.randint(-1000,1000),random.randint(-1000,1000)))
        self.set("Passengers", random.randint(1,7))
        self.set("Money", random.randint(10,100))

        bin = random.randint(0,1)

        if bin == 0:
           self.print_client(0)
           self.requestFood = RequestFood()
           self.add_behaviour(self.requestFood)
        else:
            self.print_client(1)
            self.requestRide = RequestRide()
            self.add_behaviour(self.requestRide)

        self.receiveInfo = ReceiveInfo()
        self.add_behaviour(self.receiveInfo)
     

    def select_service(self,service,type):

        ret = []


        for manager in service:
            for ride in service[manager]:
                if ride == type:
                    valor = float(service[manager][ride])
                    ret.append((manager,valor))

        ret = sorted(ret,key=lambda x: x[1])
        return ret

    def select_serviceType(self,service,type):

        ret = []

        for ride in service:
            if ride != type:
                valor = float(service[ride])
                ret.append((ride,valor))

        ret = sorted(ret,key=lambda x: x[1])
        return ret


    
    def select_ride(self,service,passengers):

        if passengers > 4:
            ret = (self.select_service(service,"XL"),"XL")
        elif passengers >= 1 and passengers <= 2:
            ret = (self.select_service(service,"Saver"),"Saver")
        elif passengers > 2 and passengers <= 4:
            ret = (self.select_service(service,"Standard"),"Standard")

        return ret
    

    def select_rideType(self,service,type):

        ret = self.select_serviceType(service,type)
        return ret

    

    def call_prices(self,stock_prices):

        sorted_prices = {}

        for store in stock_prices:
            inner_dict = stock_prices[store]
            sorted_inner_dict = dict(sorted(inner_dict.items(), key=lambda item: item[1]))
            sorted_prices[store] = sorted_inner_dict

        return sorted_prices


    def sort_by_lowest_price(self,stock_prices):
   
        def get_lowest_price(store_dict):
            return min(store_dict.values())

    
        sorted_list = sorted(stock_prices, key=lambda store: get_lowest_price(list(store.values())[0]))
    
        return sorted_list
    
    def print_client(self, flag):
    
        if flag == 0: 

            print(colored("=======================================", 'cyan', attrs=['bold']))
            print(colored("          == Client Info ==", 'cyan', attrs=['bold']))
            print(colored("=======================================", 'cyan', attrs=['bold']))
            print(colored(f"[Name]: {self.get('Name')}", 'cyan', attrs=['bold']))
            print(colored(f"[Location]: {self.get('Location')}", 'cyan', attrs=['bold']))
            print(colored(f"[Money]: {self.get('Money')}€", 'cyan', attrs=['bold']))
            print(colored("=======================================", 'cyan', attrs=['bold']))
        else: 

            print(colored("=======================================", 'cyan', attrs=['bold']))
            print(colored("          == Client Info ==", 'cyan', attrs=['bold']))
            print(colored("=======================================", 'cyan', attrs=['bold']))
            print(colored(f"[Name]: {self.get('Name')}", 'cyan', attrs=['bold']))
            print(colored(f"[Location]: {self.get('Location')}", 'cyan', attrs=['bold']))
            print(colored(f"[Destination]: {self.get('Destination')}", 'cyan', attrs=['bold']))
            print(colored(f"[Passengers]: {self.get('Passengers')}", 'cyan', attrs=['bold']))
            print(colored("=======================================", 'cyan', attrs=['bold']))


    def print_requestFood(self,request):

        stock_type = request.getType()
        quantity = request.getQuantity()

        print(" ")
        print(colored("***************************************", 'cyan', attrs=['bold']))
        print(colored("CLIENT REQUEST", 'cyan', attrs=['bold']))
        print(colored("---------------------------", 'cyan', attrs=['bold']))
        print(" ")
        print(colored(   f"STOCK TYPE: {stock_type}", 'cyan', attrs=['bold']))
        print(colored(   f"QUANTITY: {quantity}", 'cyan', attrs=['bold']))
        print(colored("***************************************", 'cyan', attrs=['bold']))

    
    def print_prices(self,prices):
        
        print(" ")
        print(" ")
        print(colored("=======================================", 'cyan', attrs=['bold']))
        print(colored("==       STOCK PRICES BY STORE       ==",'cyan', attrs=['bold']))
        print(colored("=======================================", 'cyan', attrs=['bold']))

        for pos in prices:
            for manager in pos:
                print(colored(f"[{manager}] :", 'cyan', attrs=['bold']))
                for store in pos[manager]:
                    print(colored(f"  {store} : {pos[manager][store]}€", 'cyan', attrs=['bold']))
            print(colored("--------------------------- ", 'cyan', attrs=['bold']))
        print(colored("=======================================", 'cyan', attrs=['bold']))


    

    def print_services(self,service):
        
        print(" ")
        print(" ")
        print(colored("=======================================", 'cyan', attrs=['bold']))
        print(colored("==  AVAILABLE SERVICES BY MANAGER   ==",'cyan', attrs=['bold']))
        print(colored("=======================================", 'cyan', attrs=['bold']))

        for manager in service:
            print(colored(f"[{manager}] :", 'cyan', attrs=['bold']))
            for class_ in service[manager]:
                print(colored(f"  {class_} : {service[manager][class_]}€", 'cyan', attrs=['bold']))
            print(colored("--------------------------------------- ", 'cyan', attrs=['bold']))
        print(colored("=======================================", 'cyan', attrs=['bold']))