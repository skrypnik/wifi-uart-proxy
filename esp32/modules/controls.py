from machine import Pin, Timer

class button:
    
    @staticmethod
    def clicked( pin_number ):
        
        pin = Pin( pin_number, Pin.IN, Pin.PULL_UP )
        
        if pin.value() == 1: return False
        
        return True
    