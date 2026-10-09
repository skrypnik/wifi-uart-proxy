import machine, socket, time, json

import uasyncio as asyncio

from modules import logger, config, leds

LOGGER_CATEGORY = 'UDPS'
log = logger.logger( LOGGER_CATEGORY )

MODE_LED_PIN = 14

COMMON_MODE_START_BYTE = 0
CONFIG_MODE_START_BYTE = 123

#################################################################
# UDP server class
class server:
    
    def __init__( self, configuration ):
        
        self.queue = []
        
        self.configuration = configuration
        
        self.HANDLING_INTERVAL = configuration['common']['handling_interval']
        self.MAX_PACKET_SIZE   = configuration['common']['max_packet_size']
        self.UDP_HEADER_SIZE   = configuration['common']['udp_header_size']
        
        self.listen_address = '0.0.0.0' 
        self.listen_netport = configuration['network']['netport']
        
        log.write( 'Initializing' )
        self.udp = socket.socket( socket.AF_INET, socket.SOCK_DGRAM )   
        self.udp.bind( ( self.listen_address, self.listen_netport ) )
        self.udp.setblocking( False )
        
        log.write( 'Server started on %s %d' % ( self.listen_address, self.listen_netport ) )
        
    def ready( self ):
        
        return len( self.queue )
    
    def put( self, data ):
        
        self.udp.sendto( data, self.address )
    
    def get( self ):
        
        if self.ready():
        
            item = self.queue.pop( 0 )
        
            return item
        
        return None
            
    def handle_common( self, datagram, address ):
        
        data = datagram[self.UDP_HEADER_SIZE:]
        self.address = address
        self.queue.append( data )
    
    def handle_config( self, datagram, address ):
        
        request = json.loads( datagram )
                    
        if request['request'] == 'get':
            
            response = {
                        
                'response': 'get',
                'data': self.configuration
            }
                        
            self.udp.sendto( json.dumps( response ), address )
            
        if request['request'] == 'set':
            
            config.saveConfig( json.dumps( request['data'] ) )
            
            machine.reset()
    
    async def common_udp_handler( self ):
    
        try:
            
            while True:
        
                try:
                
                    datagram, address = self.udp.recvfrom( self.MAX_PACKET_SIZE )
                    
                    if datagram[0] != COMMON_MODE_START_BYTE: continue
                    
                    self.handle_common( datagram, address )
                
                except OSError as exception: pass # log.write( exception )
            
                await asyncio.sleep_ms( self.HANDLING_INTERVAL )
                
        except asyncio.CancelledError: log.write( '[common_udp_handler] Task canceled' )
        
        except Exception as exception: pass # log.write( exception )
    
    async def config_udp_handler( self ):
    
        try:
        
            while True:
            
                try:
                
                    datagram, address = self.udp.recvfrom( self.MAX_PACKET_SIZE )
                    
                    if datagram[0] != CONFIG_MODE_START_BYTE: continue
                    
                    self.handle_config( datagram, address )
                
                except OSError as exception: pass # log.write( exception )
            
                await asyncio.sleep_ms( self.HANDLING_INTERVAL )
                
        except asyncio.CancelledError: log.write( '[config_udp_handler] Task canceled' )
        
        except Exception as exception: pass # log.write( exception )
            