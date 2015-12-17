#include <iostream>
#include <iomanip>
#include <ios>

#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "protobuf_util.h"
#include "memory_samples.pb.h"
#include "sample_file_util.h"

using namespace std;
sample_file::Sample make_sample(unsigned window_id, const sample_file::MemoryAccess& begin, const sample_file::MemoryAccess& end)
{
    sample_file::Sample sample;
    sample.set_window_id(window_id);
    sample.mutable_begin()->CopyFrom(begin);
    sample.mutable_end()->CopyFrom(end);

    return sample;
}

sample_file::Sample make_dangling_sample(unsigned window_id, const sample_file::MemoryAccess& begin)
{
    sample_file::Sample sample;
    sample.set_window_id(window_id);
    sample.mutable_begin()->CopyFrom(begin);

    return sample;
}

void print_memoryaccess(const sample_file::MemoryAccess& access)
{
    cout << "access counter: " << access.access_counter() << endl;
    cout << std::hex << "memory address: " << access.memory_address() << endl;
    cout << "program counter: " << access.program_counter() << endl;
    std::setbase(10);
}

void print_sample(const sample_file::Sample& sample)
{
    const bool has_end = sample.has_end();
    if (has_end)
        cout << "==Sample==" << endl;
    else
        cout << "==Dangling Sample==" << endl;

    cout << "Begin:" << endl;
    print_memoryaccess(sample.begin());

    if (has_end)
    {
        cout << "End:" << endl;
        print_memoryaccess(sample.end());
    }
}

SampleWriter::SampleWriter(const string& filename) : filename(filename), finalized(false), ofs(filename, ios::binary)
{
    if (ofs.fail())
        throw ios_base::failure("Could not open the sample file " + filename);

    oos = new google::protobuf::io::OstreamOutputStream(&ofs);
}

void SampleWriter::write_sample(const sample_file::Sample& sample)
{
    bool ret =  writeDelimitedTo_custom(sample, oos);
    if (!ret)
        throw ios_base::failure("Output error on sample file " + filename);
}

void SampleWriter::finalize(void)
{
    if (!finalized)
    {
        delete oos;
        ofs.close();
        finalized = true;
    }
}

SampleWriter::~SampleWriter(void)
{
    if (!finalized)
        finalize();
}

SampleReader::SampleReader(const string& filename) : filename(filename), finalized(false), ifs(filename, ios::binary)
{
    if (ifs.fail())
        throw ios_base::failure("Could not open the sample file " + filename);

    iis = new google::protobuf::io::IstreamInputStream(&ifs);
}

bool SampleReader::read_sample(sample_file::Sample& sample)
{
    bool clean_eof;

    const bool ret = readDelimitedFrom_custom(iis, &sample, &clean_eof);

    if (!ret && !clean_eof)
        throw ios_base::failure("Input error on sample file " + filename);

    return ret;
}

SampleReader::~SampleReader(void)
{
    delete iis;
    ifs.close();
}
