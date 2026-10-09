from modules import logger

import uasyncio as asyncio

import json

LOGGER_CATEGORY = 'CONFIG'
log = logger.logger( LOGGER_CATEGORY )

class parity:
    
    EVEN = 0
    ODD  = 1
    NONE = 3

def readConfig():
    
    with open( 'config.json', 'rb' ) as file:
    
        data = file.read()
        
        config = json.loads( data )
        
        if config['uart']['parity'] == parity.NONE: config['uart']['parity'] = None
    
        return config
    
def saveConfig( data ):
    
    log.write( 'Rewriting config file...' )
    
    with open( 'config.json', 'w' ) as file:
        
        file.write( data )
        
    log.write( 'Success.' )
    