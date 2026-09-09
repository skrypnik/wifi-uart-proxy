from machine import UART

from modules import logger

import _thread, time

LOGGER_CATEGORY = 'UART'
log = logger.logger( LOGGER_CATEGORY )

#################################################################
# UART handler class

class handler:
    
    def __init__( self, configuration ):
        
        self.configuration = configuration
        
        self.MAX_PACKET_SIZE = configuration['common']['max_packet_size']
        
        self.PORT_NUMBER = configuration['uart']['port_number']
        self.BAUD_RATE   = configuration['uart']['baud_rate']
        self.TX_GPIO     = configuration['uart']['tx_gpio']
        self.RX_GPIO     = configuration['uart']['rx_gpio']
        self.PARITY      = configuration['uart']['parity']
        self.INVERT      = configuration['uart']['invert']
        self.BITS        = configuration['uart']['bits']
        self.STOP        = configuration['uart']['stop']
        
        log.write('Initializing UART')
        self.uart = UART( self.PORT_NUMBER, baudrate=self.BAUD_RATE, tx=self.TX_GPIO, rx=self.RX_GPIO )
        self.uart.init( bits=self.BITS, stop=self.STOP, parity=self.PARITY, invert=self.INVERT )
        
    def put( self, data ):
        
        # \todo lock handler thread
        
        log.write( ' >>> %s' % data )
        
        self.uart.write( data )
        
    def get( self ):
        
        data = self.uart.read( self.MAX_PACKET_SIZE )
        
        if data != None: log.write( ' <<< %s' % data )
        
        return data
        
    def handling_loop( self ):
        
        # \todo put it to thread
        
        while True:
            
            # \todo handle packet queue here
            
            time.sleep_ms( self.HANDLING_INTERVAL )
        