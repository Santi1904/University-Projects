from spade.message import Message
import jsonpickle
from spade.behaviour import CyclicBehaviour
from spade.behaviour import OneShotBehaviour

from Info.ClientInfo import ClientInfo

from termcolor import colored

import random

class ReceiveInfo(CyclicBehaviour):
    
    async def run(self):

        XMPP = self.agent.get("XMPP")
        
        message = await self.receive(timeout=100)

        if message:
                    
            sender = str(message.sender).split("@")[0]

            client_info = ClientInfo(self.agent.get("Name"),self.agent.get("Location"),self.agent.get("Destination"))

            performative = message.get_metadata("performative")

            if performative == "inform":

                service = jsonpickle.decode(message.body)

                if service[1] == "stock":
                    
                    stock_prices = service[0]

                    stores = self.agent.call_prices(stock_prices)

                    store_list = self.agent.get("Stores")

                    store_list.append(stores)


                    if(len(store_list) == 2):

                        stores_sorted = self.agent.sort_by_lowest_price(store_list)

                        self.agent.print_prices(stores_sorted)

                        self.agent.set("Stores", stores_sorted)

                        send_to = next(iter(stores_sorted[0]))

                        choosen_store = next(iter(stores_sorted[0][send_to]))

                        price = stores_sorted[0][send_to][choosen_store]

                        balance = self.agent.get("Money")

                        clientRequest = service[2]


                        if balance >= price:
                            
                            print(" ")
                            print(colored(f"CLIENT ({self.agent.get('Name')}): I WANT TO BUY THE PRODUCT FROM [{send_to}] -> [{choosen_store}] !", 'cyan', attrs=['bold']))
                            print(" ")
                            

                            msg = Message(to=f"{send_to}{XMPP}")
                            msg.body = jsonpickle.encode((choosen_store,client_info,clientRequest))
                            msg.set_metadata("performative", "request")
                            await self.send(msg)
                        
                        else:
                            print(" ")
                            print(colored(f"CLIENT ({self.agent.get('Name')}): I DONT HAVE ENOUGH MONEY TO BUY THE PRODUCT", "cyan", attrs=["bold"]))
                            print(colored(f"CLIENT ({self.agent.get('Name')}): I ONLY HAVE {balance} ", "cyan", attrs=["bold"]))
                            print(colored(f"CLIENT ({self.agent.get('Name')}): WILL YOU ACCEPT THIS MONEY?", "cyan", attrs=["bold"]))
                            print(" ")

                            msg = Message(to=f"{send_to}{XMPP}")
                            msg.body = jsonpickle.encode((balance,price,choosen_store,client_info,clientRequest))
                            msg.set_metadata("performative", "propose")
                            await self.send(msg)
                                
                        
                else:

                    service_dic = self.agent.get("Service")
                    service_dic[sender] = service[0]


                    self.agent.set("Service", service_dic)

                    passengers = self.agent.get("Passengers")

                    service = self.agent.get("Service")

                    request_to = self.agent.select_ride(service,passengers)

                    class_ = request_to[1]

                    if len(request_to[0]) == 2:

                        self.agent.print_services(service)

                        print(" ")
                        print(colored(f"CLIENT ({self.agent.get('Name')}): I WANNA CHOOSE {class_} FROM {sender} !", 'cyan', attrs=['bold']))

                        send_to = request_to[0][0][0]
                        client_info.addSender(send_to)
   
                        msg = Message(to=f"{send_to}{XMPP}")
                        msg.body = jsonpickle.encode((client_info,class_,request_to))
                        msg.set_metadata("performative", "request")
                        await self.send(msg)

            elif performative == "propose":

                new_service = jsonpickle.decode(message.body)

                if len(new_service) != 3:
                        
                        if new_service == "None":
                            
                            print(" ")
                            print(colored(f"CLIENT ({self.agent.get('Name')}): NO VEHICLES AVAILABLE, I'M GOING TO LEAVE", "cyan", attrs=["bold"]))
                            print(" ")
                            self.kill()

                        else:

                            storeStock = new_service[0]
                            clientInfo = new_service[1]
                            stock_request = new_service[2]
                            clientQuantity = stock_request.getQuantity()
                            store = new_service[3]
                            send_to = new_service[4]

                            diff = abs(clientQuantity - storeStock)

                            if diff < 5:

                                print(colored(f"CLIENT ({self.agent.get('Name')}): I ACCEPT YOUR OFFER ","cyan",attrs=["bold"]))
                                print(" ")
                                msg = Message(to=f"{send_to}{XMPP}")
                                msg.body = jsonpickle.encode((store,clientInfo,stock_request))
                                msg.set_metadata("performative", "accept_proposal")
                                await self.send(msg)
                            
                            else:

                                print(colored(f"CLIENT ({self.agent.get('Name')}): THAT OFFER WAS NOT GOOD ENOUGH FOR ME, GOING TO CHECK ANOTHER STORE","cyan",attrs=["bold"]))

                                store_list = self.agent.get("Stores")


                                for item in store_list:
                                    if send_to in item:
                                        if store in item[send_to]:
                                            del item[send_to][store]
                                        if not item[send_to]:
                                            del item[send_to]
                                    

                                for item in store_list:
                                    if item == {}:
                                        store_list.remove(item)


                                if store_list != []:

                                    
                                    self.agent.print_prices(store_list)

                                    send_to = next(iter(store_list[0]))
                                    

                                    choosen_store = next(iter(store_list[0][send_to]))
                                    

                                    price = store_list[0][send_to][choosen_store]

                                    print(" ")
                                    print(colored(f"CLIENT ({self.agent.get('Name')}): I WANT TO BUY THE PRODUCT FROM [{send_to}] => [{choosen_store}] !", 'cyan', attrs=['bold']))
                                    

                                    balance = self.agent.get("Money")

                                    if balance >= price:

                                        msg = Message(to=f"{send_to}{XMPP}")
                                        msg.body = jsonpickle.encode((choosen_store,clientInfo,stock_request))
                                        msg.set_metadata("performative", "request")
                                        await self.send(msg)
                                    
                                    else:

                                        print(colored(f"CLIENT ({self.agent.get('Name')}): I DONT HAVE ENOUGH MONEY TO BUY THE PRODUCT", "cyan", attrs=["bold"]))
                                        print(colored(f"CLIENT ({self.agent.get('Name')}): I ONLY HAVE {balance} ", "cyan", attrs=["bold"]))
                                        print(colored(f"CLIENT ({self.agent.get('Name')}): WILL YOU ACCEPT THIS MONEY?", "cyan", attrs=["bold"]))
                                        print(" ")

                                        msg = Message(to=f"{send_to}{XMPP}")
                                        msg.body = jsonpickle.encode((balance,price,choosen_store,client_info,stock_request))
                                        msg.set_metadata("performative", "propose")
                                        await self.send(msg)

                                else:
                                            
                                        print(colored(f"CLIENT ({self.agent.get('Name')}): NO MANAGERS OR STORES AVAILABLE, I'M GOING TO LEAVE", "cyan", attrs=["bold"]))
                                        print(" ")
                                        self.kill()

    
                else:        
                
                    bin = random.randint(0,1)
                    
                    if bin == 0:

                        request_to = new_service[0]
                        class_ = new_service[1]
                        send_to = new_service[2]


                        print(colored(f"CLIENT ({self.agent.get('Name')}): I ACCEPT YOUR OFFER ","cyan",attrs=["bold"]))

                        if len(request_to) != 0:
                            
                            msg = Message(to=f"{send_to}{XMPP}")
                            msg.body = jsonpickle.encode((client_info,class_,request_to))
                            msg.set_metadata("performative", "request")
                            await self.send(msg)

                    elif bin == 1:
                        
                        print(colored(f"CLIENT ({self.agent.get('Name')}): I REFUSE YOUR OFFER AND NOW I'M GOING TO LOOK FOR ANOTHER MANAGER ","cyan",attrs=["bold"]))

                        service = self.agent.get("Service")

                        service.pop(new_service[2])


                        if (service != {}):


                            passengers = self.agent.get("Passengers")

                            request_to = self.agent.select_ride(service,passengers)

                            send_to = next(iter(service))

                            class_ = new_service[1]

                            self.agent.print_services(service)

                            msg = Message(to=f"{send_to}{XMPP}")
                            msg.body = jsonpickle.encode((client_info,class_,request_to))
                            msg.set_metadata("performative", "request")
                            await self.send(msg)
                    
                        else:

                            print(colored(f"CLIENT ({self.agent.get('Name')}): THERE ARE NO SERVICES AVAILABLE AT THE MOMENT","cyan",attrs=["bold"]))
                            self.kill()


            elif performative == "request":

                confirmation = jsonpickle.decode(message.body)

                if confirmation != None:

                    if confirmation[1] == "delivery":

                        pass

                    else:
                        
                        print(colored(f"CLIENT ({self.agent.get('Name')}): WAITING FOR MY RIDE -> ({confirmation[0].getModel()})","cyan",attrs=["bold"]))


            elif performative == "accept_proposal":

                info = jsonpickle.decode(message.body)
                sender = str(message.sender).split("@")[0]

                choosen_store = info[0]
                clientInfo = info[1]
                stock_request = info[2]


                msg = Message(to=f"{sender}{XMPP}")
                msg.body = jsonpickle.encode((choosen_store,clientInfo,stock_request))
                msg.set_metadata("performative", "request")
                await self.send(msg)
            
            elif performative == "refuse_proposal":

                info = jsonpickle.decode(message.body)
                send_to = str(message.sender).split("@")[0]

                if len(info) > 3:
                    print(colored(f"CLIENT ({self.agent.get('Name')}): THIS STORE DIDN'T HAVE  ANY STOCK, GOING TO CHECK OTHER STORE","cyan",attrs=["bold"]))
                else:
                    print(colored(f"CLIENT ({self.agent.get('Name')}): MY OFFER WAS REJECT BY THE STORE, GOING TO CHECK OTHER STORE","cyan",attrs=["bold"]))

                choosen_store = info[0]
                clientInfo = info[1]
                stock_request = info[2]

                store_list = self.agent.get("Stores")


                for item in store_list:
                    if send_to in item:
                        if choosen_store in item[send_to]:
                            del item[send_to][choosen_store]
                        if not item[send_to]:
                            del item[send_to]
                        
                    

                for item in store_list:
                    if item == {}:
                        store_list.remove(item)

                if store_list != []:
                   
                    send_to = next(iter(store_list[0]))
                    choosen_store = next(iter(store_list[0][send_to]))
                    price = store_list[0][send_to][choosen_store]

                    balance = self.agent.get("Money")

                    if balance >= price:

                        print(" ")
                        print(colored(f"CLIENT ({self.agent.get('Name')}): I WANT TO BUY THE PRODUCT FROM [{send_to}] -> [{choosen_store}] !", 'cyan', attrs=['bold']))

                        msg = Message(to=f"{send_to}{XMPP}")
                        msg.body = jsonpickle.encode((choosen_store,clientInfo,stock_request))
                        msg.set_metadata("performative", "request")
                        await self.send(msg)
                    
                    else:
                                
                        print(colored(f"CLIENT ({self.agent.get('Name')}): I DONT HAVE ENOUGH MONEY TO BUY THE PRODUCT", "cyan", attrs=["bold"]))
                        print(colored(f"CLIENT ({self.agent.get('Name')}): I ONLY HAVE {balance} ", "cyan", attrs=["bold"]))
                        print(colored(f"CLIENT ({self.agent.get('Name')}): WILL YOU ACCEPT THIS MONEY?", "cyan", attrs=["bold"]))

                        msg = Message(to=f"{send_to}{XMPP}")
                        msg.body = jsonpickle.encode((balance,price,choosen_store,client_info,stock_request))
                        msg.set_metadata("performative", "propose")
                        await self.send(msg)
                
                else:

                    print(colored(f"CLIENT ({self.agent.get('Name')}): NO MANAGERS OR STORES AVAILABLE, I'M GOING TO LEAVE", "cyan", attrs=["bold"]))
                    print(" ")
                    self.kill()
            
            elif performative == "disconfirm":

                print(colored(f"CLIENT ({self.agent.get('Name')}): NO VEHICLES AVAILABLE, I'M GOING TO LEAVE", "cyan", attrs=["bold"]))
                print(" ")
                self.kill()
                


        else:
            self.kill()


    async def on_end(self):
        await self.agent.stop()