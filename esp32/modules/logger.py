#################################################################
# Logger class

class logger:
    
    def __init__( self, category ):
        
        self.category = category
        
    def write( self, message ):
        
        print( '[%s] %s' % ( self.category, message ) )
        
    def write_hex( self, message ):
        
        print( '[%s] %s' % ( self.category, bytes(message).hex() ) )