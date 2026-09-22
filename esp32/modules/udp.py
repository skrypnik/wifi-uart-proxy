import socket, time, json

import uasyncio as asyncio

from modules import logger, config, queue

LOGGER_CATEGORY = 'UDP'
log = logger.logger( LOGGER_CATEGORY )

#################################################################
# UDP server class
class server:
    
    def __init__( self, configuration ):
        
        self.queue = queue.async_queue()
        
        self.configuration = configuration
        
        self.HANDLING_INTERVAL = configuration['common']['handling_interval']
        self.MAX_PACKET_SIZE   = configuration['common']['max_packet_size']
        
        self.listen_address = '0.0.0.0' 
        self.listen_netport = configuration['network']['netport']
        
        log.write( 'Initializing' )
        self.udp = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )   
        self.udp.bind( ( self.listen_address, self.listen_netport ) )
        self.udp.setblocking( False )
        
        log.write( 'Server started on %s %d' % ( self.listen_address, self.listen_netport ) )
        
    def put( self, data, address ):
        
        # \todo
        
        pass
        
    def get( self ):
        
        if not self.queue.empty(): 
        
            datagram, address = await self.queue.get()
        
            return ( datagram, addresss )
        
    def ready( self ):
        
        return not self.queue.empty()
    
    def unpack( self, datagram ):

        header = datagram[0:9]

        if header[0] == 0:
            
            self.handle_common( datagram )
            
            return
        
        self.handle_cofig( datagram )
            
    def handle_common( self, datagram, address ):
        
        await self.queue.put( ( address, datagram ) )
    
    def handle_config( self, datagram, address ):
        
        log.write( datagram )
        
        request = json.loads( datagram )
                    
        if request['request'] == 'get':
                        
            log.write( request )
            
            response = {
                        
                'response': 'get',
                'data': self.configuration
            }
            
            log.write( address )
                        
            self.udp.sendto( json.dumps( response ), address )
        
    
    async def common_udp_handler( self ):
    
        try:
            
            while True:
        
                try:
                
                    datagram, address = self.udp.recvfrom( self.MAX_PACKET_SIZE )
                    
                    if datagram[0] != 0: continue
                    
                    log.write( datagram )
        
                    # self.handle_common( datagram, address )
                
                except OSError as exception:
                
                    if exception.errno == errno.EAGAIN: log.write( '[common_udp_handler] No data received' )
                    else: log.write( '[common_udp_handler] While reading, socket error occured' )
            
                await asyncio.sleep_ms( 500 )
                
        except asyncio.CancelledError: log.write( '[common_udp_handler] Task canceled' )
        
        except Exception as exception: log.write( '[common_udp_handler] Error canceling task' )
    
    async def config_udp_handler( self ):
    
        try:
        
            while True:
            
                try:
                
                    datagram, address = self.udp.recvfrom( self.MAX_PACKET_SIZE )
                    
                    if datagram[0] != 123: continue
                
                    self.handle_config( datagram, address )
                
                except OSError as exception:
                
                    if exception.errno == errno.EAGAIN: log.write( '[config_udp_handler] No data received' )
                    else: log.write( '[config_udp_handler] While reading, socket error occured' )
            
                await asyncio.sleep_ms( 500 )
                
        except asyncio.CancelledError: log.write( '[config_udp_handler] Task canceled' )
        
        except Exception as exception: log.write( '[config_udp_handler] Error canceling task' )
            