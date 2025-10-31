from Behaviours.ReceiveRequest import ReceiveRequest

from spade.agent import Agent

import math
import random

from termcolor import colored


class Freenow(Agent):

     async def setup(self):

          keys = ["Saver","Standard","XL"]
          service = dict.fromkeys(keys)

          self.set("Name", "freenow")
          self.set("Transport List", [])
          self.set("Service", service)

          receiveRequest = ReceiveRequest()
          self.add_behaviour(receiveRequest)  

          

     def calculate_distance(self, location, destination):
          return math.sqrt((location[1] - location[0])**2 + (destination[1] - destination[0])**2)
     
     
     def calculate_service(self, location, destination):

          service = self.get("Service")

          
          for key in service:
               if key == "Saver":
                    service[key] = round(self.calculate_distance(location, destination) * random.uniform(0.1,0.9),2)
               elif key == "Standard":
                    service[key] = round(self.calculate_distance(location, destination) * random.uniform(1.1,1.9),2)
               elif key == "XL":
                    service[key] = round(self.calculate_distance(location, destination) * random.uniform(2.1,2.9),2)

          return service


     def select_vehicle(self,cl_location,_class):

          closest_vehicle = None
          min_dist = 10000

          for v in self.get("Transport List"):
               if v.getClass() == _class:
                    loc = v.getLocation()
                    if v.getAvailability() == True:
                         dist = self.calculate_distance(cl_location,loc)
                         if dist < min_dist:
                              min_dist = dist
                              closest_vehicle = v

          return closest_vehicle


     def print_all_vehicles(self):

          print(" ")
          print(colored("========================= ", "yellow", attrs=["bold"]))
          print(colored("=     VEHICLES LIST     = ", "yellow", attrs=["bold"]))
          print(colored("========================= ", "yellow", attrs=["bold"]))
          for t in self.get("Transport List"):
               print(colored(f"= Model: {t.getModel()}", "yellow", attrs=["bold"]))
               print(colored(f"= Class: {t.getClass()}", "yellow", attrs=["bold"]))
               print(colored(f"= Location: {t.getLocation()}", "yellow", attrs=["bold"]))
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
                    print(colored("=========================", "yellow", attrs=["bold"]))
          print(" ")

