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

bool Connection::open(const std::string& dest_ip, const std::string& src_ip)
{
  mState->open(this, dest_ip, src_ip);
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
