from spade.behaviour import CyclicBehaviour
from spade.message import Message

import jsonpickle
import asyncio
from termcolor import colored

class ExecuteRide(CyclicBehaviour):

    async def run(self):

        XMPP = self.agent.get("XMPP")

        message = await self.receive(timeout=100)

        if message:

            performative = message.get_metadata("performative")
            sender = str(message.sender).split("@")[0]

            if performative == "request":

                full_msg = jsonpickle.decode(message.body)

                if len(full_msg) != 2:

                    cli_location = full_msg[0].getLocation()
                    client_name = full_msg[0].getName()

                    print(" ")
                    print(colored("==============================================", "green", attrs=["bold"]))
                    print(colored(f"= DELIVERING TO {full_msg[0].getName()}'s LOCATION: " + str(cli_location), "green", attrs=["bold"]))
                    print(colored("==============================================", "green", attrs=["bold"]))
                    print("")

                    await asyncio.sleep(3)
                    print(" ")
                    print(colored("==========================================", "green", attrs=["bold"]))
                    print(colored(f"[{self.agent.get('Model')}] ARRIVED AT {full_msg[0].getName()}'s LOCATION", "green", attrs=["bold"]))
                    print(colored("==========================================", "green", attrs=["bold"]))
                    print(" ")

                    self.agent.set("Location",cli_location)

                    msg_manager = Message(to=f"{sender}{XMPP}")
                    msg_manager.body = jsonpickle.encode((full_msg[1],"delivery",client_name))
                    msg_manager.set_metadata("performative", "confirm")
                    await self.send(msg_manager)


                else:    

                    clientInfo = full_msg[0]

                    cli_location = clientInfo.getLocation()
                    destination = clientInfo.getDestination()
                    client_name = clientInfo.getName()

                    print(" ")
                    print(colored("=================================", "green", attrs=["bold"]))
                    print(colored(f"= {client_name} LOCATION: {cli_location}", "green", attrs=["bold"]))
                    print(colored("=================================", "green", attrs=["bold"]))
                    print(" ")

                    await asyncio.sleep(3)
                    print(" ")
                    print(colored("=====================================================", "green", attrs=["bold"]))
                    print(colored(f"= [{self.agent.get('Model')}] ARRIVED AT {client_name} LOCATION", "green", attrs=["bold"]))
                    print(colored("=====================================================", "green", attrs=["bold"]))
                    print(" ")
                    print(colored("=======================================", "green", attrs=["bold"]))
                    print(colored(f"{client_name}'s DESTINATION: {destination}", "green", attrs=["bold"]))
                    print(colored("=======================================", "green", attrs=["bold"]))
                    print(" ")

                    self.agent.set("Location",destination)

                    await asyncio.sleep(5)

                    print(colored("====================================================", "green", attrs=["bold"]))
                    print(colored(f"[{self.agent.get('Model')}] ARRIVED AT {client_name}'s DESTINATION {destination}", "green", attrs=["bold"]))
                    print(colored("====================================================", "green", attrs=["bold"]))
                    print(" ")

                    msg_manager = Message(to=f"{sender}{XMPP}")
                    msg_manager.body = jsonpickle.encode((full_msg[1],"ride",client_name))
                    msg_manager.set_metadata("performative", "confirm")
                    await self.send(msg_manager)
        
        else:
            self.kill()