import sys
from tkinter import Tk
from clientHandler import ClientHandler
import os
import time



class Client:

	def __init__(self, host, senders, node_name, rtpPort):
		self.host = host
		self.senders = senders
		self.node_name = node_name
		self.rtpPort = rtpPort

	def client_gui(self):

		rtpAddr = self.host.split(':')[0]

		next_sender = self.senders[0]
		server_ip, server_port = next_sender.nb_address.split(':')

		os.environ['DISPLAY'] = ':0.0'
		root = Tk()

	
		# Create a new client
		time.sleep(10)
		app = ClientHandler(root,server_ip,server_port,rtpAddr,self.rtpPort,self.senders)
		app.master.title("RTPClient")
		root.mainloop()
	