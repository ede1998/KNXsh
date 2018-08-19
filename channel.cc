#include "channel.hh"
#include <exception>
#include <sstream>
#include <string>
#include <ios>

namespace ip = boost::asio::ip;
using ip::udp;
namespace dg = KNX::datagrams;

namespace {
  class UnknownServiceTypeID: public std::exception
  {
    public:
      
      UnknownServiceTypeID(unsigned short ID)
      : mSTID(ID)
      {
      }
  
      virtual const char* what() const noexcept
      {
        std::stringstream msg("Unknown Service Type-ID: 0x");
        msg << std::hex << mSTID;
        return msg.str().c_str();
      }
  
    private:
      unsigned short mSTID;
  };
  
  union datagramUnion {
    dg::knx_header header;
    dg::knx_tunneling_request tunneling_request;
    dg::knx_tunneling_response tunneling_response;
    dg::knx_connection_request con_request;
    dg::knx_connection_response con_response;
    dg::knx_connectionstate_request const_request;
    dg::knx_connectionstate_response const_response;
    dg::knx_disconnect_request discon_request;
    dg::knx_disconnect_response discon_response;
  };  
} // namespace anonymous

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

dg::package* Channel::receive()
{
  udp::endpoint ep;
  unsigned char data[sizeof(datagramUnion)];

  // receive package and create datagram from it
  size_t len = mSocket.receive_from(boost::asio::buffer(data), ep);
  datagramUnion& p = reinterpret_cast<datagramUnion&>(data);

  switch (p.header.service_type_identifier)
  {
  case CONNECT_REQUEST:
    return new dg::knx_connection_request(p.con_request);
  case CONNECT_RESPONSE:
    return new dg::knx_connection_response(p.con_response);
  case DISCONNECT_REQUEST:
    return new dg::knx_disconnect_request(p.discon_request);
  case DISCONNECT_RESPONSE:
    return new dg::knx_disconnect_response(p.discon_response);
  case CONNECTIONSTATE_REQUEST:
    return new dg::knx_connectionstate_request(p.const_request);
  case CONNECTIONSTATE_RESPONSE:
    return new dg::knx_connectionstate_response(p.const_response);
  case TUNNELING_REQUEST:
    return new dg::knx_tunneling_request(p.tunneling_request);
  case TUNNELING_ACKNOWLEDGE:
    return new dg::knx_tunneling_response(p.tunneling_response);
  default:
    throw UnknownServiceTypeID(p.header.service_type_identifier);
  }
}
