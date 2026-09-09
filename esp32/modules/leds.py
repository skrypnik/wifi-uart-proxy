from neopixel import NeoPixel

from machine import Pin

class pixel:
    
    @staticmethod
    def lightPixel( pin_number, rgb_color ):
        
        pin = Pin( pin_number, Pin.OUT )
        
        led = NeoPixel( pin, 1 )
        led[0] = rgb_color
        led.write()