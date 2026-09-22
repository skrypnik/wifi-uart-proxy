from modules import controls, logger, config, leds, udp

import uasyncio as asyncio

import time

LOGGER_CATEGORY = 'MAIN'
log = logger.logger( LOGGER_CATEGORY )

#################################################################
# Reading converter configuration, setting global constants

configuration = config.readConfig()

HANDLING_INTERVAL = configuration['common']['handling_interval']

MODE_COMMON_COLOR = (0, 64, 0)
MODE_CONFIG_COLOR = (0, 0, 64)
MODE_REBOOT_COLOR = (64, 0, 0)

MODE_LED_PIN = 14
MODE_KEY_PIN = 15

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

async def main():
    
    # Setting up UDP server
    server = udp.server( configuration )
    
    # Setting up mode settings, starts default UDP handler
    task = asyncio.create_task( server.common_udp_handler() )
    leds.pixel.lightPixel( MODE_LED_PIN, MODE_COMMON_COLOR )
    mode_button = controls.button( MODE_KEY_PIN )
    mode = Mode()

    while True:
        
        if mode_button.clicked():
            
            mode.invert()
            
            if mode.value == Mode.COMMON_MODE:
                
                log.write( 'Mode changed: <COMMON> mode enabled' )
                leds.pixel.lightPixel( MODE_LED_PIN, MODE_COMMON_COLOR )
                
                task.cancel()
                await task
                task = asyncio.create_task( server.common_udp_handler() )
                
            if mode.value == Mode.CONFIG_MODE:
                
                log.write( 'Mode changed: <CONFIG> mode enabled' )
                leds.pixel.lightPixel( MODE_LED_PIN, MODE_CONFIG_COLOR )
                
                task.cancel()
                await task
                task = asyncio.create_task( server.config_udp_handler() )
        
        await asyncio.sleep_ms( 500 )

#################################################################
# Runing main thread

asyncio.run( main() )
