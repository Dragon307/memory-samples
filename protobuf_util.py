#!/usr/bin/python

from google.protobuf.internal import encoder
from google.protobuf.internal import decoder

def readRawVarint32(stream):
    raw_varint32 = []
    while 1:
        b = stream.read(1)
        #eof
        if b == "":
            break
        raw_varint32.append(b)

        if not (ord(b) & 0x80):
            #we found a byte starting with a 0, which means it's the last byte of this varint
            break

    return raw_varint32

def writeDelimitedTo(message, stream):
    message_str = message.SerializeToString()
    delimiter = encoder._VarintBytes(len(message_str))

    stream.write(delimiter + message_str)

def readDelimitedFrom(MessageType, stream):
    raw_varint32 = readRawVarint32(stream)
    message = None

    if raw_varint32:
        size, _ = decoder._DecodeVarint32(raw_varint32, 0)

        data = stream.read(size)
        if len(data) < size:
            raise Exception("Unexpected end of file")

        message = MessageType()
        message.ParseFromString(data)

    return message

def readDelimitedFrom_inplace(message, stream):
    raw_varint32 = readRawVarint32(stream)

    if raw_varint32:
        size, _ = decoder._DecodeVarint32(raw_varint32, 0)

        data = stream.read(size)
        if len(data) < size:
            raise Exception("Unexpected end of file")

        message.ParseFromString(data)

        return message
    else:
        return None
