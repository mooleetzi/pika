// Copyright (c) 2019-present, Qihoo, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.

#ifndef PIKA_REPL_SERVER_THREAD_H_
#define PIKA_REPL_SERVER_THREAD_H_

#include "net/src/holy_thread.h"

#include "include/pika_repl_server_conn.h"

class PikaReplServerThread : public net::HolyThread {
 public:
  PikaReplServerThread(const std::set<std::string>& ips, int port, int cron_interval);
  virtual ~PikaReplServerThread() = default;

  int ListenPort();

  // for ProcessBinlogData use
  uint64_t GetnPlusSerial() {
    return serial_++;
  }

 private:
  class ReplServerConnFactory : public net::ConnFactory {
   public:
    explicit ReplServerConnFactory(PikaReplServerThread* binlog_receiver)
        : binlog_receiver_(binlog_receiver) {
    }

    virtual std::shared_ptr<net::NetConn> NewNetConn(
        int connfd,
        const std::string& ip_port,
        net::Thread* thread,
        void* worker_specific_data,
        net::NetEpoll* net_epoll) const override {
      return std::static_pointer_cast<net::NetConn>
        (std::make_shared<PikaReplServerConn>(connfd, ip_port, thread, binlog_receiver_, net_epoll));
    }
    private:
     PikaReplServerThread* binlog_receiver_;
  };

  class ReplServerHandle : public net::ServerHandle {
   public:
    virtual void FdClosedHandle(int fd, const std::string& ip_port) const override;
  };

  ReplServerConnFactory conn_factory_;
  ReplServerHandle handle_;
  int port_;
  uint64_t serial_;
};

#endif
