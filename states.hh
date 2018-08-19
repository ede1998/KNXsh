#pragma once

#include <memory>
#include <string>
#include "channel.hh"


namespace KNX
{

class Connection;

namespace ConnectionState
{

class State
{
  public:
    virtual void open(KNX::Connection* con, const std::string& ip) {}
    virtual void close(KNX::Connection* con) {}
    virtual void send(KNX::Connection* con) {}

  protected:
     static void changeState(KNX::Connection* con, const std::shared_ptr<State>& newState);
     static Channel& getControlChannel(KNX::Connection* con);
     static Channel& getDataChannel(KNX::Connection* con);
};

class Closed: public State
{
  public:
    static std::shared_ptr<State> getInstance();
    virtual void open(KNX::Connection* con, const std::string& ip);
};

class Opened: public State
{
  public:
    static std::shared_ptr<State> getInstance();
    virtual void close(KNX::Connection* con);
    virtual void send(KNX::Connection* con);
};

} // namespace ConnectionState
} // namespace KNX
