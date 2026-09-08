class logger:
    
    def __init__( self, category ):
        
        self.category = category
        
    def write( self, message ):
        
        print( '[%s] %s' % ( self.category, message ) )
        