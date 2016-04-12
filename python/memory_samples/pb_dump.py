#!/usr/bin/python

import sys
import sample_file_util

def stringify_memaccess(memaccess):
    return "[tid: {}, pc: {:#x}, addr: {:#x}, time: {}, type: {}]".format(memaccess.thread_id, memaccess.program_counter, memaccess.memory_address, memaccess.access_counter, memaccess.access_type)

def stringify_sample(sample):
    is_dangling = not sample.HasField("end")

    ret = "[SAMPLE] " if not is_dangling else "[DANGLING] "
    ret += "begin: " + stringify_memaccess(sample.begin)

    if not is_dangling:
        ret += ", end: " + stringify_memaccess(sample.end)

    return ret

sample_reader = sample_file_util.SampleReader(sys.argv[1])

for sample in sample_reader.iter_in_place():
    print(stringify_sample(sample))
