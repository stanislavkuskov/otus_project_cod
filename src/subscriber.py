import zmq
from threading import Thread


class Subscriber(Thread):
    def __init__(
            self, ip_addres, port="5563", topic=b'cod', message_waiting_time=5000):
        Thread.__init__(self)
        self.is_stopped = False

        context = zmq.Context()
        self.ip_addres = ip_addres
        self.port = port
        self.topic = topic
        self.socket = context.socket(zmq.SUB)
        self.socket.connect("tcp://{}:{}".format(self.ip_addres, self.port))
        self.socket.setsockopt(zmq.SUBSCRIBE, topic)

        self.poller = zmq.Poller()
        self.poller.register(self.socket, zmq.POLLIN)
        self.message_waiting_time = message_waiting_time    # ms

        self.detect_dict = None
        self._error = False

    def run(self):
        while not self.is_stopped:

            socks = dict(self.poller.poll(self.message_waiting_time))

            if not socks:
                self.detect_dict = None
                self._error = True
            else:
                if socks.get(self.socket) == zmq.POLLIN:
                    self.topic = self.socket.recv_string()
                    self.detect_dict = self.socket.recv_json()
                    print(self.detect_dict)
                    self._error = False

    def stop(self):
        self.is_stopped = True

    @property
    def return_detect_dict(self):
        return [self._error, self.detect_dict]


if __name__ == '__main__':

    subscriber = Subscriber(ip_addres="127.0.0.1")
    subscriber.start()

    while not subscriber.is_stopped:
        err, detect_dict = subscriber.return_detect_dict
        if err:
            # Если произошла ошибка останавливаем работу программы и
            # записываем сообщение об ошибке в лог файл
            subscriber.stop()

        if detect_dict:
            # Чтобы отображать список детектируемых объектов раскомментируйте следующую строку
            # print("w:{}, h:{}".format(detect_dict["objects"]["w"], detect_dict["objects"]["h"]))
            print(detect_dict)
