/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "HTTPProxy_types.h"

#include <algorithm>

namespace HTTP_Proxy {

const char* HTTPProxy::ascii_fingerprint = "EEBC915CE44901401D881E6091423036";
const uint8_t HTTPProxy::binary_fingerprint[16] = {0xEE,0xBC,0x91,0x5C,0xE4,0x49,0x01,0x40,0x1D,0x88,0x1E,0x60,0x91,0x42,0x30,0x36};

uint32_t HTTPProxy::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readBinary(this->document);
          this->__isset.document = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->result_code);
          this->__isset.result_code = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t HTTPProxy::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("HTTPProxy");

  xfer += oprot->writeFieldBegin("document", ::apache::thrift::protocol::T_STRING, 1);
  xfer += oprot->writeBinary(this->document);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("result_code", ::apache::thrift::protocol::T_I32, 2);
  xfer += oprot->writeI32(this->result_code);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(HTTPProxy &a, HTTPProxy &b) {
  using ::std::swap;
  swap(a.document, b.document);
  swap(a.result_code, b.result_code);
  swap(a.__isset, b.__isset);
}

} // namespace
