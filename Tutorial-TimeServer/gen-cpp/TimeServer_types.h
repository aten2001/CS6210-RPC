/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef TimeServer_TYPES_H
#define TimeServer_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace TimeServer {

typedef struct _TimeInfo__isset {
  _TimeInfo__isset() : timestamp(false) {}
  bool timestamp;
} _TimeInfo__isset;

class TimeInfo {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  TimeInfo() : timestamp() {
  }

  virtual ~TimeInfo() throw() {}

  std::string timestamp;

  _TimeInfo__isset __isset;

  void __set_timestamp(const std::string& val) {
    timestamp = val;
  }

  bool operator == (const TimeInfo & rhs) const
  {
    if (!(timestamp == rhs.timestamp))
      return false;
    return true;
  }
  bool operator != (const TimeInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TimeInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TimeInfo &a, TimeInfo &b);

} // namespace

#endif
