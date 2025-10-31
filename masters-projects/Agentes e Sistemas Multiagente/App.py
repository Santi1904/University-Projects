from Agents.Store import Store
from Agents.Uber import Uber
from Agents.Glovo import Glovo
from Agents.Freenow import Freenow
from Agents.Car import Car
from Agents.Van import Van
from Agents.Moto import Moto
from Agents.Client import Client
from spade import quit_spade

from termcolor import colored

import time

PASSWORD = "MOPASSWORD"
XMPP = "@santi1904"



class App:

    def run_app(self):

        managers = ["uber","freenow","glovo"]
        stores = ["McDonalds","BurgerKing","KFC","Subway","TacoBell","Wendys","PizzaHut","DunkinDonuts","Starbucks","Chipotle"]
        cars = ["Mazda","Renault","Mercedes","Fiat"]
        motos = ["Yamaha","Honda","Suzuki","Kawasaki"]
        vans = ["Transit","Sprinter","Ducato","Crafter"]
        clients_20 = ["Sara","Duarte","Santiago","Chica","Chico","Pablo","Maria","Juan","Pedro","Luis","Ana","Lucia",
                      "Sofia","Carlos","Javier","Jorge","Raul","Rosa","Laura","Lola"] # 20 clients 



        clients_50 = ["Ana", "Bruno", "Carlos", "Diana", "Eduardo", "Fernanda", "Gustavo", "Helena", "Igor", "Joana",
                    "Karla", "Lucas", "Maria", "Nuno", "Olívia", "Paulo", "Quirino", "Rita", "Sofia", "Tiago",
                    "Ursula", "Vítor", "Wesley", "Xavier", "Yara", "Zeca", "Alexandre", "Beatriz", "Catarina", "Daniel",
                    "Eva", "Fábio", "Gabriela", "Henrique", "Inês", "Jorge", "Kátia", "Leonardo", "Marta", "Natália",
                    "Oscar", "Patrícia", "Quintino", "Raquel", "Sérgio", "Teresa", "Ulisses", "Vanessa", "Wagner", "Ximena"] # 50 clients


        clients_100 = ["Ana", "Bruno", "Carlos", "Diana", "Eduardo", "Fernanda", "Gustavo", "Helena", "Igor", "Joana",
                    "Karla", "Lucas", "Maria", "Nuno", "Olívia", "Paulo", "Quirino", "Rita", "Sofia", "Tiago",
                    "Ursula", "Vítor", "Wesley", "Xavier", "Yara", "Zeca", "Alexandre", "Beatriz", "Catarina", "Daniel",
                    "Eva", "Fábio", "Gabriela", "Henrique", "Inês", "Jorge", "Kátia", "Leonardo", "Marta", "Natália",
                    "Oscar", "Patrícia", "Quintino", "Raquel", "Sérgio", "Teresa", "Ulisses", "Vanessa", "Wagner", "Ximena",
                    "André", "Bárbara", "Clara", "Diogo", "Elisa", "Francisco", "Gonçalo", "Hugo", "Isabel", "José",
                    "Kelly", "Luís", "Matilde", "Nelson", "Otávio", "Pedro", "Quirina", "Renata", "Sandra", "Tomás",
                    "Úrsula", "Vera", "William", "Xana", "Yasmin", "Zélia", "António", "Bianca", "Cristina", "David",
                    "Eduarda", "Filipe", "Guilherme", "Helder", "Irene", "Júlia", "Kim", "Lourenço", "Miguel", "Nádia",
                    "Orlando", "Paula", "Quaresma", "Rui", "Simone", "Tatiana", "Ulisses", "Vitória", "Wesley", "Xiomara"] # 100 clients


        managers_list = []
        locals_list = []
        cars_list = []
        motos_list = []
        vans_list = []
        clients_list = []



        #uber_jid = "uber"
        uber = Uber(f"uber{XMPP}", PASSWORD)
        uber.set("XMPP",XMPP)
        u = uber.start(auto_register=True)
        u.result()
        managers_list.append(uber)

        glovo = Glovo(f"glovo{XMPP}", PASSWORD)
        glovo.set("XMPP",XMPP)
        g = glovo.start(auto_register=True)
        g.result()
        managers_list.append(glovo)

        freenow = Freenow(f"freenow{XMPP}",PASSWORD)
        freenow.set("XMPP",XMPP)
        f = freenow.start(auto_register=True)
        f.result()
        managers_list.append(freenow)

        time.sleep(1)

        for car in cars:
            car = Car(f"{car}{XMPP}", PASSWORD)
            car.set("XMPP",XMPP)
            c = car.start(auto_register=True)
            c.result()
            cars_list.append(car)

        time.sleep(1)


        for store in stores:
            local = Store(f"{store}{XMPP}",PASSWORD)
            local.set("XMPP",XMPP)
            l = local.start(auto_register=True)
            l.result()
            locals_list.append(local)



        for van in vans:
            van = Van(f"{van}{XMPP}",PASSWORD)
            van.set("XMPP",XMPP)
            v = van.start(auto_register=True)
            v.result()
            vans_list.append(van)

        print(" ")
        print(colored("=======================================","red",attrs=["bold"]))
        print(colored("== INICIALIZANDO SISTEMA MULTIAGENTE ==", "red", attrs=["bold"]))
        print(colored("=======================================", "red", attrs=["bold"]))
        print(" ")

        time.sleep(1)


        for moto in motos:
            moto = Moto(f"{moto}{XMPP}",PASSWORD)
            moto.set("XMPP",XMPP)
            m = moto.start(auto_register=True)
            m.result()
            motos_list.append(moto)

        time.sleep(1)


        for i in range(0,len(clients_100)):

            if i % 2 == 0:
               time.sleep(1)

            client = Client(f"{clients_100[i]}{XMPP}",PASSWORD)
            client.set("Managers",managers)
            client.set("XMPP",XMPP)
            cl = client.start(auto_register=True)
            cl.result()
            clients_list.append(client)


        while uber.is_alive() and glovo.is_alive() and freenow.is_alive():
            try:
                time.sleep(1)
            except KeyboardInterrupt:

                for local in locals_list:
                    local.stop()

                for car in cars_list:
                    car.stop()

                for moto in motos_list:
                    moto.stop()

                for van in vans_list:
                    van.stop()

                for client in clients_list:
                    client.stop()

                break
            
        print("ACABOU")

        quit_spade()


if __name__ == "__main__":

    app = App()
    app.run_app()

