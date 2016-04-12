#!/usr/bin/python2

import argparse
import sys
import glob
import os

import pyusf
import memory_samples_pb2 as mspb
import sample_file_util

def convert_memaccess(usf_memaccess, is_instruction=False):
    pb_memaccess = mspb.MemoryAccess()
    pb_memaccess.memory_address = usf_memaccess.addr
    pb_memaccess.program_counter = usf_memaccess.pc
    pb_memaccess.thread_id = usf_memaccess.tid
    pb_memaccess.access_counter = usf_memaccess.time

    if (is_instruction):
        pb_memaccess.access_type = mspb.INSTRUCTION

    elif (usf_memaccess.type == 0):
        pb_memaccess.access_type = mspb.READ

    elif (usf_memaccess.type == 1):
        pb_memaccess.access_type = mspb.WRITE

    else:
        raise ValueError("Unknown access type {}".format(e.type))

    return pb_memaccess


def convert(usf_root_dir, basename="sample_d", new_basename = "memory.samples"):
    samples = glob.glob(usf_root_dir + '/' + basename + ".[0-9]*")

    samples = sorted(samples, key=lambda x: int(os.path.basename(x).split('.')[1]))

    sample_writer = sample_file_util.SampleWriter(new_basename)

    for i, s in enumerate(samples):
        usf_file = pyusf.Usf()
        usf_file.open(s)

        usf_file.next() #skip first Burst event

        for event in usf_file:
            assert(isinstance(event, pyusf.Sample) or isinstance(event, pyusf.Dangling))

            pb_sample = mspb.Sample()
            pb_sample.window_id = i

            pb_sample.begin.CopyFrom(convert_memaccess(event.begin))

            if isinstance(event, pyusf.Sample):
                pb_sample.end.CopyFrom(convert_memaccess(event.end))

            sample_writer.write_sample(pb_sample)

convert(sys.argv[1])
