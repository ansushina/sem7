from EventGenerator import Generator
from numpy import random as nr

class Processor(Generator):
    def __init__(self, generator, max_queue=-1):
        self._generator = generator
        self.current_queue_size = 0
        self.max_queue_size = max_queue
        self.processed_requests = 0
        self.received_requests  = 0
        self.next = 0

# обрабатываем запрос, если они есть
    def process_request(self):
        if self.current_queue_size > 0:
            self.processed_requests += 1
            self.current_queue_size -= 1
            #self.emit_request()
    
# добавляем реквест в очередь
    def receive_request(self):
        # print(self.max_queue_size, self.current_queue_size ) 
        if self.max_queue_size == -1 or self.max_queue_size > self.current_queue_size:
            self.current_queue_size += 1
            self.received_requests += 1
            return True
        return False

    def next_time(self):
        return self._generator.generate()