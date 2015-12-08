#ifndef SAMPLE_FILE_UTIL_H
#define SAMPLE_FILE_UTIL_H

#include <fstream>

#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "memory_samples.pb.h"
#include "protobuf_util.h"

sample_file::Sample make_sample(unsigned window_id, const sample_file::MemoryAccess& begin, const sample_file::MemoryAccess& end);
sample_file::Sample make_dangling_sample(unsigned window_id, const sample_file::MemoryAccess& begin);

void print_memoryaccess(const sample_file::MemoryAccess& access);
void print_sample(const sample_file::Sample& sample);

class OutputSampleFile
{
    bool finalized;
    std::ofstream ofs;
    google::protobuf::io::OstreamOutputStream* oos;

public:
    OutputSampleFile(const std::string& filename);
    void write_sample(const sample_file::Sample& sample);
    void finalize(void);
    ~OutputSampleFile();
};

#endif
