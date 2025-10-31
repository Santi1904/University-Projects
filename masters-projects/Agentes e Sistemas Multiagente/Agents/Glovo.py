from Behaviours.ReceiveRequest import ReceiveRequest


from spade.agent import Agent

from termcolor import colored

import random
import math


class Glovo(Agent):

     async def setup(self):

          self.set("Name", "glovo")
          self.set("Transport List", [])
          self.set("Store List", [])  

          receiveRequest = ReceiveRequest()
          self.add_behaviour(receiveRequest)    

     
     def calculate_distance(self, location, destination):
          return math.sqrt((location[1] - location[0])**2 + (destination[1] - destination[0])**2)
     

     def calculate_price(self,type,quantity):

          store_list = self.get("Store List")
          ret = {}
          aux = {}
          total = 0
          comission = random.uniform(0.1,0.9)

          for store in store_list:
               
               if type == "Stock1":

                    total = round(quantity * store.getStock1()[1] * comission,2)
                    aux[f"{store.getName()}"] = total
               
               elif type == "Stock2":
          
              
                    total = round(quantity * store.getStock2()[1] * comission,2)
                    aux[f"{store.getName()}"] = total
               
               elif type == "Stock3":
          
                    total = round(quantity * store.getStock3()[1] * comission,2)
                    aux[f"{store.getName()}"] = total
          
          ret[self.get("Name")] = aux
          
          return ret


     def contact_store(self,store,quantity,stock_type):

          store_list = self.get("Store List")
          

          for s in store_list:
               if s.getName() == store:
                    if stock_type == "Stock1":
                         if quantity <= s.getStock1()[0]:
                              return True
                         else:
                              return s.getStock1()[0]
                    elif stock_type == "Stock2":
                         if quantity <= s.getStock2()[0]:
                              return True
                         else:
                              return s.getStock2()[0]
                    elif stock_type == "Stock3":
                         if quantity <= s.getStock3()[0]:
                              return True
                         else:
                              return s.getStock3()[0]
                    
                    

     def food_deliver_vehicle(self,client_location):

          transport_list = self.get("Transport List")

          closest_vehicle = None
          min_dist = 10000

          for t in transport_list:
               if t.getAvailability() == True:
                    loc = t.getLocation()
                    dist = self.calculate_distance(client_location,loc)
                    if dist < min_dist:
                         min_dist = dist
                         closest_vehicle = t

          return closest_vehicle
     

     def remove_stock(self,store,quantity,stock):

          stores = self.get("Store List")

          for s in stores:
               if s.getName() == store:
                    if stock == "Stock1":
                         stock_value = s.getStock1()[0]
                         new_value = stock_value - quantity
                         if new_value < 0:
                              new_value = 0
                         s.setStock1(new_value)
                    elif stock == "Stock2":
                         stock_value = s.getStock1()[0]
                         new_value = stock_value - quantity
                         if new_value < 0:
                              new_value = 0
                         s.setStock1(new_value)
                    elif stock == "Stock3":
                         stock_value = s.getStock1()[0]
                         new_value = stock_value - quantity
                         if new_value < 0:
                              new_value = 0
                         s.setStock1(new_value)
                    break

          self.set("Store List", stores)
     

     def print_vehicle(self,model,client_name):

          print(" ")
          for t in self.get("Transport List"):
               if t.getModel() == model:
                    print(colored("================================= ", "yellow", attrs=["bold"]))
                    print(colored(f"= {client_name}'s DELIVERY VEHICLE INFO = ", "yellow", attrs=["bold"]))
                    print(colored("================================= ", "yellow", attrs=["bold"]))
                    print(colored(f"= Model: {t.getModel()}", "yellow", attrs=["bold"]))
                    print(colored(f"= Location: {t.getLocation()}", "yellow", attrs=["bold"]))
                    print(colored("================================", "yellow", attrs=["bold"]))
          print("")

     
     def print_all_vehicles(self):

          print(" ")
          print(colored("========================= ", "yellow", attrs=["bold"]))
          print(colored("=     VEHICLES LIST     = ", "yellow", attrs=["bold"]))
          print(colored("========================= ", "yellow", attrs=["bold"]))
          for t in self.get("Transport List"):
               print(colored(f"= Model: {t.getModel()}", "yellow", attrs=["bold"]))
               print(colored(f"= Class: {t.getClass()}", "yellow", attrs=["bold"]))
               print(colored(f"= Location: {t.getLocation()}", "yellow", attrs=["bold"]))
               print(colored(f"= PASSENGERS ALLOWED: {t.getPassengers()}", "yellow", attrs=["bold"]))
               print(colored(f"= AVAILABLE: {t.getAvailability()}", "yellow", attrs=["bold"]))
               print(colored("=========================", "yellow", attrs=["bold"]))
          print(" ")

     

     def print_ride(self,model,client_name):

          print(" ")
          for t in self.get("Transport List"):
               if t.getModel() == model:
                    print(colored("========================= ", "yellow", attrs=["bold"]))
                    print(colored(f"=  {client_name}'s RIDE INFO  = ", "yellow", attrs=["bold"]))
                    print(colored("========================= ", "yellow", attrs=["bold"]))
                    print(colored(f"= Model: {t.getModel()}", "yellow", attrs=["bold"]))
                    print(colored(f"= Class: {t.getClass()}", "yellow", attrs=["bold"]))
                    print(colored(f"= Location: {t.getLocation()}", "yellow", attrs=["bold"]))
                    print(colored(f"= PASSENGERS ALLOWED: {t.getPassengers()}", "yellow", attrs=["bold"]))
                    print(colored("=========================", "yellow", attrs=["bold"]))
          print(" ")


     def print_stock(self):

          print(" ")
          print(colored("========================== ", "yellow", attrs=["bold"]))
          print(colored(f"=       STOCK INFO      = ", "yellow", attrs=["bold"]))
          print(colored("========================== ", "yellow", attrs=["bold"]))
          for s in self.get("Store List"):
               print(colored(f"         {s.getName()} ", "yellow", attrs=["bold"]))
               print(colored(f"  -> Stock1: {s.getStock1()[0]} un", "yellow", attrs=["bold"]))
               print(colored(f"  -> Stock2: {s.getStock2()[0]} un", "yellow", attrs=["bold"]))
               print(colored(f"  -> Stock3: {s.getStock3()[0]} un", "yellow", attrs=["bold"]))
               print(colored("==========================", "yellow", attrs=["bold"]))
          print(" ")