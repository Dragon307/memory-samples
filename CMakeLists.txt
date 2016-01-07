set (CMAKE_CXX_STANDARD 11)
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS "memory_samples.proto")
protobuf_generate_python(PROTO_PY "memory_samples.proto")
add_custom_target(force_protobuf_python ALL DEPENDS ${PROTO_PY})

include_directories(${CMAKE_BINARY_DIR})
add_executable(test_memory_samples_protobuf test_memory_samples_protobuf.cpp sample_file_util.cpp protobuf_util.cpp ${PROTO_SRCS})
add_executable(benchmark benchmark.cpp sample_file_util.cpp protobuf_util.cpp ${PROTO_SRCS})

target_link_libraries(test_memory_samples_protobuf ${PROTOBUF_LIBRARY})
target_link_libraries(benchmark ${PROTOBUF_LIBRARY})
