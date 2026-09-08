import json

class parity:
    
    EVEN = 0
    ODD  = 1
    NONE = 3

def readConfig():
    
    with open( 'config.json', 'rb' ) as file:
    
        data = file.read()
        
        config = json.loads( data )
        
        # We can't stores in JSON python None value, it equals to 3 in config file
        # The remaining values corresponds to the values of the UART class
        if config['uart']['parity'] == parity.NONE: config['uart']['parity'] = None
    
        return config