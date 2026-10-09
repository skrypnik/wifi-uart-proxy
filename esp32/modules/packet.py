from modules import config, logger

LOGGER_CATEGORY = 'PACK'
log = logger.logger( LOGGER_CATEGORY )

class reply:
    
    SUCCESS = [0x00, 0x02]
    FAILURE = [0xff, 0x02]

class packer:
        
    def __init__( self, configuration ):
        
        self.MAX_PACKET_SIZE = configuration['common']['max_packet_size']
        self.UDP_HEADER_SIZE = configuration['common']['udp_header_size']
        
        self.MAX_DATA_SIZE = self.MAX_PACKET_SIZE + self.UDP_HEADER_SIZE
        
        self.buffer = bytearray()
        
        self.length = 0x00
        self.offset = 0x00
        
        self.queue = []
        
    def ready( self ):
        
        return len( self.queue )
        
    def put( self, data ):
        
        self.buffer = self.buffer + data
        
        if not self.offset:
            
            HDR_SIZE = 0x04
            CRC_SIZE = 0x02
            
            size = int.from_bytes(self.buffer[0x02:0x04], 'little') + HDR_SIZE + CRC_SIZE
            
            if size <= self.MAX_PACKET_SIZE:
                
                data = bytearray( 0x09 ) + self.buffer[0:size]
                
                log.write_hex( self.buffer[0x00:0x02] )
                log.write( 'SIZE: %d' % (size) )
                log.write( 'OFFS: %d' % (self.offset) )
                log.write( 'BLEN: %d' % ( len(self.buffer) ) )
                log.write( '--------------------------------')
                
                self.queue.append( data )
                self.buffer = self.buffer[size:]
                
            else:
            
                self.length = size
                self.offset = 0x00
                
        while len( self.buffer ) >= self.MAX_PACKET_SIZE and self.length:
            
            size = self.MAX_PACKET_SIZE if self.length >= self.MAX_PACKET_SIZE else self.length
            header = bytearray( 0x01 ) + size.to_bytes( 0x04 ) + self.offset.to_bytes( 0x04 )
            data = header + self.buffer[0x00:size]
            
            if not self.offset: log.write_hex( self.buffer[0x00:0x02] )
            log.write( 'SIZE: %d' % (size) )
            log.write( 'OFFS: %d' % (self.offset) )
            log.write( 'BLEN: %d' % ( len(self.buffer) ) )
            log.write( '--------------------------------')
            
            self.queue.append( data )
            self.buffer = self.buffer[size:]
            self.length -= size
            self.offset += 1
            
            if not self.length:
                
                self.offset = 0x00
                break
    
    def get( self ):
        
        if self.ready():
        
            data = self.queue.pop( 0x00 )
        
            return data
        
        return None
        