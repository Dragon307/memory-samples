#include <iostream>
#include <iomanip>

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