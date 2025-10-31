import sys
import threading
from myparser import Parser
from packet import Packet
from UDPsender import UDPsender
from UDPreceiver import UDPreceiver
from cache import Cache
    

def run(config_file):

    senders = []
    hosts = []
    filename = "movie.Mjpeg"

    

    parser = Parser(config_file)
    parsed_file, node_name = parser.parse_json()

    cache = Cache()

    
    if parsed_file["host"] is not None:
        for host in parsed_file["host"]:
            hosts.append(host)

    if parsed_file["nb"] is not None:
        for nb in parsed_file["nb"]:
            sender = UDPsender(node_name,hosts,nb)
            senders.append(sender)


    for host in hosts:    
        receiver = UDPreceiver(node_name,senders,hosts,cache)
        host_socket = threading.Thread(target=receiver.udp_bind,args=(host,))
        host_socket.start()
            
        
    for sender, host in zip(senders, hosts):
        sender.addHost(host)
        conn_socket = threading.Thread(target=sender.udp_connect,args=())
        conn_socket.start()
        if node_name == 'rp':  
            send_socket_thread = threading.Thread(target=sender.latencyTest, args=())
            send_socket_thread.start()

        elif node_name[0] == 'c':
            packet = Packet('VR',host)
            packet.addFilename(filename)
            packet.packet_encode()
            packetVideoRequest = threading.Thread(target=sender.videoRequest, args=(packet,))
            packetVideoRequest.start()
  

if __name__ == '__main__':
    config_file = sys.argv[1]
    run(config_file)
