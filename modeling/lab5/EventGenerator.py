
class Generator:
    def __init__(self, generator, count):
        self._generator = generator
        self.receivers = []
        self.num_requests = count
        self.next = 0 

    def next_time(self):
        return self._generator.generate()
    
    def generate_request(self):
        self.num_requests -= 1
        for receiver in self.receivers:
            if receiver.receive_request():
                return receiver
        return None