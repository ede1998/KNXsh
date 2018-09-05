#include "knxconnection.hh"

#include <cassert>
#include <iostream>
#include "states.hh"

namespace KNX
{

Connection::Connection()
: mState(ConnectionState::Closed::getInstance())
{
}

bool Connection::open(const std::string& ip)
{
  mState->open(this, ip);
  return isOpen();
}

void Connection::close()
{
  mState->close(this);
}

void Connection::send()
{
  mState->send(this);
}

bool Connection::isOpen()
{
  return mState == ConnectionState::Opened::getInstance();
}


} // namespace KNX
