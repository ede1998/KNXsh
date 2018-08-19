#pragma once

#include <string>
#include <memory>
#include "data_blocks.hh"
#include <boost/asio.hpp>
  
template <class T>
static boost::asio::const_buffer convertToBuffer(const T& data)
{
  return boost::asio::buffer(reinterpret_cast<const void*>(&data), sizeof(T));
}

class Channel
{
  public:
    Channel();
    boost::asio::ip::udp::endpoint& getEndpoint();
    boost::asio::ip::udp::socket& getSocket();
    void setIP(const std::string& ip);
    void setPort(unsigned short port);
    template <class T>
    void send(const T& buf);
    KNX::datagrams::package* receive();
    void run();
  private:
    boost::asio::ip::udp::endpoint mEndpoint;
    boost::asio::io_service mIOService;
    boost::asio::ip::udp::socket mSocket;
};

template <class T>
void Channel::send(const T& buf)
{
  mSocket.send_to(convertToBuffer(buf), mEndpoint);
}

