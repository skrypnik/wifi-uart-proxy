from modules import config, uart

import time

#################################################################
# Reading converter configuration, setting global constants

configuration = config.readConfig()

HANDLING_INTERVAL = configuration['common']['handling_interval']

#################################################################
# Main thread handler function

def main():
    
    uart_handler = uart.handler( configuration )
    
    while True:
        
        time.sleep_ms( HANDLING_INTERVAL )
        
#################################################################
# Makes main() function as start point

if __name__ == '__main__': main()
 