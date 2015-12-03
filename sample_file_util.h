#ifndef SAMPLE_FILE_UTIL_H
#define SAMPLE_FILE_UTIL_H

#include "memory_samples.pb.h"

//sample_file::MemoryAccess make_memaccess(void);

sample_file::Sample make_sample(unsigned window_id, const sample_file::MemoryAccess& begin, const sample_file::MemoryAccess& end);
sample_file::Sample make_dangling_sample(unsigned window_id, const sample_file::MemoryAccess& begin);

void print_memoryaccess(const sample_file::MemoryAccess& access);
void print_sample(const sample_file::Sample& sample);


#endif
