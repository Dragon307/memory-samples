#include <iostream>
#include <fstream>
#include <cstdint>

#include <google/protobuf/io/zero_copy_stream_impl.h>

#include "memory_samples.pb.h"
#include "protobuf_util.h"
#include "sample_file_util.h"

using namespace std;

int main(void)
{
    void* addr1 = (void*) 0xaaaaaaaaaaaaaaaa;
    void* addr2 = (void*) 0xbbbbbbbbbbbbbbbb;
    void* addr3 = (void*) 0xcccccccccccccccc;
    void* addr4 = (void*) 0xdddddddddddddddd;
    void* addr5 = (void*) 0xeeeeeeeeeeeeeeee;
    void* addr6 = (void*) 0xffffffffffffffff;


    sample_file::MemoryAccess access_1;

    access_1.set_memory_address((uint64_t) addr1);
    access_1.set_access_counter(1337);
    access_1.set_access_type(sample_file::AccessType::READ);
    access_1.set_thread_id(42);
    access_1.set_program_counter(0xdeadbeef);


    sample_file::MemoryAccess access_2;
    access_2.set_memory_address((uint64_t) addr2);
    access_2.set_access_counter(2048);
    access_2.set_access_type(sample_file::AccessType::WRITE);
    access_2.set_thread_id(3);
    access_2.set_program_counter(0xdeadbeef);

    sample_file::Sample sample1 = make_sample(1, access_1, access_2);

    sample_file::MemoryAccess access_3;
    access_3.set_memory_address((uint64_t) addr3);
    access_3.set_access_counter(1337);
    access_3.set_access_type(sample_file::AccessType::READ);
    access_3.set_thread_id(42);
    access_3.set_program_counter(0xdeadbeef);

    sample_file::MemoryAccess access_4;
    access_4.set_memory_address((uint64_t) addr4);
    access_4.set_access_counter(2048);
    access_4.set_access_type(sample_file::AccessType::WRITE);
    access_4.set_thread_id(3);
    access_4.set_program_counter(0xdeadbeef);

    sample_file::Sample sample2 = make_sample(2, access_3, access_4);

    ofstream of("out2", ios::binary);

    google::protobuf::io::OstreamOutputStream* oos = new google::protobuf::io::OstreamOutputStream(&of);

    writeDelimitedTo_custom(sample1, oos);
    writeDelimitedTo_custom(sample2, oos);

    delete oos;
    of.close();

    ifstream ifs("out2", ios::binary);
    google::protobuf::io::IstreamInputStream* iis = new google::protobuf::io::IstreamInputStream(&ifs);

    bool clean_eof;

    while (1)
    {
        sample_file::Sample sample;
        const bool success = readDelimitedFrom_custom(iis, &sample, &clean_eof);

        if (!success)
            break;

        print_sample(sample);
    }

    if (clean_eof)
        cout << "End of file reached" << endl;
    else
        cout << "An error was encountered when reading the sample file" << endl;

    delete iis;
    ifs.close();
    return 0;
}
