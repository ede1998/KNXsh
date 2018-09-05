#include "channel.hh"
#include <exception>
#include <sstream>
#include <string>
#include <ios>
#include "data_blocks.hh"

namespace ip = boost::asio::ip;
using ip::udp;

Channel::Channel()
: mSocket(mIOService)
{
  mSocket.open(udp::v4());
}


void Channel::setIP(const std::string& ip)
{
  mEndpoint.address(ip::make_address(ip));
}

void Channel::setPort(unsigned short port)
{
  mEndpoint.port(port);
}
