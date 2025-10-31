from spade.behaviour import CyclicBehaviour
from spade.message import Message

from Info.StoreInfo import StoreInfo
from Info.TransportInfo import TransportInfo 
from Info.ClientInfo import ClientInfo
from Info.StockRequest import StockRequest

from termcolor import colored

import jsonpickle

class ReceiveRequest(CyclicBehaviour):
    
    async def run(self):

        XMPP = self.agent.get("XMPP")

        
        message = await self.receive(timeout=100)

        if message:

            performative = message.get_metadata("performative")

            if performative == "subscribe":

                info = jsonpickle.decode(message.body)

                if info.__class__ == StoreInfo:
                    
                    if info.getName() not in self.agent.get("Store List"):
                        self.agent.get("Store List").append(info)
    

                elif info.__class__ == TransportInfo:

                    if info.getModel() not in self.agent.get("Transport List"):
                        self.agent.get("Transport List").append(info)
            
            elif performative == "inform":

                clientInfo = jsonpickle.decode(message.body)

                if clientInfo.__class__ == ClientInfo:

                    location = clientInfo.getLocation()
                    destination = clientInfo.getDestination()

                    service = self.agent.calculate_service(location,destination)    

                    msg = Message(to=f"{clientInfo.getName()}{XMPP}")
                    msg.body = jsonpickle.encode((service,"ride"))
                    msg.set_metadata("performative", "inform")
                    await self.send(msg)
                
                elif clientInfo.__class__ == StockRequest:

                    stock_prices = self.agent.calculate_price(clientInfo.getType(),clientInfo.getQuantity())
                    msg = Message(to=f"{clientInfo.getClient()}{XMPP}")
                    msg.body = jsonpickle.encode((stock_prices,"stock",clientInfo)) 
                    msg.set_metadata("performative", "inform")
                    await self.send(msg)

            
            elif performative == "request":
                
                
                info = jsonpickle.decode(message.body)

                if info[0].__class__ == ClientInfo:

                    total = jsonpickle.decode(message.body)
                    
                    clientInfo = total[0]
 
                    class_ = total[1]

                    self.agent.print_all_vehicles()

                    closest_vehicle = self.agent.select_vehicle(clientInfo.getLocation(),class_)

                    if closest_vehicle != None:

                        self.agent.print_ride(closest_vehicle.getModel(),clientInfo.getName())

                        msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                        msg_cl.body = jsonpickle.encode((closest_vehicle,"ride"))
                        msg_cl.set_metadata("performative","request")

                        msg_vh = Message(to=f"{closest_vehicle.getModel()}{XMPP}")
                        msg_vh.body = jsonpickle.encode((clientInfo,closest_vehicle.getModel()))
                        msg_vh.set_metadata("performative","request")

                        await self.send(msg_cl)
                        await self.send(msg_vh)

                        closest_vehicle.setAvailability(False)
                    
                    else:

                        print(colored(f"MANAGER ({self.agent.get('Name')}): THERE IS NO AVAILABLE VEHICLE FOR YOUR PREFERENCE AT THE MOMENT", "yellow", attrs=["bold"]))
                        service = self.agent.get("Service")

                        if class_ == "Saver":
                            
                            print(colored(f"MANAGER ({self.agent.get('Name')}): CAN I OFFER YOU OUR STANDARD OPTION?", "yellow", attrs=["bold"]))
                            print(" ")

                            new_service = {'Standard':service["Standard"]}
                            new_class = "Standard"

                            add_to_sender = self.agent.get("Name")

                            closest_vehicle = self.agent.select_vehicle(clientInfo.getLocation(),new_class)
            
                            msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg_cl.body = jsonpickle.encode((new_service,new_class,add_to_sender))
                            msg_cl.set_metadata("performative","propose")
                            await self.send(msg_cl)
                        
                        elif class_ == "Standard":
                            
                            print(colored(f"MANAGER ({self.agent.get('Name')}): CAN I OFFER YOU OUR XL OPTION?", "yellow", attrs=["bold"]))
                            print(" ")
                            
                            new_service = {'XL':service["XL"]}
                            new_class = "XL"
                            
                            add_to_sender = self.agent.get("Name")
            
                            msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg_cl.body = jsonpickle.encode((new_service,new_class,add_to_sender))
                            msg_cl.set_metadata("performative","propose")
                            await self.send(msg_cl)
                        
                        else:

                            print(colored(f"MANAGER ({self.agent.get('Name')}): SORRY, BUT THERE ARE NO MORE OPTIONS AVAILABLE AT THE MOMENT", "yellow", attrs=["bold"]))
                            msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg_cl.body = jsonpickle.encode("None")
                            msg_cl.set_metadata("performative","propose")
                            await self.send(msg_cl)
                
                else:

                    self.agent.print_stock()

                    stock_request = jsonpickle.decode(message.body)

                    clientInfo = stock_request[1]

                    stock_request_tuple = stock_request[2]

                    choosen_store = stock_request[0]
                
                    quantity = stock_request_tuple.getQuantity()

                    stock_type = stock_request_tuple.getType()

                    store_response = self.agent.contact_store(choosen_store,quantity,stock_type)

                   


                    name = self.agent.get("Name")

                    if store_response == True:

                        closest_vehicle = self.agent.food_deliver_vehicle(clientInfo.getLocation())

                        if closest_vehicle != None:
                            
                            print(" ")
                            print(colored(f"MANAGER ({self.agent.get('Name')}): [{choosen_store}] IS PREPARING YOUR REQUEST!","yellow",attrs=["bold"]))

                            self.agent.print_vehicle(closest_vehicle.getModel(),clientInfo.getName())

                            self.agent.remove_stock(choosen_store,quantity,stock_type)

                            msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg_cl.body = jsonpickle.encode((closest_vehicle,"delivery"))
                            msg_cl.set_metadata("performative","request")

                            msg_vh = Message(to=f"{closest_vehicle.getModel()}{XMPP}")
                            msg_vh.body = jsonpickle.encode((clientInfo,closest_vehicle.getModel(),choosen_store,stock_request_tuple,"delivery"))
                            msg_vh.set_metadata("performative","request")

                            await self.send(msg_cl)
                            await self.send(msg_vh)

                            closest_vehicle.setAvailability(False)
                        
                        else:
                            
                            print(" ")
                            print(colored(f"MANAGER ({self.agent.get('Name')}): THERE ARE NO VEHICLES AVAILABLE AT THE MOMENT, PLEASE TRY AGAIN LATER", "yellow", attrs=["bold"]))
                            print(" ")
                            
                            msg = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg.body = jsonpickle.encode(("None"))
                            msg.set_metadata("performative","disconfirm")
                            await self.send(msg)


                    else:
                        
                        if store_response > 0:

                            print(" ")
                            print(colored(f"MANAGER ({self.agent.get('Name')}): {[choosen_store]} DOES NOT HAVE ENOUGH STOCK ", "yellow", attrs=["bold"]))
                            print(colored(f"MANAGER ({self.agent.get('Name')}): ONLY {store_response} LEFT", "yellow", attrs=["bold"]))
                            print(colored(f"MANAGER ({self.agent.get('Name')}): WILL YOU ACCEPT THIS OFFER?", "yellow", attrs=["bold"]))
                            print(" ")

                            msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg_cl.body = jsonpickle.encode((store_response,clientInfo,stock_request_tuple,choosen_store,name,"delivery"))
                            msg_cl.set_metadata("performative","propose")
                            await self.send(msg_cl)

                        else:

                            msg = Message(to=f"{clientInfo.getName()}{XMPP}")
                            msg.body = jsonpickle.encode((choosen_store,clientInfo,stock_request_tuple,"no_stock"))
                            msg.set_metadata("performative","refuse_proposal")
                            await self.send(msg)
                            

                    
            elif performative == "confirm":

                confirmation = jsonpickle.decode(message.body)
                        
                if confirmation != None:     


                    if confirmation[1] == "delivery":

                        print(" ")
                        print(colored("================================================", "yellow", attrs=["bold"]))
                        print(colored(f"DELIVERY FINISHED FOR {confirmation[2]} | CAR -> [{confirmation[0]}]", "yellow", attrs=["bold"]))
                        print(colored("================================================", "yellow", attrs=["bold"]))
                        print(" ")
                       
                    else:   
                        
                        print(" ")
                        print(colored("============================================", "yellow", attrs=["bold"]))
                        print(colored(f"RIDE FINISHED FOR {confirmation[2]} | CAR -> [{confirmation[0]}] ", "yellow", attrs=["bold"]))
                        print(colored("============================================", "yellow", attrs=["bold"]))
                        print(" ")

                    transport_list = self.agent.get("Transport List")

                    for t in transport_list:
                        if t.getModel() == confirmation[0]:
                            t.setAvailability(True)
                            break

            
            elif performative == "accept_proposal":

                info = jsonpickle.decode(message.body)

                store = info[0]
                clientInfo = info[1]
                stock_request = info[2]

                print(colored(f"MANAGER ({self.agent.get('Name')}): [{store}] IS PREPARING YOUR REQUEST!","yellow",attrs=["bold"]))

                closest_vehicle = self.agent.food_deliver_vehicle(clientInfo.getLocation())

                if closest_vehicle != None:

                    self.agent.print_vehicle(closest_vehicle.getModel(),clientInfo.getName())

                    msg_cl = Message(to=f"{clientInfo.getName()}{XMPP}")
                    msg_cl.body = jsonpickle.encode((closest_vehicle,"delivery"))
                    msg_cl.set_metadata("performative","request")

                    msg_vh = Message(to=f"{closest_vehicle.getModel()}{XMPP}")
                    msg_vh.body = jsonpickle.encode((clientInfo,closest_vehicle.getModel(),store,stock_request,"delivery"))
                    msg_vh.set_metadata("performative","request")

                    await self.send(msg_cl)
                    await self.send(msg_vh)

                    closest_vehicle.setAvailability(False)
                
                else:

                    print(" ")
                    print(colored(f"MANAGER ({self.agent.get('Name')}): THERE ARE NO VEHICLES AVAILABLE AT THE MOMENT, PLEASE TRY AGAIN LATER", "yellow", attrs=["bold"]))
                    print(" ")
             
                    msg = Message(to=f"{clientInfo.getName()}{XMPP}")
                    msg.body = jsonpickle.encode(("None"))
                    msg.set_metadata("performative","disconfirm")
                    await self.send(msg)
                    

            elif performative == "propose":

                proposal = jsonpickle.decode(message.body)

                client_offer = proposal[0]
                price = proposal[1]
                choosen_store = proposal[2]
                clientInfo = proposal[3]
                stock_request = proposal[4]

                sender = str(message.sender).split("@")[0]

                acceptable_margin = 0.35


                if client_offer >= (1 - acceptable_margin) * price:

                    print(colored(f"MANAGER ({self.agent.get('Name')}): [{choosen_store}] ACCEPTED YOUR OFFER", "yellow", attrs=["bold"]))
                    msg = Message(to=f"{sender}{XMPP}")
                    msg.body = jsonpickle.encode((choosen_store,clientInfo,stock_request))
                    msg.set_metadata("performative","accept_proposal")
                    await self.send(msg)
                
                else:

                    print(colored(f"MANAGER ({self.agent.get('Name')}): [{choosen_store}] DID NOT ACCEPT YOUR OFFER", "yellow", attrs=["bold"]))
                    print(" ")

                    msg = Message(to=f"{sender}{XMPP}")
                    msg.body = jsonpickle.encode((choosen_store,clientInfo,stock_request))
                    msg.set_metadata("performative","refuse_proposal")
                    await self.send(msg)
                   
        else:

            self.kill()

        
    async def on_end(self):
        await self.agent.stop()
