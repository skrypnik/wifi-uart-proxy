from modules import logger, config, uart, udp

import time

LOGGER_CATEGORY = 'MAIN'
log = logger.logger( LOGGER_CATEGORY )

#################################################################
# Reading converter configuration, setting global constants

log.write('Reading configuration')
configuration = config.readConfig()

HANDLING_INTERVAL = configuration['common']['handling_interval']

#################################################################
# Main thread handler function

def main():
    
    log.write( 'Creating UART handler' )
    uart_handler = uart.handler( configuration )
    
    log.write( 'Creating UDP handler' )
    udp_server = udp.server( configuration )
    
    log.write( 'Starting main loop' )
    loop()
        
#################################################################
# Main thread handler function
def loop():
    
    while True:
        
        time.sleep_ms( HANDLING_INTERVAL )
    
#################################################################
# Makes main() function as start point

if __name__ == '__main__': main()
 