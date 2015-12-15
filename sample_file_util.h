#ifndef SAMPLE_FILE_UTIL_H
#define SAMPLE_FILE_UTIL_H

#include <fstream>
#include <string>

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
    std::string filename;
    std::ofstream ofs;
    google::protobuf::io::OstreamOutputStream* oos;

public:
    OutputSampleFile(const std::string& filename);
    OutputSampleFile(const OutputSampleFile&) = delete;
    OutputSampleFile& operator=(const OutputSampleFile&) = delete;

    void write_sample(const sample_file::Sample& sample);
    void finalize(void);
    ~OutputSampleFile();
};

class InputSampleFile
{
    bool finalized;
    std::string filename;
    std::ifstream ifs;
    google::protobuf::io::IstreamInputStream* iis;

public:
    InputSampleFile(const std::string& filename);
    InputSampleFile(const InputSampleFile&) = delete;
    InputSampleFile& operator=(const InputSampleFile&) = delete;

    bool read_sample(sample_file::Sample&);
    ~InputSampleFile();
};
#endif
