from machine import UART

import _thread, time

class handler:
    
    def __init__( self, configuration ):
        
        self.MAX_PACKET_SIZE = 1400
        
        self.configuration = configuration
        
        self.PORT_NUMBER = configuration['uart']['port_number']
        self.BAUD_RATE   = configuration['uart']['baud_rate']
        self.TX_GPIO     = configuration['uart']['tx_gpio']
        self.RX_GPIO     = configuration['uart']['tx_gpio']
        self.PARITY      = configuration['uart']['parity']
        self.INVERT      = configuration['uart']['invert']
        self.BITS        = configuration['uart']['bits']
        self.STOP        = configuration['uart']['stop']
        
        self.uart = UART( self.PORT_NUMBER, baudrate=self.BAUD_RATE, tx=self.TX_GPIO, rx=self.RX_GPIO )
        self.uart.init( bits=self.BITS, stop=self.STOP, parity=self.PARITY, invert=self.INVERT )
        
    def put( self, data ):
        
        # \todo lock handler thread
        
        self.uart.write( data )
        
    def get( self ):
        
        self.uart.read( self.MAX_PACKET_SIZE )
        
    def queue_handler( self ):
        
        # \todo put it to thread
        
        while True:
            
            # \todo handle packet queue here
            
            pass
        