#include <vector>
#include <random>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <fstream>

#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "memory_samples.pb.h"
#include "sample_file_util.h"
#include "protobuf_util.h"

using namespace std;

vector<sample_file::Sample> generate_random_samples(unsigned nb_samples)
{
    //default_random_engine eng(0);
    //uniform_int_distribution<uint32_t> distr(0);

    vector<sample_file::Sample> samples;

    samples.reserve(nb_samples);
    for (unsigned i = 0; i < nb_samples; ++i)
    {
        sample_file::MemoryAccess begin, end;

        begin.set_memory_address(10);
        begin.set_access_counter(10);
        begin.set_access_type(sample_file::AccessType::READ);
        begin.set_thread_id(42);
        begin.set_program_counter(10);

        end.set_memory_address(begin.memory_address());
        end.set_access_counter(begin.access_counter() + 10);
        end.set_access_type(sample_file::AccessType::WRITE);
        end.set_thread_id(42);
        end.set_program_counter(10);

        samples.emplace_back(make_sample(26, begin, end));
    }

    return samples;
}

int main(void)
{
    auto samples = generate_random_samples(10000000);

    OutputSampleFile sample_file("benchmark_ofstream.output");

    auto start = chrono::system_clock::now();

    for (const auto& sample : samples)
    {
        sample_file.write_sample(sample);
    }

    auto end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end - start;
    cout << "elapsed time: " << elapsed_seconds.count() << 's' <<endl;
}
