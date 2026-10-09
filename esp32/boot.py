from modules import config, logger, wifi, leds

MODE_LED_PIN = 14

MODE_REBOOT_COLOR = ( 64, 0, 0 )

#################################################################
# Converter initializer class

class initializator:
    
    #############################################################
    # Constructor, initializes logger and WLAN access point
    
    def __init__( self, config ):
        
        self.config = config
        
        self.LOGGER_CATEGORY = 'WIFI'
        self.log = logger.logger( self.LOGGER_CATEGORY )
        
        self.point = wifi.point( self.config )
        
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

leds.pixel.lightPixel( MODE_LED_PIN, MODE_REBOOT_COLOR )

log.write('Reading configuration')
configuration = config.readConfig()

log.write('Initializing')
init = initializator( configuration )

log.write('Starting')
init.start()