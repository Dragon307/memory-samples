find_package(Protobuf REQUIRED)
find_program(PYTHON "python2")

protobuf_generate_python(PROTO_PY "../memory_samples.proto")
add_custom_target(force_protobuf_python ALL DEPENDS ${PROTO_PY})

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/memory_samples" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/python_module")

add_custom_target(copy_protopy ALL DEPENDS force_protobuf_python)
add_custom_command(TARGET copy_protopy COMMAND ${CMAKE_COMMAND} -E copy ${PROTO_PY} "${CMAKE_CURRENT_BINARY_DIR}/python_module/memory_samples/")

set(SETUP_PY_IN "${CMAKE_CURRENT_SOURCE_DIR}/setup.py.in")
set(SETUP_PY    "${CMAKE_CURRENT_BINARY_DIR}/python_module/setup.py")

configure_file(${SETUP_PY_IN} ${SETUP_PY})

install(CODE "execute_process(COMMAND ${PYTHON} ${SETUP_PY} install WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/python_module/)")
