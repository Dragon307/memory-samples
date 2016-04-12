set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE "Release")
find_package(Protobuf REQUIRED)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS "memory_samples.proto")
protobuf_generate_python(PROTO_PY "memory_samples.proto")
# add_custom_target(force_protobuf_python ALL DEPENDS ${PROTO_PY})
#
# include_directories(${CMAKE_BINARY_DIR})
# add_executable(test_memory_samples_protobuf test_memory_samples_protobuf.cpp sample_file_util.cpp protobuf_util.cpp ${PROTO_SRCS})
# add_executable(benchmark benchmark.cpp sample_file_util.cpp protobuf_util.cpp ${PROTO_SRCS})
#
# target_link_libraries(test_memory_samples_protobuf ${PROTOBUF_LIBRARY})
# target_link_libraries(benchmark ${PROTOBUF_LIBRARY})
#
# add_custom_target(wait_for_protoc DEPENDS ${PROTO_SRCS})
# add_library(sample_file_util SHARED sample_file_util.cpp protobuf_util.cpp)
# add_dependencies(sample_file_util wait_for_protoc)
# install(TARGETS sample_file_util DESTINATION lib)
# install(TARGETS benchmark DESTINATION examples)
# install(FILES ${PROTO_PY} sample_file_util.py DESTINATION python)

include_directories(${CMAKE_BINARY_DIR})

add_library(memory_samples SHARED sample_file_util.cpp protobuf_util.cpp ${PROTO_SRCS})
target_link_libraries(memory_samples ${PROTOBUF_LIBRARY})

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark memory_samples)

set_target_properties(benchmark PROPERTIES INSTALL_RPATH_USE_LINK_PATH TRUE)
install(TARGETS benchmark memory_samples
        RUNTIME DESTINATION bin/memory_samples/examples
        LIBRARY DESTINATION lib)

install(FILES ${PROTO_HDRS} sample_file_util.h protobuf_util.h DESTINATION include/memory_samples)
