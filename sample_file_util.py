import protobuf_util
import memory_samples_pb2
import itertools

class SampleReader(object):
    def __init__(self, filename):
        self.file = open(filename, 'rb')

    def iter_in_place(self):
        sample = memory_samples_pb2.Sample()
        while 1:
            msg = protobuf_util.readDelimitedFrom_inplace(sample, self.file)
            if msg is None:
                break

            yield msg

    def __iter__(self):
        while 1:
            msg = protobuf_util.readDelimitedFrom(memory_samples_pb2.Sample, self.file)
            if msg is None:
                break

            yield msg
