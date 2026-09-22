from machine import Pin, Timer

class button:
    
    def __init__( self, pin_number ):
        
        self.pin = Pin( pin_number, Pin.IN, Pin.PULL_UP )
        
        self.last = self.pin.value()
        
    def clicked( self ):
        
        idle = (self.pin.value() == 1) or (self.pin.value() == self.last)
        
        self.last = self.pin.value()
         
        return not idle
    