#ifndef PROTOBUF_UTIL_H
#define PROTOBUF_UTIL_H

#include <google/protobuf/message_lite.h>
#include <google/protobuf/io/zero_copy_stream.h>

/* We want to write several Sample's into the same file.
 * In the protobuf Java API, this is achieved by using the methods writeDelimitedTo
 * and readDelimitedFrom, that allow to write the length in bytes of a message before
 * serializing it. Unfortunately, the C++ API does not provide such interface yet, so
 * we have to provide our own.
 * This is almost entirely copied from:
 * https://stackoverflow.com/questions/2340730/are-there-c-equivalents-for-the-protocol-buffers-delimited-i-o-functions-in-ja/22927149#22927149
 * and https://github.com/google/protobuf/pull/710
 */

bool writeDelimitedTo_custom(const google::protobuf::MessageLite& message, google::protobuf::io::ZeroCopyOutputStream* rawOutput);
bool readDelimitedFrom_custom(google::protobuf::io::ZeroCopyInputStream* rawInput, google::protobuf::MessageLite* message, bool* clean_eof);

#endif
