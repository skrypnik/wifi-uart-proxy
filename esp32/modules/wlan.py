import network, time

class point:
    
    def __init__( self, configuration ):
        
        self.configuration = configuration
        
        self.SSID     = configuration['network']['ssid']
        self.CHANNEL  = configuration['network']['channel']
        self.ADDRESS  = configuration['network']['address']
        self.NETMASK  = configuration['network']['netmask']
        self.PASSWORD = configuration['network']['password']
    
    def tuneAccessPoint( self ):
    
        self.access_point = network.WLAN( network.AP_IF )
    
        self.access_point.active( True )
        self.access_point.ifconfig( (self.ADDRESS, self.NETMASK, '127.0.0.1', '127.0.0.1') )
        self.access_point.config( ssid = self.SSID, channel = self.CHANNEL, password = self.PASSWORD, authmode = network.AUTH_WPA_WPA2_PSK )
    
        while not self.access_point.active(): time.sleep_ms( 10 )

    def waitForStation( self ):
        
        interval = self.configuration['common']['handling_interval']
        
        while not self.access_point.isconnected(): time.sleep_ms( interval )