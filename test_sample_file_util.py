#!/usr/bin/python

import time

import memory_samples_pb2
import protobuf_util
import sample_file_util

sample = memory_samples_pb2.Sample()

sample.begin.access_counter = 0xdeadbeef
sample.begin.memory_address = 0xabcdef

sample.end.access_counter = 0xdeadbeef
sample.end.memory_address = 0xabcdef


filename = 'new_test'

iter = 3000000
with open('new_test', 'wb') as f:
    start = time.clock()

    for i in xrange(iter):
        protobuf_util.writeDelimitedTo(sample, f)

    end = time.clock()

print("wrote {} samples in {}s".format(iter, end - start))

reader = sample_file_util.SampleReader(filename)

start = time.clock()

for i, s in enumerate(reader.iter_in_place()):
    pass

end = time.clock()

print("Read {} samples in {}s".format(i + 1, end - start))
