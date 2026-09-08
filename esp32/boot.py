from modules import config, logger, wlan

#################################################################
# Converter initializer class

class initializator:
    
    #############################################################
    # Constructor, initializes logger and WLAN access point
    
    def __init__( self, config ):
        
        self.config = config
        
        self.LOGGER_CATEGORY = 'WLAN'
        
        self.logger = logger.logger( self.LOGGER_CATEGORY )
        
        self.point = wlan.point( self.config )
        
    #############################################################
    # Starts WLAN access point and waits for station connected
    
    def start( self ):

        self.logger.write( 'Configuring access point' )

        self.point.tuneAccessPoint()

        self.logger.write( 'Waiting for station' )

        self.point.waitForStation()

        self.logger.write( 'Station connected' )

#################################################################
# Converter initialization

configuration = config.readConfig()

init = initializator( configuration )
init.start()
