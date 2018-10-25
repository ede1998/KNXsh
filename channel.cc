#include "channel.hh"
#include <exception>
#include <sstream>
#include <string>
#include <ios>

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

boost::asio::ip::udp::endpoint& Channel::getEndpoint()
{
    return mEndpoint;
}

boost::asio::ip::udp::socket& Channel::getSocket()
{
    return mSocket;
}
