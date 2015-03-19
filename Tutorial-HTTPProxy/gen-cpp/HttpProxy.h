/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef HttpProxy_H
#define HttpProxy_H

#include <thrift/TDispatchProcessor.h>
#include "HTTPProxy_types.h"

namespace HTTP_Proxy {

class HttpProxyIf {
 public:
  virtual ~HttpProxyIf() {}
  virtual void get(HTTPProxy& _return, const std::string& URL) = 0;
};

class HttpProxyIfFactory {
 public:
  typedef HttpProxyIf Handler;

  virtual ~HttpProxyIfFactory() {}

  virtual HttpProxyIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(HttpProxyIf* /* handler */) = 0;
};

class HttpProxyIfSingletonFactory : virtual public HttpProxyIfFactory {
 public:
  HttpProxyIfSingletonFactory(const boost::shared_ptr<HttpProxyIf>& iface) : iface_(iface) {}
  virtual ~HttpProxyIfSingletonFactory() {}

  virtual HttpProxyIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(HttpProxyIf* /* handler */) {}

 protected:
  boost::shared_ptr<HttpProxyIf> iface_;
};

class HttpProxyNull : virtual public HttpProxyIf {
 public:
  virtual ~HttpProxyNull() {}
  void get(HTTPProxy& /* _return */, const std::string& /* URL */) {
    return;
  }
};

typedef struct _HttpProxy_get_args__isset {
  _HttpProxy_get_args__isset() : URL(false) {}
  bool URL;
} _HttpProxy_get_args__isset;

class HttpProxy_get_args {
 public:

  HttpProxy_get_args() : URL() {
  }

  virtual ~HttpProxy_get_args() throw() {}

  std::string URL;

  _HttpProxy_get_args__isset __isset;

  void __set_URL(const std::string& val) {
    URL = val;
  }

  bool operator == (const HttpProxy_get_args & rhs) const
  {
    if (!(URL == rhs.URL))
      return false;
    return true;
  }
  bool operator != (const HttpProxy_get_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const HttpProxy_get_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class HttpProxy_get_pargs {
 public:


  virtual ~HttpProxy_get_pargs() throw() {}

  const std::string* URL;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _HttpProxy_get_result__isset {
  _HttpProxy_get_result__isset() : success(false) {}
  bool success;
} _HttpProxy_get_result__isset;

class HttpProxy_get_result {
 public:

  HttpProxy_get_result() {
  }

  virtual ~HttpProxy_get_result() throw() {}

  HTTPProxy success;

  _HttpProxy_get_result__isset __isset;

  void __set_success(const HTTPProxy& val) {
    success = val;
  }

  bool operator == (const HttpProxy_get_result & rhs) const
  {
    if (!(success == rhs.success))
      return false;
    return true;
  }
  bool operator != (const HttpProxy_get_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const HttpProxy_get_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

typedef struct _HttpProxy_get_presult__isset {
  _HttpProxy_get_presult__isset() : success(false) {}
  bool success;
} _HttpProxy_get_presult__isset;

class HttpProxy_get_presult {
 public:


  virtual ~HttpProxy_get_presult() throw() {}

  HTTPProxy* success;

  _HttpProxy_get_presult__isset __isset;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class HttpProxyClient : virtual public HttpProxyIf {
 public:
  HttpProxyClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) :
    piprot_(prot),
    poprot_(prot) {
    iprot_ = prot.get();
    oprot_ = prot.get();
  }
  HttpProxyClient(boost::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, boost::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) :
    piprot_(iprot),
    poprot_(oprot) {
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void get(HTTPProxy& _return, const std::string& URL);
  void send_get(const std::string& URL);
  void recv_get(HTTPProxy& _return);
 protected:
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  boost::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class HttpProxyProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  boost::shared_ptr<HttpProxyIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (HttpProxyProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_get(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  HttpProxyProcessor(boost::shared_ptr<HttpProxyIf> iface) :
    iface_(iface) {
    processMap_["get"] = &HttpProxyProcessor::process_get;
  }

  virtual ~HttpProxyProcessor() {}
};

class HttpProxyProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  HttpProxyProcessorFactory(const ::boost::shared_ptr< HttpProxyIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::boost::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::boost::shared_ptr< HttpProxyIfFactory > handlerFactory_;
};

class HttpProxyMultiface : virtual public HttpProxyIf {
 public:
  HttpProxyMultiface(std::vector<boost::shared_ptr<HttpProxyIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~HttpProxyMultiface() {}
 protected:
  std::vector<boost::shared_ptr<HttpProxyIf> > ifaces_;
  HttpProxyMultiface() {}
  void add(boost::shared_ptr<HttpProxyIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void get(HTTPProxy& _return, const std::string& URL) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->get(_return, URL);
    }
    ifaces_[i]->get(_return, URL);
    return;
  }

};

} // namespace

#endif
