#pragma once

#include <memory>
#include <string>
#include "channel.hh"

namespace KNX
{
  namespace ConnectionState
  {
    class State;
  } // namespace ConnectionState

  class Connection
  {
    public:
      Connection();
      bool open(const std::string& dest_ip, const std::string& src_ip);
      void close();
      void send();
      bool isOpen();
      static const unsigned int PORT = 3671;
    private:
      friend class ConnectionState::State;
      std::shared_ptr<ConnectionState::State> mState;
      Channel mControl;
      Channel mData;
  };
} // namespace KNX
