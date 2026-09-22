import uasyncio, asyncio

class async_queue:
    
    def __init__( self ):
        
        self.queue = []
        
        self.not_empty = asyncio.Event()

    async def put( self, item ):
            
        self.queue.append( item )

    async def get( self ):
        
        while not self.queue:
            
            await self.not_empty.wait()
            
            self.not_empty.clear()
        
        item = self.queue.pop( 0 )
        
        return item

    def empty( self ):
        
        return not len( self.queue )