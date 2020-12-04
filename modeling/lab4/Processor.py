from EventGenerator import Generator
from numpy import random as nr

class Processor(Generator):
    def __init__(self, generator, reenter_probability=0):
        super().__init__(generator)
        self.current_queue_size = 0
        self.max_queue_size = 0
        self.processed_requests = 0
        self.reenter_probability = reenter_probability
        self.reentered_requests = 0

# обрабатываем запрос, если они есть
    def process(self):
        if self.current_queue_size > 0:
            self.processed_requests += 1
            self.current_queue_size -= 1
            self.emit_request()
            # Возвращаем реквест, если срабатывает возвращаемость
            if nr.random_sample() <= self.reenter_probability:
                self.reentered_requests += 1
                #Sself.processed_requests -= 1
                self.receive_request()
    
# добавляем реквест в очередь
    def receive_request(self):
        self.current_queue_size += 1
        if self.current_queue_size > self.max_queue_size:
            self.max_queue_size = self.current_queue_size