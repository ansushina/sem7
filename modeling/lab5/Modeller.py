  
from Distributions import UniformDistribution
from EventGenerator import Generator
from Processor import Processor


class Modeller:
    def __init__(self, generator, operators, computers):
        self._generator = generator
        self._operators = operators
        self._computers = computers

    def event_mode(self):
        refusals = 0
        processed = 0
        generated_requests = self._generator.num_requests
        generator = self._generator

        generator.receivers = self._operators.copy()
        self._operators[0].receivers = [self._computers[0]]
        self._operators[1].receivers = [self._computers[0]]
        self._operators[2].receivers = [self._computers[1]]

        generator.next = generator.next_time()
        self._operators[0].next = self._operators[0].next_time()

        blocks = [
            generator,
            self._operators[0],
            self._operators[1],
            self._operators[2],
            self._computers[0],
            self._computers[1],
        ]

        while generator.num_requests >= 0:
            # находим наименьшее время
            current_time = generator.next
            for block in blocks:
                if 0 < block.next < current_time:
                    current_time = block.next

            # для каждого из блоков
            for block in blocks:
                # если событие наступило для этого блока
                if current_time == block.next:
                    if not isinstance(block, Processor):
                        # для генератора 
                        # проверяем, может ли оператор обработать
                        next_generator = generator.generate_request()
                        if next_generator is not None:
                            next_generator.next = \
                                current_time + next_generator.next_time()
                            processed += 1
                        else:
                            refusals += 1
                        generator.next = current_time + generator.next_time()
                    else:
                        block.process_request()
                        if block.current_queue_size == 0:
                            block.next = 0
                        else:
                            block.next = current_time + block.next_time()

        return {"refusal_percentage": refusals / generated_requests * 100,
                "refusals": refusals,
                "processed": processed,
                }