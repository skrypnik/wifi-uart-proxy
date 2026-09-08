import socket, time

#################################################################
# UDP server class

class server:
    
    def __init_( self, configuration ):
        
        self.configuration = configuration
        
        self.HANDLING_INTERVAL = configuration['common']['handling_interval']
        self.MAX_PACKET_SIZE   = configuration['common']['max_packet_size']
        
        # \todo calculate listen addres with address and netmask from configuration
        self.listen_address = '0.0.0.0' 
        self.listen_netport = configuration['network']['netport']
        
        self.socket = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )
      
        self.socket.bind( (host, port) )
        
    def put( self, data, address ):
        
        # \todo lock handler thread
        
        sock.sendto( data, address )
        
    def get( self ):
        
        data, address = self.socket.recvfrom( self.MAX_PACKET_SIZE )
        
    def handling_loop( self ):
        
        while True:
            
            # \todo handle packet queue here
            
            time.sleep_ms( self.HANDLING_INTERVAL )
            