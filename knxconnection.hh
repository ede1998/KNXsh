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
      bool open(const std::string& ip);
      void close();
      void send();
      bool isOpen();
      static const unsigned int PORT = 13; // 3671
    private:
      friend class ConnectionState::State;
      std::shared_ptr<ConnectionState::State> mState;
      Channel mControl;
      Channel mData;
  };
} // namespace KNX
