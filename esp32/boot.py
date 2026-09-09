from modules import config, logger, wlan, leds

#################################################################
# Converter initializer class

class initializator:
    
    #############################################################
    # Constructor, initializes logger and WLAN access point
    
    def __init__( self, config ):
        
        self.config = config
        
        self.LOGGER_CATEGORY = 'WLAN'
        self.log = logger.logger( self.LOGGER_CATEGORY )
        
        self.point = wlan.point( self.config )
        
    #############################################################
    # Starts WLAN access point and waits for station connected
    
    def start( self ):

        self.log.write( 'Configuring access point' )
        self.point.tuneAccessPoint()

        self.log.write( 'Waiting for station' )
        self.point.waitForStation()

        self.log.write( 'Station connected' )

#################################################################
# Converter initialization

LOGGER_CATEGORY = 'BOOT'
log = logger.logger( LOGGER_CATEGORY )

INDICATOR_PIN = 14
leds.pixel.lightPixel( INDICATOR_PIN, (128, 64, 0) )

log.write('Reading configuration')
configuration = config.readConfig()

log.write('Initializing WLAN')
init = initializator( configuration )

log.write('Starting WLAN')
init.start()
