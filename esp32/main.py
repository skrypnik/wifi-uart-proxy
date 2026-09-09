from modules import logger, config, controls, uart, udp, leds

import time, json

LOGGER_CATEGORY = 'MAIN'
log = logger.logger( LOGGER_CATEGORY )

#################################################################
# Reading converter configuration, setting global constants

log.write('Reading configuration')
configuration = config.readConfig()

HANDLING_INTERVAL = configuration['common']['handling_interval']
MODE_BUTTON_PIN = 15
INDICATOR_PIN = 14

#################################################################
# Operable mode
class Mode:
    
    COMMON_MODE = 0
    CONFIG_MODE = 1
    
    def __init__( self ):
        
        self.value = self.COMMON_MODE
        
    def invert( self ):
        
        self.value = self.value ^ 1

#################################################################
# Main thread handler function
def main():
    
    log.write( 'Creating UDP handler' )
    udp_server = udp.server( configuration )
    
    log.write( 'Creating UART handler' )
    uart_handler = uart.handler( configuration )
    
    log.write( 'Starting main loop' )
    loop( udp_server, uart_handler )
        
#################################################################
# Main thread handler function
def loop( udp_server, uart_handler ):
    
    leds.pixel.lightPixel( INDICATOR_PIN, (0, 64, 0) )
    
    mode = Mode()
    
    while True:
        
        if controls.button.clicked( MODE_BUTTON_PIN ):
            
            log.write( 'Mode changed' )
            mode.invert()
            
            if mode.value == Mode.COMMON_MODE:
                
                leds.pixel.lightPixel( INDICATOR_PIN, (0, 64, 0) )
                
            if mode.value == Mode.CONFIG_MODE:
                
                leds.pixel.lightPixel( INDICATOR_PIN, (0, 0, 64) )
        
        val = mode.value
        
        print( '%d' % val )
        
        if mode.value == Mode.COMMON_MODE:
        
            commonModeHandler( udp_server, uart_handler )
            
            continue
        
        configModeHandler( udp_server )
        
def commonModeHandler( udp_server, uart_handler ):
        
    data = uart_handler.get()
    
    time.sleep_ms( HANDLING_INTERVAL )

def configModeHandler( udp_server ):
    
    datagramm, address = udp_server.get()
    
    response = json.loads( datagramm )
    
    if respone['command'] == 'search':
        
        reply = {
        
            'command': 'config',
            'payload': configuration
        }
        
        sock.sendto( json.dumps( reply ), address )
        
    if respone['command'] == 'config':
    
        pass
    
    time.sleep_ms( HANDLING_INTERVAL )
    
#################################################################
# Makes main() function as start point
if __name__ == '__main__': main()
 