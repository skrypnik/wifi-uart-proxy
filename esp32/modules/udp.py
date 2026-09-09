from modules import logger

import socket, time

LOGGER_CATEGORY = 'UDP'
log = logger.logger( LOGGER_CATEGORY )

#################################################################
# UDP server class

class server:
    
    def __init__( self, configuration ):
        
        self.configuration = configuration
        
        self.HANDLING_INTERVAL = configuration['common']['handling_interval']
        self.MAX_PACKET_SIZE   = configuration['common']['max_packet_size']
        
        # \todo calculate listen addres with address and netmask from configuration
        self.listen_address = '0.0.0.0' 
        self.listen_netport = configuration['network']['netport']
        
        log.write( 'Initializing UDP' )
        self.udp = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )   
        self.udp.bind( (self.listen_address, self.listen_netport) )
        
    def put( self, data, address ):
        
        # \todo lock handler thread
        
        log.write( '>>> (%s) %s' % (address, data) )
        
        self.udp.sendto( data, address )
        
    def get( self ):
        
        datagramm, address = self.udp.recvfrom( self.MAX_PACKET_SIZE )
        
        log.write( '<<< (%s) %s' % ( address, datagramm ) )
        
        return ( address, datagramm )
        
    def handling_loop( self ):
        
        while True:
            
            # \todo handle packet queue here
            
            time.sleep_ms( self.HANDLING_INTERVAL )
            