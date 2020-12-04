  
from Distributions import UniformDistribution, ErlangDistribution 
from EventGenerator import Generator
from Processor import Processor


class Modeller:
    def __init__(self, uniform_a, uniform_b, er_k, er_l, reenter_prop):
        self._generator = Generator(UniformDistribution(uniform_a, uniform_b))
        self._processor = Processor(ErlangDistribution(er_k, er_l), reenter_prop)
        self._generator.add_receiver(self._processor)

    def event_based_modelling(self, request_count):
        generator = self._generator
        processor = self._processor

        gen_period = generator.next_time()
        proc_period = gen_period +processor.next_time()

        while processor.processed_requests < request_count:
            # print( processor.next_time(), generator.next_time())
            if gen_period <= proc_period:
                # появился новый запрос
                # добавляем оправляем его в процессор
                generator.emit_request()
                gen_period += generator.next_time()
            if gen_period >= proc_period:
                # закончилась обработка
                # обрабатываем запрос
                processor.process()

                # проверка для самого первого запроса
                if processor.current_queue_size > 0:
                    proc_period += processor.next_time()
                else:
                    proc_period = gen_period + processor.next_time()

        return (processor.processed_requests, processor.reentered_requests,
                processor.max_queue_size, round(proc_period, 3))

    def time_based_modelling(self, request_count, dt):
        generator = self._generator
        processor = self._processor

        gen_period = generator.next_time()
        proc_period = gen_period
        current_time = 0
        while processor.processed_requests < request_count:
            if gen_period <= current_time:
                # появился новый запрос
                # добавляем оправляем его в процессор
                generator.emit_request()
                gen_period += generator.next_time()
            if current_time >= proc_period:
                # закончилась обработка
                # обрабатываем запрос
                processor.process()
                if processor.current_queue_size > 0:
                    proc_period += processor.next_time()
                else:
                    proc_period = gen_period + processor.next_time()

            # прибавляем дельту
            current_time += dt

        return (processor.processed_requests, processor.reentered_requests,
                processor.max_queue_size, round(current_time, 3))